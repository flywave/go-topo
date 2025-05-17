/********************************************************************************
 *                                                                              *
 * This file is part of IfcOpenShell.                                           *
 *                                                                              *
 * IfcOpenShell is free software: you can redistribute it and/or modify         *
 * it under the terms of the Lesser GNU General Public License as published by  *
 * the Free Software Foundation, either version 3.0 of the License, or          *
 * (at your option) any later version.                                          *
 *                                                                              *
 * IfcOpenShell is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                 *
 * Lesser GNU General Public License for more details.                          *
 *                                                                              *
 * You should have received a copy of the Lesser GNU General Public License     *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.         *
 *                                                                              *
 ********************************************************************************/

#include <ifcgeom/mapping/mapping.h>
#define mapping POSTFIX_SCHEMA(mapping)
using namespace ifcopenshell::geometry;

#ifdef SCHEMA_HAS_IfcCurveSegment

#include <ifcgeom/profile_helper.h>

#include <boost/math/quadrature/trapezoidal.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <numeric>

namespace {
// @todo: rb is there a common math library these functions can be moved to?
auto sign = [](double v) -> double { return v ? v / fabs(v) : 1.0; };

enum segment_type_t {
    ST_HORIZONTAL,
    ST_VERTICAL,
    ST_CANT
};

// @todo use std::numbers::pi when upgrading to C++ 20
static const double PI = boost::math::constants::pi<double>();

double translate_to_length_measure(const IfcSchema::IfcCurve* crv, double param_value) {
    if (std::abs(param_value) < 1.e-7) {
        return param_value;
    } else if (auto line = crv->as<IfcSchema::IfcLine>()) {
        return line->Dir()->Magnitude() * param_value;
    } else if (auto clothoid = crv->as<IfcSchema::IfcClothoid>()) {
       // param_value = 1.0, corresponds to tangent direction = PI/2
       // param_value = (arc length)/fabs(A*PI)
        return fabs(clothoid->ClothoidConstant()*sqrt(PI))*param_value;
    } else if (auto circ = crv->as<IfcSchema::IfcCircle>()) {
        return circ->Radius() * param_value;
    } else if (auto poly = crv->as<IfcSchema::IfcPolynomialCurve>()) {
        return param_value;
    } else {
        throw std::runtime_error("Unsupported curve measure type");
    }
}

double translate_if_param_value(const IfcSchema::IfcCurve* crv, IfcSchema::IfcCurveMeasureSelect* val) {
    if (auto param = val->as<IfcSchema::IfcParameterValue>()) {
        // We don't care whether length- or positive length measure.
        return translate_to_length_measure(crv, *param);
    } else {
        return val->data().get_attribute_value(0);
    }
}

// vector of parent curve types that are supported for IfcCurveSegment.ParentCurve
typedef boost::mpl::vector<
      IfcSchema::IfcLine
    , IfcSchema::IfcCircle
    , IfcSchema::IfcPolynomialCurve
#ifdef SCHEMA_HAS_IfcClothoid
    , IfcSchema::IfcClothoid
#endif
#if defined SCHEMA_HAS_IfcCosineSpiral
    , IfcSchema::IfcCosineSpiral
#endif
#if defined SCHEMA_HAS_IfcSineSpiral
    , IfcSchema::IfcSineSpiral
#endif
#if defined SCHEMA_HAS_IfcSecondOrderPolynomialSpiral
    , IfcSchema::IfcSecondOrderPolynomialSpiral
#endif
#if defined SCHEMA_HAS_IfcThirdOrderPolynomialSpiral
    , IfcSchema::IfcThirdOrderPolynomialSpiral
#endif
#if defined SCHEMA_HAS_IfcSeventhOrderPolynomialSpiral
    , IfcSchema::IfcSeventhOrderPolynomialSpiral
#endif
> curve_seg_types;


struct parent_curve_function {
    parent_curve_function() = default;
    parent_curve_function(const parent_curve_function&) = default;
    parent_curve_function(std::function<Eigen::Matrix4d(double)> fn, std::function<Eigen::Matrix4d(double)> cfn) : fn_(fn), cfn_(cfn) {
    }

    virtual Eigen::Matrix4d operator()(double u) const { return fn_(u); }
    virtual Eigen::Matrix4d curvature(double u) const { return cfn_(u); }

    private:
    std::function<Eigen::Matrix4d(double)> fn_;
    std::function<Eigen::Matrix4d(double)> cfn_;
};

struct polynomial_parent_curve : public parent_curve_function {
   using parent_curve_function::parent_curve_function;
};

struct line_parent_curve : public parent_curve_function {
    using parent_curve_function::parent_curve_function;
};

struct circle_parent_curve : public parent_curve_function {
    using parent_curve_function::parent_curve_function;
};

struct spiral_parent_curve : public parent_curve_function {
    using parent_curve_function::parent_curve_function;
};

// this is the piecewise curve segment function for horizontal and vertical
struct curve_segment_function {
    curve_segment_function(const Eigen::Matrix4d& curve_segment_placement, const Eigen::Matrix4d& remove_parent_curve_rotation, const Eigen::Matrix4d& remove_parent_curve_translation, std::shared_ptr<parent_curve_function> parent_curve_fn) : 
       curve_segment_placement_(curve_segment_placement),
       remove_parent_curve_rotation_(remove_parent_curve_rotation),
       remove_parent_curve_translation_(remove_parent_curve_translation),
       parent_curve_fn_(parent_curve_fn) {
    }

    Eigen::Matrix4d operator()(double u) const {
        Eigen::Matrix4d parent_curve_point = (*parent_curve_fn_)(u);
        Eigen::Matrix4d curve_segment_point = curve_segment_placement_ * remove_parent_curve_rotation_ * remove_parent_curve_translation_ * parent_curve_point;
        return curve_segment_point + parent_curve_fn_->curvature(u);
    }

  private:
    Eigen::Matrix4d curve_segment_placement_;
    Eigen::Matrix4d remove_parent_curve_rotation_;
    Eigen::Matrix4d remove_parent_curve_translation_;
    std::shared_ptr<parent_curve_function> parent_curve_fn_;
};

// this is the piecewise curve segment function for cant
struct cant_curve_segment_function {
    cant_curve_segment_function(const Eigen::Matrix4d& curve_segment_placement, const Eigen::Matrix4d& parent_curve_start_point, std::shared_ptr<parent_curve_function> parent_curve_fn) : 
       curve_segment_placement_(curve_segment_placement),
       parent_curve_start_point_(parent_curve_start_point),
       parent_curve_fn_(parent_curve_fn) {
    }

    Eigen::Matrix4d operator()(double u) const {
        // The parent curve function returns the cant rotation and superelevation for the parent curve.
        // Subtract the parent_curve_start_point to get the incremental cant rotation and superelevation
        // Add the incremental cant rotation and superelevation to curve_segment_placement to get the curve_segment_point
        Eigen::Matrix4d parent_curve_point = (*parent_curve_fn_)(u);
        Eigen::Matrix4d cant_increment = parent_curve_point - parent_curve_start_point_;
        Eigen::Matrix4d curve_segment_point = curve_segment_placement_ + cant_increment;
        return curve_segment_point + parent_curve_fn_->curvature(u);
    }

  private:
    Eigen::Matrix4d curve_segment_placement_;
    Eigen::Matrix4d parent_curve_start_point_;
    std::shared_ptr<parent_curve_function> parent_curve_fn_;
};

// evaluates a IfcCurveSegment to set up the placement and parent curve function
class curve_segment_evaluator {
  private:
    mapping* mapping_ = nullptr;
    const IfcSchema::IfcCurveSegment* inst_ = nullptr;      // this curve segment instance
    double length_unit_;
    double start_;
    double length_; // length along the curve, as provided from the IfcCurveSegment
    segment_type_t segment_type_;
    const IfcSchema::IfcCurve* parent_curve_ = nullptr;

    double projected_length_; // for vertical segments, this is the length of curve projected onto the "Distance Along" axis

    std::shared_ptr<parent_curve_function> parent_curve_fn_; // function for the parent curve. Function takes distances along, u, and returns the 4x4 position matrix
    std::optional<Eigen::Matrix4d> parent_curve_start_point_; // placement matrix for the parent curve

    std::optional<Eigen::Matrix4d> curve_segment_placement_; // placement of this segment
    std::optional<Eigen::Matrix4d> next_segment_placement_; // placement of the next segment

  public:
    curve_segment_evaluator(mapping* mapping, const IfcSchema::IfcCurveSegment* inst, double length_unit)
        : mapping_(mapping),
          inst_(inst),
          length_unit_(length_unit),
          parent_curve_(inst->ParentCurve()) {

           auto composite_curves = inst->UsingCurves();

        // Find the next segment after inst
        const IfcSchema::IfcCurveSegment* next_inst = nullptr;
        if (composite_curves) {
            if (composite_curves->size() == 1) {
                auto segments = (*composite_curves->begin())->as<IfcSchema::IfcCompositeCurve>()->Segments();
                bool emit_next = false;
                for (auto& s : *segments) {
                    if (emit_next) {
                        next_inst = s->as<IfcSchema::IfcCurveSegment>();
                        break;
                    }
                    if (s == inst) {
                        emit_next = true;
                    }
                }
            } else {
                Logger::Warning("IfcCurveSegment belongs to multiple IfcCompositeCurve instances. Cannot determine the next segment.");
            }
        }

        bool is_horizontal = false;
        bool is_vertical = false;
        bool is_cant = false;

        if (composite_curves) {
            for (auto& cc : *composite_curves) {
                if (cc->as<IfcSchema::IfcSegmentedReferenceCurve>()) {
                    is_cant = true;
                } else if (cc->as<IfcSchema::IfcGradientCurve>()) {
                    is_vertical = true;
                } else {
                    is_horizontal = true;
                }
            }
        }

        if ((is_horizontal + is_vertical + is_cant) != 1) {
            // We have to choose the correct functor based on usage. We can't
            // support multiple, because we don't know the caller at this point.
            Logger::Error(std::runtime_error("multiple uses of IfcSegmentCurve not supported"), inst_);
        }

        segment_type_ = is_horizontal ? ST_HORIZONTAL : is_vertical ? ST_VERTICAL : is_cant  ? ST_CANT : ST_HORIZONTAL;


        start_ = translate_if_param_value(inst->ParentCurve(), inst->SegmentStart()) * length_unit;
        length_ = translate_if_param_value(inst->ParentCurve(), inst->SegmentLength()) * length_unit;
        projected_length_ = length_; // initialize with something reasonable

        if (inst) {
            curve_segment_placement_ = taxonomy::cast<taxonomy::matrix4>(mapping_->map(inst->Placement()))->ccomponents();
        }

        if (next_inst) {
            next_segment_placement_ = taxonomy::cast<taxonomy::matrix4>(mapping_->map(next_inst->Placement()))->ccomponents();
        } else {
           // there is not a next segment, however IfcGradientCurve and IfcSegmentReferenceCurve have an
           // optional EndPoint which services the same purpose as the zero-length last segment.
            IfcSchema::IfcPlacement* end_point = nullptr;
            if (composite_curves->size() == 1) {
                auto& cc = *(composite_curves)->begin();
                if (segment_type_ == ST_VERTICAL) {
                    auto gradient_curve = cc->as<IfcSchema::IfcGradientCurve>();
                    end_point = gradient_curve->EndPoint();
                } else if (segment_type_ == ST_CANT) {
                    auto segmented_reference_curve = cc->as<IfcSchema::IfcSegmentedReferenceCurve>();
                    end_point = segmented_reference_curve->EndPoint();
                }
            } else {
                Logger::Warning("IfcCurveSegment belongs to multiple IfcCompositeCurve instances. Cannot determine the end point.");
            }
            if (end_point) {
                next_segment_placement_ = taxonomy::cast<taxonomy::matrix4>(mapping_->map(end_point))->ccomponents();
            }
        }
    }

    // Take the boost::type value from mpl::for_each and test it against our curve instance
    template <typename T>
    void operator()(boost::type<T>) {
        if (parent_curve_->as<T>()) {
            (*this)(parent_curve_->as<T>());
        }
    }

    double length() const {
        return (segment_type_ == ST_HORIZONTAL || segment_type_ == ST_CANT) ? length_ : projected_length_;
    }

    taxonomy::ptr get_segment_curve_function() {
        if (!parent_curve_fn_ || !parent_curve_start_point_) {
            Logger::Error(std::runtime_error(inst_->ParentCurve()->declaration().name() + " not implemented"), inst_);
        }

        auto length = fabs(this->length());

        if (segment_type_ == ST_CANT) {
            auto fn = cant_curve_segment_function(*curve_segment_placement_, *parent_curve_start_point_, parent_curve_fn_);
            return taxonomy::make<taxonomy::functor_item>(length, fn);
        } else {
            // The parent curve function returns the 4x4 matrix for the parent curve.
            // Subtract the parent curve start point (remove the translation and rotation)
            // to get the incremental translation and rotation. Apply the incremental
            // translation and rotation to the curve_segment_placement to get the curve_segment_point

            // Do a negative translation of the parent curve point relative to the start of the parent curve.
            // This moves parent_curve_fn(u=0.0) to coordinate (0,0).
            // This is done so the curve_segment_placement is applied relative to (0,0)
            Eigen::Matrix4d remove_parent_curve_translation = Eigen::Matrix4d::Identity();
            remove_parent_curve_translation.col(3) = -1.0 * (*parent_curve_start_point_).col(3);
            remove_parent_curve_translation(3, 3) = 1.0;

            // Do a rotation so that the tangent of the parent curve is in the direction (1,0)
            // Example: if the parent curve IfcLine is at a 30 degree clockwise angle, this does
            // a 30 degree counter-clockwise rotation
            // Clockwise rotation matrix = [cos(angle) -sin(angle)]
            //                             [sin(angle)  cos(angle)]
            //
            // Counter-clockwise rotation = [ cos(angle) sin(angle)]
            //                              [-sin(angle) cos(angle)]
            //
            // That's just a sign flip in positions (0,1) and (1,0)
            Eigen::Matrix4d remove_parent_curve_rotation = (*parent_curve_start_point_);
            remove_parent_curve_rotation(0, 1) *= -1.0;
            remove_parent_curve_rotation(1, 0) *= -1.0;
            remove_parent_curve_rotation.col(3) = Eigen::Vector4d(0, 0, 0, 1); // remove the parent curve placement point

            auto fn = curve_segment_function(*curve_segment_placement_, remove_parent_curve_rotation, remove_parent_curve_translation, parent_curve_fn_);
            return taxonomy::make<taxonomy::functor_item>(length, fn);
        }
    }

    void set_spiral_function(double s, std::function<double(double)> fnX, std::function<double(double)> fnY, std::function<double(double)> curvature) {
        if (segment_type_ == ST_HORIZONTAL || segment_type_ == ST_VERTICAL) {
            // start of trimmed curve
            double pcStartX = 0.0, pcStartY = 0.0;
            double pcStartDx = 1.0, pcStartDy = 0.0;
            if (start_) {
                // the spiral doesn't start at the inflection point
                // compute the point where it starts
                pcStartX = boost::math::quadrature::trapezoidal(fnX, 0.0, start_ / s);
                pcStartY = boost::math::quadrature::trapezoidal(fnY, 0.0, start_ / s);

                // compute the slope of the spiral at the start point
                pcStartDx = s ? fnX(start_ / s) / s : 1.0;
                pcStartDy = s ? fnY(start_ / s) / s : 0.0;
            }

            Eigen::Matrix4d p = Eigen::Matrix4d::Identity();
            p.col(0) = Eigen::Vector4d(pcStartDx, pcStartDy, 0, 0);
            p.col(1) = Eigen::Vector4d(-pcStartDy, pcStartDx, 0, 0);
            p.col(3) = Eigen::Vector4d(pcStartX, pcStartY, 0, 1);
            parent_curve_start_point_ = p;

            std::function<double(double)> convert_u;
            if (segment_type_ == ST_HORIZONTAL)
            {
                convert_u = [](double u) -> double { return u; };
            } else {
                // This functor is f'(x) = dy/dx
                 auto df = [fnX,fnY](double t) -> double {
                    auto dy = fnY(t);
                    auto dx = fnX(t);
                    return dx ? dy / dx : 0.0;
                 };

                 // This functor computes the curve length
                 // Integral (sqrt (f'(x) ^ 2 + 1)dx
                 convert_u = [df](double x) -> double {
                     auto fs = [df](double x) -> double {
                         return sqrt(pow(df(x), 2) + 1);
                     };
                     auto s = boost::math::quadrature::trapezoidal(fs, 0.0, x);
                     return s;
                 };
            }

            parent_curve_fn_ = std::make_shared<spiral_parent_curve>(
               [start=start_, s, convert_u, fnX, fnY](double u)->Eigen::Matrix4d {
                   u = convert_u(u+start);

                   // integration limits, integrate from a to b
                   auto b = s ? u / s : 0.0;

                   // point on parent curve
                   auto x = boost::math::quadrature::trapezoidal(fnX, 0.0, b);
                   auto y = boost::math::quadrature::trapezoidal(fnY, 0.0, b);
                   auto dx = s ? fnX(b) / s : 1.0;
                   auto dy = s ? fnY(b) / s : 0.0;

                   Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
                   m.col(0) = Eigen::Vector4d(dx, dy, 0, 0);
                   m.col(1) = Eigen::Vector4d(-dy, dx, 0, 0);
                   m.col(3) = Eigen::Vector4d(x, y, 0, 1);
                   return m;
               },
                [start = start_, convert_u, curvature](double u) -> Eigen::Matrix4d {
                    u = convert_u(u + start);
                    Eigen::Matrix4d c = Eigen::Matrix4d::Zero();
                    c(3, 0) = curvature(u);
                    return c;
               }
            );

            if (segment_type_ == ST_VERTICAL) {
               // for vertical, the input curve length is measured along the spiral.
               // projected_length_ is the domain of the curve, measured in the horizontal "Distance Along" coordinate
               // The quickest way to get the projected length is the difference of the i-ordinates at the start and end of the spiral.

               // Evalute the parent curve at the start and end
                Eigen::Matrix4d m1 = (*parent_curve_fn_)(start_);
                Eigen::Matrix4d m2 = (*parent_curve_fn_)(start_ + length_);

                // parent curve point at start
                double x1 = m1(0, 3);
                double y1 = m1(1, 3);

                // parent curve point at end
                double x2 = m2(0, 3);
                double y2 = m2(1, 3);

                // direction of tangent at start of parent curve in curve coordinates
                auto dx = (*curve_segment_placement_)(0, 0);
                auto dy = -(*curve_segment_placement_)(1, 0); // -1 to rotation in opposite direction
                auto X1 = x1 * dx - y1 * dy; // X of start point in global coordinates
                auto X2 = x2 * dx - y2 * dy; // X of end point in global coordinates
                projected_length_ = X2 - X1; // distance between points on the global X-axis
            } else {
                projected_length_ = length_;
            }
        } else if (segment_type_ == ST_CANT) {
            Logger::Error(std::runtime_error("Unexpected segment type encountered - cant is handled in set_cant_spiral_function - should never get here"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); }
             );
        } else {
            Logger::Error(std::runtime_error("Unexpected segment type encountered"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); }
            );
        }
    }

    // defines the parent_curve_fn_ functor for cant segments.
    void set_cant_spiral_function(std::function<double(double)> Superelevation, std::function<double(double)> SuperelevationSlope, std::function<double(double)> Cant) {
        // compute start cross slope angle, measured relative to (0,0,1)
        auto dy = (*curve_segment_placement_)(1, 2); // Axis.dy
        auto dz = (*curve_segment_placement_)(2, 2); // Axis.dz
        auto start_angle = atan2(dz, dy);

        // compute end cross slope angle, measured relative to (0,0,1)
        dy = (next_segment_placement_.has_value() ? (*next_segment_placement_)(1, 2) : 0.0);
        dz = (next_segment_placement_.has_value() ? (*next_segment_placement_)(2, 2) : 1.0);
        auto end_angle = atan2(dz, dy);

        // angular change of railhead cross slope over the length of the segment
        auto delta_angle = end_angle - start_angle;
        auto start_cant = Cant(0.0 /*start_*/);
        auto end_cant = Cant(/* start_ + */ length_);
        auto delta_cant = end_cant - start_cant;

       parent_curve_fn_ = std::make_shared<spiral_parent_curve>(
          [start_angle,delta_angle,start_cant,delta_cant,Superelevation, SuperelevationSlope, Cant](double u) -> Eigen::Matrix4d {
              // departure of the curve segment from the base curve (superelevation)
              auto super_elevation = Superelevation(u);
              auto slope = SuperelevationSlope(u);

              // direction along curve segment
              auto angle = atan(slope);
              auto dx = cos(angle);
              auto dy = sin(angle);
              Eigen::Vector4d ref_dir(dx, dy, 0.0, 0.0);

              // tilt angle in the plane of the cross section
              auto cant = Cant(u);
              auto tilt_angle = start_angle + delta_angle * (cant - start_cant) / delta_cant;
              Eigen::Vector4d z(0.0, cos(tilt_angle), sin(tilt_angle), 0.0);

              // compute axis direction
              Eigen::Vector4d y = z.cross3(ref_dir);
              Eigen::Vector4d axis = ref_dir.cross3(y);

              Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
              m.col(0) = ref_dir;
              m.col(1) = y;
              m.col(2) = axis;
              m.col(3) = Eigen::Vector4d(u, super_elevation, 0.0, 1.0);
              return m;
          },
          [Cant](double u) -> Eigen::Matrix4d {
                Eigen::Matrix4d c = Eigen::Matrix4d::Zero();
                c(3, 0) = Cant(u);
                return c;
          }
        );

        parent_curve_start_point_ = (*parent_curve_fn_)(0.0);
    }

    // returns function for super elevation and the slope of the super elevation curve if the super elevation is constant
    // over the length of the segment. otherwise, no functions are returned because they are the same as the cant tilt angle
    // functions.
    std::pair<boost::optional<std::function<double(double)>>, boost::optional<std::function<double(double)>>> get_superelevation_functions() {
        boost::optional<std::function<double(double)>> superelevation_fn;
        boost::optional<std::function<double(double)>> superelevation_slope_fn;

        if (curve_segment_placement_.has_value() && next_segment_placement_.has_value()) {
            double y1 = (*curve_segment_placement_)(1, 3);
            double y2 = (*next_segment_placement_)(1, 3);

            // if y2-y1 = 0, the super elevation is constant
            // so we need a function that always returns the constant value
            if (!(y2 - y1)) {
                superelevation_fn = [y1](double) -> double { return y1; };
                superelevation_slope_fn = [](double) -> double { return 0.0; };
            }
        }

        return std::make_pair(superelevation_fn,superelevation_slope_fn);
    }

#ifdef SCHEMA_HAS_IfcClothoid
    void operator()(const IfcSchema::IfcClothoid* c) {
        auto A = c->ClothoidConstant() * length_unit_;
        auto L = length(); // already includes length_unit_

        if (segment_type_ == ST_CANT) {
            boost::optional<std::function<double(double)>> super, slope;
            std::tie(super, slope) = get_superelevation_functions();
            auto cant = [A, L](double t) -> double { return A ? L * L * A * t / fabs(pow(A, 3)) : 0.0; };

            if (!super.has_value()) {
                super = cant;
            }

            if (!slope.has_value()) {
                slope = [A, L](double /*t*/) -> double { return A ? L * A / fabs(pow(A, 3)) : 0.0; };
            }

           set_cant_spiral_function(*super,*slope, cant);
        } else {
            auto s = fabs(A * sqrt(PI)); // curve length when u = 1.0
            auto fn_x = [A, s](double t) -> double { return A ? s * cos(PI * A * t * t / (2 * fabs(A))) : 0.0; };
            auto fn_y = [A, s](double t) -> double { return A ? s * sin(PI * A * t * t / (2 * fabs(A))) : 0.0; };
            auto curvature = [A](double t) -> double { return A ? A * t / fabs(A * A * A) : 0.0; };
            set_spiral_function(s, fn_x, fn_y, curvature);
        }
    }
#endif

#if defined SCHEMA_HAS_IfcCosineSpiral
    void operator()(const IfcSchema::IfcCosineSpiral* c) {
        auto constant_term = c->ConstantTerm();
        if (constant_term.has_value()) {
            constant_term.value() *= length_unit_;
        }
        auto cosine_term = c->CosineTerm() * length_unit_;
        auto L = length(); // already converted to internal units by constructor
        if (segment_type_ == ST_HORIZONTAL) {

            auto theta = [constant_term, cosine_term, L](double t) -> double {
                auto a0 = constant_term.has_value() ? t / constant_term.value() : 0.0;
                auto a1 = (L / PI) * (1.0 / cosine_term) * sin((PI / L) * t);
                return a0 + a1;
            };
            auto fn_x = [theta](double t) -> double { return cos(theta(t)); };
            auto fn_y = [theta](double t) -> double { return sin(theta(t)); };
            auto curvature = [constant_term, cosine_term, L](double t) -> double {
                auto a0 = constant_term.has_value() ? L / constant_term.value() : 0.0;
                auto a1 = (L / cosine_term) * cos((PI / L) * t);
                return a0 + a1;
            };
            double s = 1.0;
            set_spiral_function(s, fn_x, fn_y, curvature);
        } else if (segment_type_ == ST_CANT) {
            boost::optional<std::function<double(double)>> super, slope;
            std::tie(super, slope) = get_superelevation_functions();
            
            auto cant = [constant_term, cosine_term, L](double t) -> double {
                auto a0 = constant_term.has_value() ? 1 / constant_term.value() : 0.0;
                auto a1 = (1 / cosine_term) * cos(PI * t / L);
                return L*L*(a0 + a1);
            };

            if (!super.has_value()) {
                super = cant;
            }

            if (!slope.has_value()) {
                slope = [cosine_term, L](double t) -> double {
                    auto a1 = -(PI / cosine_term) * sin(PI * t / L);
                    return a1;
                };
            }

            set_cant_spiral_function(*super, *slope, cant);
        } else if (segment_type_ == ST_VERTICAL) {
            Logger::Error(std::runtime_error("IfcCosineSpiral cannot be used for vertical alignment"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); }
            );
        } else {
            Logger::Error(std::runtime_error("Unexpected segment type encountered"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); }
            );
        }
    }
#endif

#if defined SCHEMA_HAS_IfcSineSpiral
    void operator()(const IfcSchema::IfcSineSpiral* c) {
        auto constant_term = c->ConstantTerm();
        if (constant_term.has_value()) {
            constant_term.value() *= length_unit_;
        }
        auto linear_term = c->LinearTerm();
        if (linear_term.has_value()) {
            linear_term.value() *= length_unit_;
        }
        auto sine_term = c->SineTerm() * length_unit_;
        auto L = length(); // already converted to internal units by constructor
        if (segment_type_ == ST_HORIZONTAL) {
            auto theta = [constant_term, linear_term, sine_term, L](double t) -> double {
                auto a0 = constant_term.has_value() ? t / constant_term.value() : 0.0;
                auto a1 = linear_term.has_value() ? (linear_term.value() / fabs(linear_term.value())) * pow(t / linear_term.value(), 2.0) / 2.0 : 0.0;
                auto a2 = -1.0 * (L / (2 * PI * sine_term)) * (cos(2 * PI * t / L) - 1.0);
                return a0 + a1 + a2;
            };
            auto fn_x = [theta](double t) -> double { return cos(theta(t)); };
            auto fn_y = [theta](double t) -> double { return sin(theta(t)); };
            auto curvature = [constant_term, linear_term, sine_term, L](double t) -> double {
                auto a0 = constant_term.has_value() ? L / constant_term.value() : 0.0;
                auto a1 = linear_term.has_value() ? (linear_term.value() / fabs(linear_term.value())) * pow(L / linear_term.value(), 2.0) * (t / L) : 0.0;
                auto a2 = (L / sine_term) * sin(2 * PI * t / L);
                return a0 + a1 + a2;
            };
            double s = 1.0;
            set_spiral_function(s, fn_x, fn_y, curvature);
        } else if (segment_type_ == ST_CANT) {
            boost::optional<std::function<double(double)>> super, slope;
            std::tie(super, slope) = get_superelevation_functions();
            
            auto cant = [constant_term, linear_term, sine_term, L](double t) -> double {
               auto a0 = constant_term.has_value() ? 1 / constant_term.value() : 0.0;
               auto a1 = linear_term.has_value() ? (linear_term.value()/fabs(linear_term.value())) * pow(1 / linear_term.value(), 2.0) * t : 0.0;
               auto a2 = (1 / sine_term) * sin(2 * PI * t / L);
               return L*L*(a0 + a1 + a2);
            };

            if (!super.has_value()) {
                super = cant;
            }

            if (!slope.has_value()) {
                slope = [linear_term, sine_term, L](double t) -> double {
                    auto a1 = linear_term.has_value() ? sign(linear_term.value()) * pow(L / linear_term.value(), 2.0) * (1.0 / L) : 0.0;
                    auto a2 = (2 * PI / sine_term) * cos(2 * PI * t / L);
                    return a1 + a2;
                };
            }

            set_cant_spiral_function(*super, *slope, cant);
        } else if (segment_type_ == ST_VERTICAL) {
            Logger::Error(std::runtime_error("IfcSineSpiral cannot be used for vertical alignment"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
        } else {
            Logger::Error(std::runtime_error("Unexpected segment type encountered"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
        }
    }
#endif

    void polynomial_spiral(boost::optional<double> A0, boost::optional<double> A1, boost::optional<double> A2, boost::optional<double> A3, boost::optional<double> A4, boost::optional<double> A5, boost::optional<double> A6, boost::optional<double> A7) {
        auto theta = [A0, A1, A2, A3, A4, A5, A6, A7, start = start_ * length_unit_, lu = length_unit_](double t) -> double {
            auto a0 = A0.get_value_or(0.0) != 0.0 ? t / (A0.value() * lu) : 0.0;
            auto a1 = A1.get_value_or(0.0) != 0.0 ? A1.value() * lu * std::pow(t, 2) / (2 * fabs(std::pow(A1.value() * lu, 3))) : 0.0;
            auto a2 = A2.get_value_or(0.0) != 0.0 ? std::pow(t, 3) / (3 * std::pow(A2.value() * lu, 3)) : 0.0;
            auto a3 = A3.get_value_or(0.0) != 0.0 ? A3.value() * lu * std::pow(t, 4) / (4 * fabs(std::pow(A3.value() * lu, 5))) : 0.0;
            auto a4 = A4.get_value_or(0.0) != 0.0 ? std::pow(t, 5) / (5 * std::pow(A4.value() * lu, 5)) : 0.0;
            auto a5 = A5.get_value_or(0.0) != 0.0 ? A5.value() * lu * std::pow(t, 6) / (6 * fabs(std::pow(A5.value() * lu, 7))) : 0.0;
            auto a6 = A6.get_value_or(0.0) != 0.0 ? std::pow(t, 7) / (7 * std::pow(A6.value() * lu, 7)) : 0.0;
            auto a7 = A7.get_value_or(0.0) != 0.0 ? A7.value() * lu * std::pow(t, 8) / (8 * fabs(std::pow(A7.value() * lu, 9))) : 0.0;
            return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7;
        };

        auto fn_x = [theta](double t) -> double { return cos(theta(t)); };
        auto fn_y = [theta](double t) -> double { return sin(theta(t)); };


        // this is same as cant function in polynomial_cant_spiral
        auto curvature = [A0, A1, A2, A3, A4, A5, A6, A7, start = start_, L = length_, lu = length_unit_, length = length_](double t) -> double {
            t += start;
            auto a0 = A0.get_value_or(0.0) != 0.0 ? 1 / (A0.value() * lu) : 0.0;
            auto a1 = A1.get_value_or(0.0) != 0.0 ? A1.value() * lu * t / fabs(std::pow(A1.value() * lu, 3)) : 0.0;
            auto a2 = A2.get_value_or(0.0) != 0.0 ? std::pow(t, 2) / std::pow(A2.value() * lu, 3) : 0.0;
            auto a3 = A3.get_value_or(0.0) != 0.0 ? A3.value() * lu * std::pow(t, 3) / fabs(std::pow(A3.value() * lu, 5)) : 0.0;
            auto a4 = A4.get_value_or(0.0) != 0.0 ? std::pow(t, 4) / std::pow(A4.value() * lu, 5) : 0.0;
            auto a5 = A5.get_value_or(0.0) != 0.0 ? A5.value() * lu * std::pow(t, 5) / fabs(std::pow(A5.value() * lu, 7)) : 0.0;
            auto a6 = A6.get_value_or(0.0) != 0.0 ? std::pow(t, 6) / std::pow(A6.value() * lu, 7) : 0.0;
            auto a7 = A7.get_value_or(0.0) != 0.0 ? A7.value() * lu * std::pow(t, 7) / fabs(std::pow(A7.value() * lu, 9)) : 0.0;
            return L * (a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7);
        };


        double s = 1.0;
        set_spiral_function(s, fn_x, fn_y, curvature);
    }

    void polynomial_cant_spiral(boost::optional<double> A0, boost::optional<double> A1, boost::optional<double> A2, boost::optional<double> A3, boost::optional<double> A4, boost::optional<double> A5, boost::optional<double> A6, boost::optional<double> A7) {
        boost::optional<std::function<double(double)>> super, slope;
        std::tie(super, slope) = get_superelevation_functions();

        auto cant = [A0, A1, A2, A3, A4, A5, A6, A7, start = start_, L = length_, lu = length_unit_, length = length_](double t) -> double {
            t += start;
            auto a0 = A0.get_value_or(0.0) != 0.0 ? 1 / (A0.value() * lu) : 0.0;
            auto a1 = A1.get_value_or(0.0) != 0.0 ? A1.value() * lu * t / fabs(std::pow(A1.value() * lu, 3)) : 0.0;
            auto a2 = A2.get_value_or(0.0) != 0.0 ? std::pow(t, 2) / std::pow(A2.value() * lu, 3) : 0.0;
            auto a3 = A3.get_value_or(0.0) != 0.0 ? A3.value() * lu * std::pow(t, 3) / fabs(std::pow(A3.value() * lu, 5)) : 0.0;
            auto a4 = A4.get_value_or(0.0) != 0.0 ? std::pow(t, 4) / std::pow(A4.value() * lu, 5) : 0.0;
            auto a5 = A5.get_value_or(0.0) != 0.0 ? A5.value() * lu * std::pow(t, 5) / fabs(std::pow(A5.value() * lu, 7)) : 0.0;
            auto a6 = A6.get_value_or(0.0) != 0.0 ? std::pow(t, 6) / std::pow(A6.value() * lu, 7) : 0.0;
            auto a7 = A7.get_value_or(0.0) != 0.0 ? A7.value() * lu * std::pow(t, 7) / fabs(std::pow(A7.value() * lu, 9)) : 0.0;
            return L * L * (a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7);
        };

        if (!super.has_value()) {
            super = cant;
        }

        if (!slope.has_value()) {
            slope = [A1, A2, A3, A4, A5, A6, A7, start = start_, L = length_, lu = length_unit_, length = length_](double t) -> double {
                t += start;
                auto a1 = A1.get_value_or(0.0) != 0.0 ? A1.value() * lu / fabs(std::pow(A1.value() * lu, 3)) : 0.0;
                auto a2 = A2.get_value_or(0.0) != 0.0 ? 2 * t / std::pow(A2.value() * lu, 3) : 0.0;
                auto a3 = A3.get_value_or(0.0) != 0.0 ? 3 * A3.value() * lu * std::pow(t, 2) / fabs(std::pow(A3.value() * lu, 5)) : 0.0;
                auto a4 = A4.get_value_or(0.0) != 0.0 ? 4 * std::pow(t, 3) / std::pow(A4.value() * lu, 5) : 0.0;
                auto a5 = A5.get_value_or(0.0) != 0.0 ? 5 * A5.value() * lu * std::pow(t, 4) / fabs(std::pow(A5.value() * lu, 7)) : 0.0;
                auto a6 = A6.get_value_or(0.0) != 0.0 ? 6 * std::pow(t, 5) / std::pow(A6.value() * lu, 7) : 0.0;
                auto a7 = A7.get_value_or(0.0) != 0.0 ? 7 * A7.value() * lu * std::pow(t, 6) / fabs(std::pow(A7.value() * lu, 9)) : 0.0;
                return L * L * (a1 + a2 + a3 + a4 + a5 + a6 + a7);
            };
        }

        set_cant_spiral_function(*super, *slope, cant);
    }

#ifdef SCHEMA_HAS_IfcSecondOrderPolynomialSpiral
    void operator()(const IfcSchema::IfcSecondOrderPolynomialSpiral* c) {
        auto A0 = c->ConstantTerm();
        auto A1 = c->LinearTerm();
        auto A2 = c->QuadraticTerm();
        boost::optional<double> A3, A4, A5, A6, A7;

        if (segment_type_ == ST_CANT) {
            polynomial_cant_spiral(A0, A1, A2, A3, A4, A5, A6, A7);
        } else {
            polynomial_spiral(A0, A1, A2, A3, A4, A5, A6, A7);
        }
    }
#endif

#ifdef SCHEMA_HAS_IfcThirdOrderPolynomialSpiral
    void operator()(const IfcSchema::IfcThirdOrderPolynomialSpiral* c) {
        auto A0 = c->ConstantTerm();
        auto A1 = c->LinearTerm();
        auto A2 = c->QuadraticTerm();
        auto A3 = c->CubicTerm();
        boost::optional<double> A4, A5, A6, A7;

        if (segment_type_ == ST_CANT) {
            polynomial_cant_spiral(A0, A1, A2, A3, A4, A5, A6, A7);
        } else {
            polynomial_spiral(A0, A1, A2, A3, A4, A5, A6, A7);
        }
    }
#endif

#ifdef SCHEMA_HAS_IfcSeventhOrderPolynomialSpiral
    void operator()(const IfcSchema::IfcSeventhOrderPolynomialSpiral* c) {
        auto A0 = c->ConstantTerm();
        auto A1 = c->LinearTerm();
        auto A2 = c->QuadraticTerm();
        auto A3 = c->CubicTerm();
        auto A4 = c->QuarticTerm();
        auto A5 = c->QuinticTerm();
        auto A6 = c->SexticTerm();
        auto A7 = c->SepticTerm();

        if (segment_type_ == ST_CANT) {
            polynomial_cant_spiral(A0, A1, A2, A3, A4, A5, A6, A7);
        } else {
            polynomial_spiral(A0, A1, A2, A3, A4, A5, A6, A7);
        }
    }
#endif

    void operator()(const IfcSchema::IfcCircle* c) {
        if (segment_type_ == ST_HORIZONTAL || segment_type_ == ST_VERTICAL) {
            auto R = c->Radius() * length_unit_;
            auto parent_curve_position = taxonomy::cast<taxonomy::matrix4>(mapping_->map(c->Position()))->ccomponents();

            // center point of the parent curve
            auto pcCenterX = parent_curve_position(0, 3);
            auto pcCenterY = parent_curve_position(1, 3);
            auto pcDx = parent_curve_position(0, 0);
            auto pcDy = parent_curve_position(1, 0);

            // angle from X = 0 to the parent curve X-axis
            auto pc_axis_angle = atan2(pcDy, pcDx);
            // sweep angle from the parent curve X-axis to the first point on the trimmed curve
            auto sweep_start_angle = R ? start_ / R : 0.0;
            // angle from X = 0 to the first point on the trimmed curve
            auto start_angle = pc_axis_angle + sweep_start_angle;

            auto sign_l = sign(length_);

            projected_length_ = length_;

            std::function<double(double)> convert_u;
            if (segment_type_ == ST_HORIZONTAL) {
                convert_u = [](double u) { return u; };
            } else {
                auto curve_segment_placement = taxonomy::cast<taxonomy::matrix4>(mapping_->map(inst_->Placement()))->ccomponents();
                auto csStartX = curve_segment_placement(0, 3);
                auto csStartY = curve_segment_placement(1, 3);
                auto csStartDx = curve_segment_placement(0, 0);
                auto csStartDy = curve_segment_placement(1, 0);
                auto csCenterX = csStartX - sign_l * csStartDy * R;
                auto csCenterY = csStartY + sign_l * csStartDx * R;

                // determine projected length along the x-axis
                auto subtended_angle = R ? length_ / R : 0.0;
                auto end_angle = start_angle + subtended_angle;
                auto csEndX = csCenterX + R * cos(end_angle);
                projected_length_ = csEndX - csStartX;

                convert_u = [csStartX, csStartY, csCenterX, csCenterY, R, sign_l](double u) {
                    // for vertical, u is measured along the horizonal but we need it to be an arc length

                    // x and y are coordinates on the curve segment for horizontal distance u from the start point
                    // u is a horizontal distance so x = csStartX + u
                    // Recognizing the triangle
                    // R^2 = (u + csStartX - csCenterX)^2 + (y - csCenterY)^2
                    // solve for y
                    // (y - csCenterY) = sqrt( R^2 - (u + csStartX - csCenterX)^2 )
                    // y = csCenterY + sqrt( R^2 - (u + csStartX - csCenterX)^2 )
                    auto x = csStartX + u;
                    auto y = csCenterY - sign_l * sqrt(pow(R, 2) - pow(u + csStartX - csCenterX, 2));

                    // compute the chord distance between the start point and (x,y)
                    auto c = sqrt(pow(x - csStartX, 2.0) + pow(y - csStartY, 2.0));

                    // compute the subtended angle
                    // c = 2R*sin(delta/2)
                    auto delta = R ? 2.0 * asin(c / (2 * R)) : 0.0;

                    // compute the arc length (this will always be a positive value)
                    u = R * fabs(delta);
                    return u;
                };
            }

            parent_curve_fn_ = std::make_shared<circle_parent_curve>(
               [segment_type = segment_type_, R, pcCenterX, pcCenterY, start_angle, sign_l, convert_u](double u)->Eigen::Matrix4d {
                   u = convert_u(u);

                   // u is measured along the circle
                   // angle from the X=0 axis to the current point
                   auto delta = R ? sign_l * u / R : 0.0;
                   auto sweep_angle = start_angle + delta;
                   auto cos_sweep_angle = cos(sweep_angle);
                   auto sin_sweep_angle = sin(sweep_angle);

                   // point on the parent curve
                   auto pcX = R * cos_sweep_angle + pcCenterX;
                   auto pcY = R * sin_sweep_angle + pcCenterY;

                   auto pcDx = -sign_l * sin_sweep_angle;
                   auto pcDy =  sign_l * cos_sweep_angle;

                   Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
                   m.col(0) = Eigen::Vector4d(pcDx, pcDy, 0, 0);
                   m.col(1) = Eigen::Vector4d(-pcDy, pcDx, 0, 0);
                   m.col(3) = Eigen::Vector4d(pcX, pcY, 0.0, 1.0);
                   return m;
               },
               [R](double) -> Eigen::Matrix4d {
                    Eigen::Matrix4d c = Eigen::Matrix4d::Zero();
                    c(3, 0) = 1 / R;
                    return c;
               }
            );

            if (segment_type_ == ST_HORIZONTAL) {
                parent_curve_start_point_ = (*parent_curve_fn_)(start_);
            } else {
               // @todo - find a way to simplify this
               // For vertical circle "u" is a horizontal measurement and it needs to be converted
               // to a distance along the circle. However, when evaluating the start point,
               // start_ is distance along. parent_curve_fn_ will call it's convert_u method
               // which would be wrong in this case. For this reason, the start point of the parent curve
               // is explicitly computed here. This code is a little redundant with parent_curve_fn_.
                auto cos_start_angle = cos(start_angle);
                auto sin_start_angle = sin(start_angle);

                // point on the parent curve
                auto pcStartX = R * cos_start_angle + pcCenterX;
                auto pcStartY = R * sin_start_angle + pcCenterY;

                auto pcStartDx = -sign_l * sin_start_angle;
                auto pcStartDy =  sign_l * cos_start_angle;

                Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
                m.col(0) = Eigen::Vector4d(pcStartDx, pcStartDy, 0, 0);
                m.col(1) = Eigen::Vector4d(-pcStartDy, pcStartDx, 0, 0);
                m.col(3) = Eigen::Vector4d(pcStartX, pcStartY, 0.0, 1.0);
                parent_curve_start_point_ = m;
            }

        } else if (segment_type_ == ST_CANT) {
            Logger::Warning(std::runtime_error("Use of IfcCircle for cant is not supported"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
        } else {
            Logger::Error(std::runtime_error("Unexpected segment type encountered"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
        }
    }
    
    void operator()(const IfcSchema::IfcLine* l) {
       projected_length_ = length_;

       auto c = l->Pnt()->Coordinates();
       auto pcX = c[0] * length_unit_;
       auto pcY = c[1] * length_unit_;

       // 8.9.3.75 IfcVector https://standards.buildingsmart.org/IFC/RELEASE/IFC4_3/HTML/lexical/IfcVector.htm
       // 8.9.3.30 IfcDirection https://standards.buildingsmart.org/IFC/RELEASE/IFC4_3/HTML/lexical/IfcDirection.htm
       // "The IfcDirection does not imply a vector length, and the direction ratios does not have to be normalized."
       //
       // Therefore, the direction ratios need to be normalized to compute points on the line. 
       // 
       // Magnitude is not used because it relates to the parameterization of the line, which isn't currently done for IfcCurveSegment
       // @todo - parameterization was recently added so Magnitude needs to be taking into consideration
       auto dr = l->Dir()->Orientation()->DirectionRatios();

       // normalize the direction ratios
       double m_squared = std::inner_product(dr.begin(), dr.end(), dr.begin(), 0.0);
       double m = sqrt(m_squared);
       std::transform(dr.begin(), dr.end(), dr.begin(), [m](auto& d) { return d / m; });
       auto pcDx = dr[0];
       auto pcDy = dr[1];

       if (segment_type_ == ST_VERTICAL && curve_segment_placement_) {
          // the general algorithm for mapping parent curve onto curve segment doesn't
          // exactly work for IfcLine. This is easily overcome by using the curve segment
          // placement for the IfcLine direction
          pcDx = (*curve_segment_placement_)(0, 0);
          pcDy = (*curve_segment_placement_)(1, 0);

          // projected length along the x-axis is the 'i' component of the total length
          projected_length_ = length_ * pcDx;
       }

       if (segment_type_ == ST_HORIZONTAL || segment_type_ == ST_VERTICAL || segment_type_ == ST_CANT) {
          std::function<double(double)> convert_u;
          if (segment_type_ == ST_HORIZONTAL || segment_type_ == ST_CANT) {
              convert_u = [](double u) { return u; }; // u is along curve
          } else {
             // u is along horizontal, convert to along curve
              convert_u = [pcDx](double u) { return u/pcDx; };
          }

          parent_curve_fn_ = std::make_shared<line_parent_curve>(
              [pcX, pcY, pcDx, pcDy, convert_u](double u)->Eigen::Matrix4d {
                  u = convert_u(u);

                  auto x = pcX + pcDx * u;
                  auto y = pcY + pcDy * u;

                  Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
                  m.col(0) = Eigen::Vector4d(pcDx, pcDy, 0, 0);
                  m.col(1) = Eigen::Vector4d(-pcDy, pcDx, 0, 0);
                  m.col(3) = Eigen::Vector4d(x, y, 0.0, 1.0);
                  return m;
              },
              [](double /*u*/) -> Eigen::Matrix4d {
                  // curvature is zero for a line. identity initializes c(3,0) = 0
                  Eigen::Matrix4d c = Eigen::Matrix4d::Zero();
                  return c;
              }
          );

          parent_curve_start_point_ = (*parent_curve_fn_)(start_);
       } else {
           Logger::Warning(std::runtime_error("Unexpected segment type encountered"));
           parent_curve_fn_ = std::make_shared<parent_curve_function>(
               [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
               [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
       }
    }

    void operator()(const IfcSchema::IfcPolynomialCurve* pc) {
        // see https://forums.buildingsmart.org/t/ifcpolynomialcurve-clarification/4716 for discussion on IfcPolynomialCurve
        auto coeffX = pc->CoefficientsX().get_value_or(std::vector<double>());
        auto coeffY = pc->CoefficientsY().get_value_or(std::vector<double>());
        auto coeffZ = pc->CoefficientsZ().get_value_or(std::vector<double>());
        if (!coeffZ.empty()) {
            Logger::Warning("Expected IfcPolynomialCurve.CoefficientsZ to be undefined for alignment geometry. Coefficients ignored.", pc);
        }

        if (segment_type_ == ST_HORIZONTAL || segment_type_ == ST_VERTICAL) {
            projected_length_ = length_;

            // There is one significant difference between IfcPolynomialCurve used for horizontal and vertical alignments.
            // For horizontal alignment, u is the distance along the curve. For vertical alignment, u is the horizontal distance.
            // From 4.2.2.2.8 the polynomial curve equation is in the form of y = Ax^3 for horizontal parabolic transition segments.
            // To evaluate the horizontal function, the value of x that corresponds to the distance along the curve u is needed.
            // This is what the convert_u functor does. For vertical curves, the convert_u functor simply returns x = u.
            std::function<double(double)> convert_u;

            // A numerical method is required to return the x-coordinate that corresponds to a 'u' value (distance along the curve)
            std::function<double(double)> x_at_dist_along;


            // Distance along the curve is  Integral[0,x] (sqrt(f'(x)^2 + 1) dx

            // This functor is the derivative of y(x) => dy/dx = f'(x)
            auto df = [lu=length_unit_,coeffY](double x) -> double {
                auto begin = coeffY.begin();
                auto iter = std::next(begin);
                auto end = coeffY.end();
                double value = 0;
                // y = A0 + A1*x + A2*x^2 + A3*x^3
                // y' = 0 + 1*A1*x^0 + 2*A2*x^1 + 3*A3*x^2
                // The units of y are length. y' is unitless
                // The units of x are length.
                // A unit conversion of the coefficients is needed
                // A1 = length^0
                // A2 = length^-1
                // A3 = Length^-2
                for (; iter != end; iter++) {
                    auto exp = std::distance(begin, iter);
                    auto coeff = (*iter);
                    double v = (double)exp * coeff * pow(lu, 1-exp) * pow(x, exp - 1);
                    value += v;
                }
                return value;
            };

            // This functor computes the curve length
            // Integral[0,x] (sqrt(f'(x)^2 + 1) dx
            auto curve_length_fn = [df](double x) -> double {
                auto fs = [df](double x) -> double {
                    return sqrt(pow(df(x), 2) + 1);
                };
                auto s = boost::math::quadrature::trapezoidal(fs, 0.0, x);
                return s;
            };
            // There isn't a closed form solution to get x that corresponds to a distance along the curve, u
            // A numerical solution is required.
            // This functor finds the value of x such that s(x) - u = 0, where u is the input value and s is the
            // computed curve length.
            x_at_dist_along = [curve_length_fn](double u) -> double {
                std::uintmax_t max_iter = 9000;
                auto tol = [](double a, double b) { return fabs(b - a) < 1.0E-11; };
                auto x = u; // start by assuming u = x (it's not, but it will be close)
                try {
                    // set up the root finding function that evaluates s(x) - u
                    auto f = [curve_length_fn, u](double x) -> double { return curve_length_fn(x) - u; };
                    // use a root finder to get x
                    auto result = boost::math::tools::bracket_and_solve_root(f, x, 2.0, true, tol, max_iter);
                    x = result.first;
                } catch (...) {
                    Logger::Warning("root solver failed");
                }
                return x;
            };

            if (segment_type_ == ST_HORIZONTAL) {
                convert_u = x_at_dist_along;
            } else {
                // for vertical, u = x
                convert_u = [](double u) -> double { return u; };
                projected_length_ = x_at_dist_along(length_);
            }

            // This functor evaluates the polynomial at a distance u along the curve
            parent_curve_fn_ = std::make_shared<polynomial_parent_curve>(
                     [start = start_, lu = length_unit_, coeffX, coeffY, convert_u](double u)->Eigen::Matrix4d {
                     auto x = convert_u(u + start); // find x for u
                     // evaluate the polynomial at x
                     std::array<const std::vector<double>*, 2> coefficients{&coeffX, &coeffY};
                     std::array<double, 2> position{0.0, 0.0}; // = SUM(coeff*u^pos)
                     std::array<double, 2> slope{0.0, 0.0};    // slope is derivative of the curve = SUM( coeff*pos*u^(pos-1) )
                     for (int i = 0; i < 2; i++) {             // loop over X and Y
                         auto begin = coefficients[i]->cbegin();
                         auto end = coefficients[i]->cend();
                         for (auto iter = begin; iter != end; iter++) {
                             auto exp = std::distance(begin, iter);
                             auto coeff = (*iter);
                             position[i] += coeff * pow(lu, 1-exp) * pow(x, exp);

                             if (iter != begin) {
                                 slope[i] += exp * coeff * pow(lu, 1-exp) * pow(x, exp - 1);
                             }
                         }
                     }

                     auto X = position[0];
                     auto Y = position[1];

                     auto Dx = slope[0];
                     auto Dy = slope[1];

                     auto angle = atan2(Dy, Dx);
                     Dx = cos(angle);
                     Dy = sin(angle);

                     Eigen::Matrix4d m = Eigen::Matrix4d::Identity();
                     m.col(0) = Eigen::Vector4d(Dx, Dy, 0, 0);
                     m.col(1) = Eigen::Vector4d(-Dy, Dx, 0, 0);
                     m.col(3) = Eigen::Vector4d(X, Y, 0.0, 1.0);
                     return m;
                },
                [start = start_, lu = length_unit_, coeffX, coeffY, convert_u](double u) -> Eigen::Matrix4d { 
                     auto x = convert_u(u + start); // find x for u
                    Eigen::Matrix4d c = Eigen::Matrix4d::Zero();
                    c(3, 0) = coeffY[2]; // this may need a unit conversion (also assume there is only 3 coefficients)
                     return c;
                }
            );

            parent_curve_start_point_ = (*parent_curve_fn_)(0.0); // start is added to u in parent_curve_fn_, so use 0.0 here
        } else if (segment_type_ == ST_CANT) {
            Logger::Warning(std::runtime_error("Use of IfcPolynomialCurve for cant is not supported"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
        } else {
            Logger::Error(std::runtime_error("Unexpected segment type encountered"));
            parent_curve_fn_ = std::make_shared<parent_curve_function>(
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); },
                [](double /*u*/) -> Eigen::Matrix4d { return Eigen::Matrix4d::Identity(); });
        }
    }
};
} // namespace

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcCurveSegment* inst) {
    curve_segment_evaluator cse(this, inst, length_unit_);
    boost::mpl::for_each<curve_seg_types, boost::type<boost::mpl::_>>(std::ref(cse));
    return cse.get_segment_curve_function();
}

#endif
