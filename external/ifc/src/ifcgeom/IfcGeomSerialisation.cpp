#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_BSplineCurve.hxx>

#include <Geom_Plane.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_CylindricalSurface.hxx>

#include <BRepTools_WireExplorer.hxx>

#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Geom_BezierCurve.hxx>

#include "IfcGeom.h"
namespace IFC_NAMESPACE {

template <typename T, typename U>
int convert_to_ifc(const T& t, U*& u, bool /*advanced*/) {
	std::vector<double> coords(3);
	coords[0] = t.X(); coords[1] = t.Y(); coords[2] = t.Z();
	u = new U(coords);
	return 1;
}

template <>
int convert_to_ifc(const TopoDS_Vertex& v, IFC_NAMESPACE::IfcSchema::IfcCartesianPoint*& p, bool advanced) {
	gp_Pnt pnt = BRep_Tool::Pnt(v);
	return convert_to_ifc(pnt, p, advanced);
}

template <>
int convert_to_ifc(const TopoDS_Vertex& v, IFC_NAMESPACE::IfcSchema::IfcVertex*& vertex, bool advanced) {
	IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;
	if (convert_to_ifc(v, p, advanced)) {
		vertex = new IFC_NAMESPACE::IfcSchema::IfcVertexPoint(p);
		return 1;
	} else {
		return 0;
	}
}

template <>
int convert_to_ifc(const gp_Ax2& a, IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D*& ax, bool advanced) {
	IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;
	IFC_NAMESPACE::IfcSchema::IfcDirection *x, *z;
	if (!(convert_to_ifc(a.Location(), p, advanced) && convert_to_ifc(a.Direction(), z, advanced) && convert_to_ifc(a.XDirection(), x, advanced))) {
        ax = 0;
		return 0;
	}
	ax = new IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D(p, z, x);
	return 1;
}

template <typename T, typename U>
void opencascade_array_to_vector(T& t, std::vector<U>& u) {
	u.reserve(t.Length());
	for (int i = t.Lower(); i <= t.Upper(); ++i) {
		u.push_back(t.Value(i));
	}
}

template <typename T, typename U>
void opencascade_array_to_vector2(T& t, std::vector< std::vector<U> >& u) {
	u.reserve(t.RowLength());
	for (int j = t.LowerRow(); j <= t.UpperRow(); ++j) {
		std::vector<U> v;
		v.reserve(t.ColLength());
		for (int i = t.LowerCol(); i <= t.UpperCol(); ++i) {
			v.push_back(t.Value(j, i));
		}
		u.push_back(v);
	}
}

#ifdef SCHEMA_HAS_IfcRationalBSplineSurfaceWithKnots
namespace {
	IFC_NAMESPACE::IfcSchema::IfcKnotType::Value opencascade_knotspec_to_ifc(GeomAbs_BSplKnotDistribution bspline_knot_spec) {
		IFC_NAMESPACE::IfcSchema::IfcKnotType::Value knot_spec = IFC_NAMESPACE::IfcSchema::IfcKnotType::IfcKnotType_UNSPECIFIED;
		if (bspline_knot_spec == GeomAbs_Uniform) {
			knot_spec = IFC_NAMESPACE::IfcSchema::IfcKnotType::IfcKnotType_UNIFORM_KNOTS;
		} else if (bspline_knot_spec == GeomAbs_QuasiUniform) {
			knot_spec = IFC_NAMESPACE::IfcSchema::IfcKnotType::IfcKnotType_QUASI_UNIFORM_KNOTS;
		} else if (bspline_knot_spec == GeomAbs_PiecewiseBezier) {
			knot_spec = IFC_NAMESPACE::IfcSchema::IfcKnotType::IfcKnotType_PIECEWISE_BEZIER_KNOTS;
		}
		return knot_spec;
	}
}
#endif

template <>
int convert_to_ifc(const Handle_Geom_Curve& c, IFC_NAMESPACE::IfcSchema::IfcCurve*& curve, bool advanced) {
	if (c->DynamicType() == STANDARD_TYPE(Geom_Line)) {
		IFC_NAMESPACE::IfcSchema::IfcDirection* d;
		IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;

		Handle_Geom_Line line = Handle_Geom_Line::DownCast(c);

		if (!convert_to_ifc(line->Position().Location(), p, advanced)) {
			return 0;
		}
		if (!convert_to_ifc(line->Position().Direction(), d, advanced)) {
			return 0;
		}

		IFC_NAMESPACE::IfcSchema::IfcVector* v = new IFC_NAMESPACE::IfcSchema::IfcVector(d, 1.);
		curve = new IFC_NAMESPACE::IfcSchema::IfcLine(p, v);

		return 1;
	} else if (c->DynamicType() == STANDARD_TYPE(Geom_Circle)) {
		IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* ax;

		Handle_Geom_Circle circle = Handle_Geom_Circle::DownCast(c);

		convert_to_ifc(circle->Position(), ax, advanced);
		curve = new IFC_NAMESPACE::IfcSchema::IfcCircle(ax, circle->Radius());

		return 1;
	} else if (c->DynamicType() == STANDARD_TYPE(Geom_Ellipse)) {
		IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* ax;

		Handle_Geom_Ellipse ellipse = Handle_Geom_Ellipse::DownCast(c);

		convert_to_ifc(ellipse->Position(), ax, advanced);
		curve = new IFC_NAMESPACE::IfcSchema::IfcEllipse(ax, ellipse->MajorRadius(), ellipse->MinorRadius());

		return 1;
	}
#ifdef SCHEMA_HAS_IfcRationalBSplineSurfaceWithKnots
	else if (c->DynamicType() == STANDARD_TYPE(Geom_BezierCurve)) {
		Handle_Geom_BezierCurve bezier = Handle_Geom_BezierCurve::DownCast(c);

		std::vector<int> mults;
		std::vector<double> knots;
		std::vector<double> weights;

		IFC_NAMESPACE::IfcSchema::IfcKnotType::Value knot_spec = IFC_NAMESPACE::IfcSchema::IfcKnotType::IfcKnotType_QUASI_UNIFORM_KNOTS;

		IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list::ptr points(new IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list);
		TColgp_Array1OfPnt poles(1, bezier->NbPoles());
		bezier->Poles(poles);
		for (int i = 1; i <= bezier->NbPoles(); ++i) {
			IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;
			if (!convert_to_ifc(poles.Value(i), p, advanced)) {
				return 0;
			}
			points->push(p);

			if (i == 1 || i == bezier->NbPoles()) {
				mults.push_back(bezier->Degree() + 1);
			} else {
				mults.push_back(bezier->Degree());
			}

			knots.push_back((double) i - 1);
		}

		TColStd_Array1OfReal bspline_weights(1, bezier->NbPoles());
		bezier->Weights(bspline_weights);
		opencascade_array_to_vector(bspline_weights, weights);

		curve = new IFC_NAMESPACE::IfcSchema::IfcRationalBSplineCurveWithKnots(
			bezier->Degree(),
			points,
			IFC_NAMESPACE::IfcSchema::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
			bezier->IsClosed() != 0,
			false,
			mults,
			knots,
			knot_spec,
			weights
		);

		return 1;
	}
	else if (c->DynamicType() == STANDARD_TYPE(Geom_BSplineCurve)) {
		Handle_Geom_BSplineCurve bspline = Handle_Geom_BSplineCurve::DownCast(c);

		IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list::ptr points(new IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list);
		TColgp_Array1OfPnt poles(1, bspline->NbPoles());
		bspline->Poles(poles);
		for (int i = 1; i <= bspline->NbPoles(); ++i) {
			IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;
			if (!convert_to_ifc(poles.Value(i), p, advanced)) {
				return 0;
			}
			points->push(p);
		}
		IFC_NAMESPACE::IfcSchema::IfcKnotType::Value knot_spec = opencascade_knotspec_to_ifc(bspline->KnotDistribution());

		std::vector<int> mults;
		std::vector<double> knots;
		std::vector<double> weights;

		TColStd_Array1OfInteger bspline_mults(1, bspline->NbKnots());
		TColStd_Array1OfReal bspline_knots(1, bspline->NbKnots());
		TColStd_Array1OfReal bspline_weights(1, bspline->NbPoles());

		bspline->Multiplicities(bspline_mults);
		bspline->Knots(bspline_knots);
		bspline->Weights(bspline_weights);

		opencascade_array_to_vector(bspline_mults, mults);
		opencascade_array_to_vector(bspline_knots, knots);
		opencascade_array_to_vector(bspline_weights, weights);

		bool rational = false;
		for (std::vector<double>::const_iterator it = weights.begin(); it != weights.end(); ++it) {
			if ((*it) != 1.) {
				rational = true;
				break;
			}
		}

		if (rational) {
			curve = new IFC_NAMESPACE::IfcSchema::IfcRationalBSplineCurveWithKnots(
				bspline->Degree(),
				points,
				IFC_NAMESPACE::IfcSchema::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
				bspline->IsClosed() != 0,
				false,
				mults,
				knots,
				knot_spec,
				weights
				);
		} else {
			curve = new IFC_NAMESPACE::IfcSchema::IfcBSplineCurveWithKnots(
				bspline->Degree(),
				points,
				IFC_NAMESPACE::IfcSchema::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
				bspline->IsClosed() != 0,
				false,
				mults,
				knots,
				knot_spec
				);
		}

		return 1;
	}
#endif
	return 0;
}

template <>
int convert_to_ifc(const Handle_Geom_Surface& s, IFC_NAMESPACE::IfcSchema::IfcSurface*& surface, bool advanced) {
	if (s->DynamicType() == STANDARD_TYPE(Geom_Plane)) {
		Handle_Geom_Plane plane = Handle_Geom_Plane::DownCast(s);
		IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place;
		/// @todo: Note that the Ax3 is converted to an Ax2 here
		if (!convert_to_ifc(plane->Position().Ax2(), place, advanced)) {
			return 0;
		}
		surface = new IFC_NAMESPACE::IfcSchema::IfcPlane(place);
		return 1;
	}
#ifdef SCHEMA_HAS_IfcRationalBSplineSurfaceWithKnots
	else if (s->DynamicType() == STANDARD_TYPE(Geom_CylindricalSurface)) {
		Handle_Geom_CylindricalSurface cyl = Handle_Geom_CylindricalSurface::DownCast(s);
		IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place;
		/// @todo: Note that the Ax3 is converted to an Ax2 here
		if (!convert_to_ifc(cyl->Position().Ax2(), place, advanced)) {
			return 0;
		}
		surface = new IFC_NAMESPACE::IfcSchema::IfcCylindricalSurface(place, cyl->Radius());
		return 1;
	} else if (s->DynamicType() == STANDARD_TYPE(Geom_BSplineSurface)) {
		typedef IfcTemplatedEntityListList<IFC_NAMESPACE::IfcSchema::IfcCartesianPoint> points_t;

		Handle_Geom_BSplineSurface bspline = Handle_Geom_BSplineSurface::DownCast(s);
		points_t::ptr points(new points_t);

		TColgp_Array2OfPnt poles(1, bspline->NbUPoles(), 1, bspline->NbVPoles());
		bspline->Poles(poles);
		for (int i = 1; i <= bspline->NbUPoles(); ++i) {
			std::vector<IFC_NAMESPACE::IfcSchema::IfcCartesianPoint*> ps;
			ps.reserve(bspline->NbVPoles());
			for (int j = 1; j <= bspline->NbVPoles(); ++j) {
				IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;
				if (!convert_to_ifc(poles.Value(i, j), p, advanced)) {
					return 0;
				}
				ps.push_back(p);
			}
			points->push(ps);
		}

		IFC_NAMESPACE::IfcSchema::IfcKnotType::Value knot_spec_u = opencascade_knotspec_to_ifc(bspline->UKnotDistribution());
		IFC_NAMESPACE::IfcSchema::IfcKnotType::Value knot_spec_v = opencascade_knotspec_to_ifc(bspline->VKnotDistribution());

		if (knot_spec_u != knot_spec_v) {
			knot_spec_u = IFC_NAMESPACE::IfcSchema::IfcKnotType::IfcKnotType_UNSPECIFIED;
		}

		std::vector<int> umults;
		std::vector<int> vmults;
		std::vector<double> uknots;
		std::vector<double> vknots;
		std::vector< std::vector<double> > weights;

		TColStd_Array1OfInteger bspline_umults(1, bspline->NbUKnots());
		TColStd_Array1OfInteger bspline_vmults(1, bspline->NbVKnots());
		TColStd_Array1OfReal bspline_uknots(1, bspline->NbUKnots());
		TColStd_Array1OfReal bspline_vknots(1, bspline->NbVKnots());
		TColStd_Array2OfReal bspline_weights(1, bspline->NbUPoles(), 1, bspline->NbVPoles());

		bspline->UMultiplicities(bspline_umults);
		bspline->VMultiplicities(bspline_vmults);
		bspline->UKnots(bspline_uknots);
		bspline->VKnots(bspline_vknots);
		bspline->Weights(bspline_weights);

		opencascade_array_to_vector(bspline_umults, umults);
		opencascade_array_to_vector(bspline_vmults, vmults);
		opencascade_array_to_vector(bspline_uknots, uknots);
		opencascade_array_to_vector(bspline_vknots, vknots);
		opencascade_array_to_vector2(bspline_weights, weights);

		bool rational = false;
		for (std::vector< std::vector<double> >::const_iterator it = weights.begin(); it != weights.end(); ++it) {
			for (std::vector<double>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
				if ((*jt) != 1.) {
					rational = true;
					break;
				}
			}
		}

		if (rational) {
			surface = new IFC_NAMESPACE::IfcSchema::IfcRationalBSplineSurfaceWithKnots(
				bspline->UDegree(),
				bspline->VDegree(),
				points,
				IFC_NAMESPACE::IfcSchema::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
				bspline->IsUClosed() != 0,
				bspline->IsVClosed() != 0,
				false,
				umults,
				vmults,
				uknots,
				vknots,
				knot_spec_u,
				weights
				);
		} else {
			surface = new IFC_NAMESPACE::IfcSchema::IfcBSplineSurfaceWithKnots(
				bspline->UDegree(),
				bspline->VDegree(),
				points,
				IFC_NAMESPACE::IfcSchema::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
				bspline->IsUClosed() != 0,
				bspline->IsVClosed() != 0,
				false,
				umults,
				vmults,
				uknots,
				vknots,
				knot_spec_u
				);
		}

		return 1;
	}
#endif
	return 0;
}

template <>
int convert_to_ifc(const TopoDS_Edge& e, IFC_NAMESPACE::IfcSchema::IfcCurve*& c, bool advanced) {
	double a, b;
	IFC_NAMESPACE::IfcSchema::IfcCurve* base;

	Handle_Geom_Curve crv = BRep_Tool::Curve(e, a, b);
	if (!convert_to_ifc(crv, base, advanced)) {
		return 0;
	}

	IfcEntityList::ptr trim1(new IfcEntityList);
	IfcEntityList::ptr trim2(new IfcEntityList);
	trim1->push(new IFC_NAMESPACE::IfcSchema::IfcParameterValue(a));
	trim2->push(new IFC_NAMESPACE::IfcSchema::IfcParameterValue(b));

	c = new IFC_NAMESPACE::IfcSchema::IfcTrimmedCurve(base, trim1, trim2, true, IFC_NAMESPACE::IfcSchema::IfcTrimmingPreference::IfcTrimmingPreference_PARAMETER);

	return 1;
}

template <>
int convert_to_ifc(const TopoDS_Edge& e, IFC_NAMESPACE::IfcSchema::IfcEdge*& edge, bool advanced) {
	double a, b;

	TopExp_Explorer exp(e, TopAbs_VERTEX);
	if (!exp.More()) return 0;
	TopoDS_Vertex v1 = TopoDS::Vertex(exp.Current());
	exp.Next();
	if (!exp.More()) return 0;
	TopoDS_Vertex v2 = TopoDS::Vertex(exp.Current());

	IFC_NAMESPACE::IfcSchema::IfcVertex *vertex1, *vertex2;
	if (!(convert_to_ifc(v1, vertex1, advanced) && convert_to_ifc(v2, vertex2, advanced))) {
		return 0;
	}

	Handle_Geom_Curve crv = BRep_Tool::Curve(e, a, b);

	if (crv.IsNull()) {
		return 0;
	}

	if (crv->DynamicType() == STANDARD_TYPE(Geom_Line) && !advanced) {
		IFC_NAMESPACE::IfcSchema::IfcEdge* edge2 = new IFC_NAMESPACE::IfcSchema::IfcEdge(vertex1, vertex2);
		edge = new IFC_NAMESPACE::IfcSchema::IfcOrientedEdge(edge2, true);
		return 1;
	} else {
		IFC_NAMESPACE::IfcSchema::IfcCurve* curve;
		if (!convert_to_ifc(crv, curve, advanced)) {
			return 0;
		}
		/// @todo probably not correct
		const bool sense = e.Orientation() == TopAbs_FORWARD;
		IFC_NAMESPACE::IfcSchema::IfcEdge* edge2 = new IFC_NAMESPACE::IfcSchema::IfcEdgeCurve(vertex1, vertex2, curve, true);
		edge = new IFC_NAMESPACE::IfcSchema::IfcOrientedEdge(edge2, sense);
		return 1;
	}
}

template <>
int convert_to_ifc(const TopoDS_Wire& wire, IFC_NAMESPACE::IfcSchema::IfcLoop*& loop, bool advanced) {
	bool polygonal = true;
	for (TopExp_Explorer exp(wire, TopAbs_EDGE); exp.More(); exp.Next()) {
		double a, b;
		Handle_Geom_Curve crv = BRep_Tool::Curve(TopoDS::Edge(exp.Current()), a, b);
		if (crv.IsNull()) {
			continue;
		}
		if (crv->DynamicType() != STANDARD_TYPE(Geom_Line)) {
			polygonal = false;
			break;
		}
	}
	if (!polygonal && !advanced) {
		return 0;
	} else if (polygonal && !advanced) {
		IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list::ptr points(new IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list);
		BRepTools_WireExplorer exp(wire);
		IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p;
		for (; exp.More(); exp.Next()) {
			if (convert_to_ifc(exp.CurrentVertex(), p, advanced)) {
				points->push(p);
			} else {
				return 0;
			}
		}
		loop = new IFC_NAMESPACE::IfcSchema::IfcPolyLoop(points);
		return 1;
	} else {
		IFC_NAMESPACE::IfcSchema::IfcOrientedEdge::list::ptr edges(new IFC_NAMESPACE::IfcSchema::IfcOrientedEdge::list);
		BRepTools_WireExplorer exp(wire);
		for (; exp.More(); exp.Next()) {
			IFC_NAMESPACE::IfcSchema::IfcEdge* edge;
			// With advanced set to true convert_to_ifc(TopoDS_Edge&) will always create an IfcOrientedEdge
			if (!convert_to_ifc(exp.Current(), edge, true)) {
				double a, b;
				if (BRep_Tool::Curve(TopoDS::Edge(exp.Current()), a, b).IsNull()) {
					continue;
				} else {
					return 0;
				}
			}
			edges->push(edge->as<IFC_NAMESPACE::IfcSchema::IfcOrientedEdge>());
		}
		loop = new IFC_NAMESPACE::IfcSchema::IfcEdgeLoop(edges);
		return 1;
	}
}

template <>
int convert_to_ifc(const TopoDS_Face& f, IFC_NAMESPACE::IfcSchema::IfcFace*& face, bool advanced) {
	Handle_Geom_Surface surf = BRep_Tool::Surface(f);
	TopExp_Explorer exp(f, TopAbs_WIRE);
	IFC_NAMESPACE::IfcSchema::IfcFaceBound::list::ptr bounds(new IFC_NAMESPACE::IfcSchema::IfcFaceBound::list);
	int index = 0;
	for (; exp.More(); exp.Next(), ++index) {
		IFC_NAMESPACE::IfcSchema::IfcLoop* loop;
		if (!convert_to_ifc(TopoDS::Wire(exp.Current()), loop, advanced)) {
			return 0;
		}
		IFC_NAMESPACE::IfcSchema::IfcFaceBound* bnd;
		if (index == 0) {
			bnd = new IFC_NAMESPACE::IfcSchema::IfcFaceOuterBound(loop, true);
		} else {
			bnd = new IFC_NAMESPACE::IfcSchema::IfcFaceBound(loop, true);
		}
		bounds->push(bnd);
	}

	const bool is_planar = surf->DynamicType() == STANDARD_TYPE(Geom_Plane);

	if (!is_planar && !advanced) {
		return 0;
	}
	if (is_planar && !advanced) {
		face = new IFC_NAMESPACE::IfcSchema::IfcFace(bounds);
		return 1;
	} else {
#ifdef SCHEMA_HAS_IfcAdvancedFace
		IFC_NAMESPACE::IfcSchema::IfcSurface* surface;
		if (!convert_to_ifc(surf, surface, advanced)) {
			return 0;
		}
		face = new IFC_NAMESPACE::IfcSchema::IfcAdvancedFace(bounds, surface, f.Orientation() == TopAbs_FORWARD);
		return 1;
#else
		// No IfcAdvancedFace in Ifc2x3
		return 0;
#endif
	}
}

template <typename U>
int convert_to_ifc(const TopoDS_Shape& s, U*& item, bool advanced) {
	IFC_NAMESPACE::IfcSchema::IfcFace::list::ptr faces(new IFC_NAMESPACE::IfcSchema::IfcFace::list);
	IFC_NAMESPACE::IfcSchema::IfcFace* f;

	for (TopExp_Explorer exp(s, TopAbs_FACE); exp.More(); exp.Next()) {
		if (convert_to_ifc(TopoDS::Face(exp.Current()), f, advanced)) {
			faces->push(f);
		} else {
			/// Cleanup:
			for (IFC_NAMESPACE::IfcSchema::IfcFace::list::it it = faces->begin(); it != faces->end(); ++it) {
				IfcEntityList::ptr data = IfcParse::traverse(*it)->unique();
				for (IfcEntityList::it jt = data->begin(); jt != data->end(); ++jt) {
					delete *jt;
				}
			}
			return 0;
		}
	}

	item = new U(faces);
	return faces->size();
}

IfcUtil::IfcBaseClass* IfcGeom::MAKE_TYPE_NAME(serialise_)(const TopoDS_Shape& shape, bool advanced) {

#ifndef SCHEMA_HAS_IfcAdvancedBrep
	advanced = false;
#endif

	for (TopExp_Explorer exp(shape, TopAbs_COMPSOLID); exp.More();) {
		/// @todo CompSolids are not supported
		return 0;
	}

	IFC_NAMESPACE::IfcSchema::IfcRepresentation* rep = 0;
	IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items(new IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);

	// First check if there is a solid with one or more shells
	for (TopExp_Explorer exp(shape, TopAbs_SOLID); exp.More(); exp.Next()) {
		IFC_NAMESPACE::IfcSchema::IfcClosedShell* outer = 0;
		IFC_NAMESPACE::IfcSchema::IfcClosedShell::list::ptr inner(new IFC_NAMESPACE::IfcSchema::IfcClosedShell::list);
		for (TopExp_Explorer exp2(exp.Current(), TopAbs_SHELL); exp2.More(); exp2.Next()) {
			IFC_NAMESPACE::IfcSchema::IfcClosedShell* shell;
			if (!convert_to_ifc(exp2.Current(), shell, advanced)) {
				return 0;
			}
			/// @todo Are shells always in this order or does Orientation() needs to be checked?
			if (outer) {
				inner->push(shell);
			} else {
				outer = shell;
			}
		}

#ifdef SCHEMA_HAS_IfcAdvancedBrep
		if (advanced) {
			if (inner->size()) {
				items->push(new IFC_NAMESPACE::IfcSchema::IfcAdvancedBrepWithVoids(outer, inner));
			} else {
				items->push(new IFC_NAMESPACE::IfcSchema::IfcAdvancedBrep(outer));
			}
		} else
#endif

			/// @todo this is not necessarily correct as the shell is not necessarily facetted.
			if (inner->size()) {
				items->push(new IFC_NAMESPACE::IfcSchema::IfcFacetedBrepWithVoids(outer, inner));
			} else {
				items->push(new IFC_NAMESPACE::IfcSchema::IfcFacetedBrep(outer));
			}

	}

	if (items->size() > 0) {
		rep = new IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(0, std::string("Body"), std::string("Brep"), items);
	} else {

		// If not, see if there is a shell
		IFC_NAMESPACE::IfcSchema::IfcOpenShell::list::ptr shells(new IFC_NAMESPACE::IfcSchema::IfcOpenShell::list);
		for (TopExp_Explorer exp(shape, TopAbs_SHELL); exp.More(); exp.Next()) {
			IFC_NAMESPACE::IfcSchema::IfcOpenShell* shell;
			if (!convert_to_ifc(exp.Current(), shell, advanced)) {
				return 0;
			}
			shells->push(shell);
		}

		if (shells->size() > 0) {
			items->push(new IFC_NAMESPACE::IfcSchema::IfcShellBasedSurfaceModel(shells->generalize()));
			rep = new IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(0, std::string("Body"), std::string("Brep"), items);
		} else {

			// If not, see if there is are one of more faces. Note that they will be grouped into a shell.
			IFC_NAMESPACE::IfcSchema::IfcOpenShell* shell;
			int face_count = convert_to_ifc(shape, shell, advanced);

			if (face_count > 0) {
				items->push(shell);
				rep = new IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(0, std::string("Body"), std::string("Brep"), items);
			} else {

				// If not, see if there are any edges. Note that wires are skipped as
				// they are not commonly top-level geometrical descriptions in IFC.
				// Also note that edges are written as trimmed curves rather than edges.

				IfcEntityList::ptr edges(new IfcEntityList);

				for (TopExp_Explorer exp(shape, TopAbs_EDGE); exp.More(); exp.Next()) {
					IFC_NAMESPACE::IfcSchema::IfcCurve* c;
					if (!convert_to_ifc(TopoDS::Edge(exp.Current()), c, advanced)) {
						return 0;
					}
					edges->push(c);
				}

				if (edges->size() == 0) {
					return 0;
				} else if (edges->size() == 1) {
					rep = new IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(0, std::string("Axis"), std::string("Curve2D"), edges->as<IFC_NAMESPACE::IfcSchema::IfcRepresentationItem>());
				} else {
					// A geometric set is created as that probably (?) makes more sense in IFC
					IFC_NAMESPACE::IfcSchema::IfcGeometricCurveSet* curves = new IFC_NAMESPACE::IfcSchema::IfcGeometricCurveSet(edges);
					items->push(curves);
					rep = new IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(0, std::string("Axis"), std::string("GeometricCurveSet"), items->as<IFC_NAMESPACE::IfcSchema::IfcRepresentationItem>());
				}

			}
		}
	}

	IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps(new IFC_NAMESPACE::IfcSchema::IfcRepresentation::list);
	reps->push(rep);
	return new IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape(boost::none, boost::none, reps);
}

IfcUtil::IfcBaseClass* IfcGeom::MAKE_TYPE_NAME(tesselate_)(const TopoDS_Shape& shape, double deflection) {
	BRepMesh_IncrementalMesh(shape, deflection);

	IFC_NAMESPACE::IfcSchema::IfcFace::list::ptr faces(new IFC_NAMESPACE::IfcSchema::IfcFace::list);

	for (TopExp_Explorer exp(shape, TopAbs_FACE); exp.More(); exp.Next()) {
		const TopoDS_Face& face = TopoDS::Face(exp.Current());
		TopLoc_Location loc;
		Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(face, loc);

		if (!tri.IsNull()) {
            Handle(TColgp_HArray1OfPnt) nodes = tri->MapNodeArray();
			std::vector<IFC_NAMESPACE::IfcSchema::IfcCartesianPoint*> vertices;
			for (int i = 1; i <= nodes->Length(); ++i) {
				gp_Pnt pnt = nodes->Value(i).Transformed(loc);
				std::vector<double> xyz; xyz.push_back(pnt.X()); xyz.push_back(pnt.Y()); xyz.push_back(pnt.Z());
				IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* cpnt = new IFC_NAMESPACE::IfcSchema::IfcCartesianPoint(xyz);
				vertices.push_back(cpnt);
			}
            Handle(Poly_HArray1OfTriangle) triangles = tri->MapTriangleArray();
			for (int i = 1; i <= triangles->Length(); ++i) {
				int n1, n2, n3;
				triangles->Value(i).Get(n1, n2, n3);
				IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list::ptr points(new IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list);
				points->push(vertices[n1 - 1]);
				points->push(vertices[n2 - 1]);
				points->push(vertices[n3 - 1]);
				IFC_NAMESPACE::IfcSchema::IfcPolyLoop* loop = new IFC_NAMESPACE::IfcSchema::IfcPolyLoop(points);
				IFC_NAMESPACE::IfcSchema::IfcFaceOuterBound* bound = new IFC_NAMESPACE::IfcSchema::IfcFaceOuterBound(loop, face.Orientation() != TopAbs_REVERSED);
				IFC_NAMESPACE::IfcSchema::IfcFaceBound::list::ptr bounds(new IFC_NAMESPACE::IfcSchema::IfcFaceBound::list);
				bounds->push(bound);
				IFC_NAMESPACE::IfcSchema::IfcFace* face2 = new IFC_NAMESPACE::IfcSchema::IfcFace(bounds);
				faces->push(face2);
			}
		}
	}
	IFC_NAMESPACE::IfcSchema::IfcOpenShell* shell = new IFC_NAMESPACE::IfcSchema::IfcOpenShell(faces);
	IFC_NAMESPACE::IfcSchema::IfcConnectedFaceSet::list::ptr shells(new IFC_NAMESPACE::IfcSchema::IfcConnectedFaceSet::list);
	shells->push(shell);
	IFC_NAMESPACE::IfcSchema::IfcFaceBasedSurfaceModel* surface_model = new IFC_NAMESPACE::IfcSchema::IfcFaceBasedSurfaceModel(shells);

	IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps(new IFC_NAMESPACE::IfcSchema::IfcRepresentation::list);
	IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items(new IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);

	items->push(surface_model);

	IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep = new IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(
		0, std::string("Facetation"), std::string("SurfaceModel"), items);

	reps->push(rep);
	IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* shapedef = new IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape(boost::none, boost::none, reps);

	return shapedef;
}
}
