#include "Serialization.h"

#include <boost/algorithm/string/case_conv.hpp>
namespace IFC_NAMESPACE {

namespace IfcGeom {
	extern IfcUtil::IfcBaseClass* MAKE_TYPE_NAME(tesselate_)(const TopoDS_Shape& shape, double deflection);
	// extern IfcUtil::IfcBaseClass* tesselate_Ifc4(const TopoDS_Shape& shape, double deflection);
	// extern IfcUtil::IfcBaseClass* tesselate_Ifc4x1(const TopoDS_Shape& shape, double deflection);
	// extern IfcUtil::IfcBaseClass* tesselate_Ifc4x2(const TopoDS_Shape& shape, double deflection);
	// extern IfcUtil::IfcBaseClass* tesselate_Ifc4x3_rc1(const TopoDS_Shape& shape, double deflection);

	extern IfcUtil::IfcBaseClass* MAKE_TYPE_NAME(serialise_)(const TopoDS_Shape& shape, bool advanced);
	// extern IfcUtil::IfcBaseClass* serialise_Ifc4(const TopoDS_Shape& shape, bool advanced);
	// extern IfcUtil::IfcBaseClass* serialise_Ifc4x1(const TopoDS_Shape& shape, bool advanced);
	// extern IfcUtil::IfcBaseClass* serialise_Ifc4x2(const TopoDS_Shape& shape, bool advanced);
	// extern IfcUtil::IfcBaseClass* serialise_Ifc4x3_rc1(const TopoDS_Shape& shape, bool advanced);
}

template <typename Fn, typename T>
IfcUtil::IfcBaseClass* execute_based_on_schema(Fn fn, const std::string& schema_name, const TopoDS_Shape& shape, T t) {
	// // @todo an ugly hack to guarantee schemas are initialised.
	// try {
	// 	IfcParse::schema_by_name("IFC2X3");
	// } catch (IfcParse::IfcException&) {}

	// const std::string schema_name_lower = boost::to_lower_copy(schema_name);

	// if (schema_name_lower == "ifc2x3") {
	// 	return fn_2x3(shape, t);
	// } else if (schema_name_lower == "ifc4") {
	// 	return fn_4(shape, t);
	// } else if (schema_name_lower == "ifc4x1") {
	// 	return fn_4x1(shape, t);
	// } else if (schema_name_lower == "ifc4x2") {
	// 	return fn_4x2(shape, t);
	// } else if (schema_name_lower == "ifc4x3_rc1") {
	// 	return fn_4x3_rc1(shape, t);
	// } else {
	// 	throw IfcParse::IfcException("No geometry serialization available for " + schema_name);
	// }
	return fn(shape, t);
}

IfcUtil::IfcBaseClass* IfcGeom::tesselate(const std::string& schema_name, const TopoDS_Shape& shape, double deflection) {
	return execute_based_on_schema(MAKE_TYPE_NAME(tesselate_), schema_name, shape, deflection);
}

IfcUtil::IfcBaseClass* IfcGeom::serialise(const std::string& schema_name, const TopoDS_Shape& shape, bool advanced) {
	return execute_based_on_schema(MAKE_TYPE_NAME(serialise_), schema_name, shape, advanced);
}
}
