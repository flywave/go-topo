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

#include "IfcSIPrefix.h"
 
#ifndef INCLUDE_PARENT_DIR
#define INCLUDE_PARENT_DIR(x) STRINGIFY(../ifcparse/x.h)
#include INCLUDE_PARENT_DIR(IfcSchema)
#endif
#undef INCLUDE_PARENT_DIR

namespace IFC_NAMESPACE{

double IfcParse::IfcSIPrefixToValue(const std::string& v) {
	if      ( v == "EXA"   ) return 1.e18;
	else if ( v == "PETA"  ) return 1.e15;
	else if ( v == "TERA"  ) return 1.e12;
	else if ( v == "GIGA"  ) return 1.e9;
	else if ( v == "MEGA"  ) return 1.e6;
	else if ( v == "KILO"  ) return 1.e3;
	else if ( v == "HECTO" ) return 1.e2;
	else if ( v == "DECA"  ) return 1.;
	else if ( v == "DECI"  ) return 1.e-1;
	else if ( v == "CENTI" ) return 1.e-2;
	else if ( v == "MILLI" ) return 1.e-3;
	else if ( v == "MICRO" ) return 1.e-6;
	else if ( v == "NANO"  ) return 1.e-9;
	else if ( v == "PICO"  ) return 1.e-12;
	else if ( v == "FEMTO" ) return 1.e-15;
	else if ( v == "ATTO"  ) return 1.e-18;
	else return 1.;
}

double IfcParse::get_SI_equivalent(typename IFC_NAMESPACE::IfcSchema::IfcNamedUnit* named_unit) {
	double scale =  1.;
	typename IFC_NAMESPACE::IfcSchema::IfcSIUnit* si_unit = 0;

	if (named_unit->declaration().is(IFC_NAMESPACE::IfcSchema::IfcConversionBasedUnit::Class())) {
		typename IFC_NAMESPACE::IfcSchema::IfcConversionBasedUnit* conv_unit = named_unit->template as<typename IFC_NAMESPACE::IfcSchema::IfcConversionBasedUnit>();
		typename IFC_NAMESPACE::IfcSchema::IfcMeasureWithUnit* factor = conv_unit->ConversionFactor();
		typename IFC_NAMESPACE::IfcSchema::IfcUnit* component = factor->UnitComponent();
		if (component->declaration().is(IFC_NAMESPACE::IfcSchema::IfcSIUnit::Class())) {
			si_unit = component->template as<typename IFC_NAMESPACE::IfcSchema::IfcSIUnit>();
			typename IFC_NAMESPACE::IfcSchema::IfcValue* v = factor->ValueComponent();
			scale = *v->data().getArgument(0);
		}		
	} else if (named_unit->declaration().is(IFC_NAMESPACE::IfcSchema::IfcSIUnit::Class())) {
		si_unit = named_unit->template as<typename IFC_NAMESPACE::IfcSchema::IfcSIUnit>();
	}
	if (si_unit) {
		if (si_unit->hasPrefix()) {
			scale *= IfcSIPrefixToValue(IFC_NAMESPACE::IfcSchema::IfcSIPrefix::ToString(si_unit->Prefix()));
		}
	} else {
		scale = 0.;
	}

	return scale;
}
}
// #if defined(_MSC_VER) && _MSC_VER < 1900
// template double IfcParse::get_SI_equivalent<Ifc2x3>(Ifc2x3::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4>(Ifc4::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4x1>(Ifc4x1::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4x2>(Ifc4x2::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4x3_rc1>(Ifc4x3_rc1::IfcNamedUnit* named_unit);
// #else
// template double IfcParse::get_SI_equivalent<Ifc2x3>(typename Ifc2x3::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4>(typename Ifc4::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4x1>(typename Ifc4x1::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4x2>(typename Ifc4x2::IfcNamedUnit* named_unit);
// template double IfcParse::get_SI_equivalent<Ifc4x3_rc1>(typename Ifc4x3_rc1::IfcNamedUnit* named_unit);
// #endif
