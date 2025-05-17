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

taxonomy::ptr mapping::map_impl(const IfcSchema::IfcSphere* inst) {
	auto sol = taxonomy::make<taxonomy::solid>();
	auto shl = taxonomy::make<taxonomy::shell>();
	auto fac = taxonomy::make<taxonomy::face>();
	auto spr = taxonomy::make<taxonomy::sphere>();
	spr->matrix = taxonomy::cast<taxonomy::matrix4>(map(inst->Position()));
	spr->radius = inst->Radius() * length_unit_;
	fac->basis = spr;
	shl->children.push_back(fac);
	sol->children.push_back(shl);
	return sol;
}
