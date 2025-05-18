#ifndef IFCALIGNMENTHELPER_H
#define IFCALIGNMENTHELPER_H

#include <ifcparse/IfcLogger.h>
#include <ifcparse/ifc_parse_api.h>

#ifdef HAS_SCHEMA_4x3_add2
#include <ifcparse/Ifc4x3_add2.h>
#endif

#include <ifcparse/IfcHierarchyHelper.h>

#ifdef HAS_SCHEMA_4x3_add2
//
// alignment helper methods
//

// creates a horizontal alignment from a list of PI points and curve radii. if
// include_geometry is true, the geometric representations are created,
// otherwise only business logic is created
IFC_PARSE_API Ifc4x3_add2::IfcAlignment *addHorizontalAlignment(
    IfcHierarchyHelper<Ifc4x3_add2> &file, const std::string &alignment_name,
    const std::vector<std::pair<double, double>> &points,
    const std::vector<double> &radii, bool include_geometry = true);

// creates a horizontal and vertical alignment from a list of PI points, curve
// radii, and VPI points and vertical curve lengths. if include_geometry is
// true, the geometric representations are created, otherwise only business
// logic is created
IFC_PARSE_API Ifc4x3_add2::IfcAlignment *
addAlignment(IfcHierarchyHelper<Ifc4x3_add2> &file,
             const std::string &alignment_name,
             const std::vector<std::pair<double, double>> &points,
             const std::vector<double> &radii,
             const std::vector<std::pair<double, double>> &vpoints,
             const std::vector<double> &vclength, bool include_geometry = true);

// Maps horizontal alignment business logic to geometry.
// Bloss curves have two geometry elements for one horizontal alignment segment.
// That is the reason for returning a pair. Typically the first element of the
// pair will have the geometry and the second element will be nullptr
IFC_PARSE_API
    std::pair<Ifc4x3_add2::IfcCurveSegment *, Ifc4x3_add2::IfcCurveSegment *>
    mapAlignmentSegment(const Ifc4x3_add2::IfcAlignmentSegment *segment);
IFC_PARSE_API
    std::pair<Ifc4x3_add2::IfcCurveSegment *, Ifc4x3_add2::IfcCurveSegment *>
    mapAlignmentHorizontalSegment(
        const Ifc4x3_add2::IfcAlignmentHorizontalSegment *segment);
IFC_PARSE_API
    std::pair<Ifc4x3_add2::IfcCurveSegment *, Ifc4x3_add2::IfcCurveSegment *>
    mapAlignmentVerticalSegment(
        const Ifc4x3_add2::IfcAlignmentVerticalSegment *segment);
IFC_PARSE_API
    std::pair<Ifc4x3_add2::IfcCurveSegment *, Ifc4x3_add2::IfcCurveSegment *>
    mapAlignmentCantSegment(
        const Ifc4x3_add2::IfcAlignmentCantSegment *segment);
#endif

#endif