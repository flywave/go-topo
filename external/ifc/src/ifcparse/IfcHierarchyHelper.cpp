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

/********************************************************************************
 *                                                                              *
 * This class is a subclass of the regular IfcFile class that implements        *
 * several convenience functions for creating geometrical representations and   *
 * spatial containers.                                                          *
 *                                                                              *
 ********************************************************************************/

#include <time.h>

#include "../ifcparse/IfcHierarchyHelper.h"
namespace IFC_NAMESPACE{
typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* IfcHierarchyHelper::addPlacement3d(
	double ox, double oy, double oz,
	double zx, double zy, double zz,
	double xx, double xy, double xz) 
{
		typename IFC_NAMESPACE::IfcSchema::IfcDirection* x = addTriplet<typename IFC_NAMESPACE::IfcSchema::IfcDirection>(xx, xy, xz);
		typename IFC_NAMESPACE::IfcSchema::IfcDirection* z = addTriplet<typename IFC_NAMESPACE::IfcSchema::IfcDirection>(zx, zy, zz);
		typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* o = addTriplet<typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint>(ox, oy, oz);
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* p3d = new typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D(o, z, x);
		addEntity(p3d);
		return p3d;
}


typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* IfcHierarchyHelper::addPlacement2d(
	double ox, double oy,
	double xx, double xy) 
{
		typename IFC_NAMESPACE::IfcSchema::IfcDirection* x = addDoublet<typename IFC_NAMESPACE::IfcSchema::IfcDirection>(xx, xy);
		typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* o = addDoublet<typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint>(ox, oy);
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* p2d = new typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D(o, x);
		addEntity(p2d);
		return p2d;
}


typename IFC_NAMESPACE::IfcSchema::IfcLocalPlacement* IfcHierarchyHelper::addLocalPlacement(typename IFC_NAMESPACE::IfcSchema::IfcObjectPlacement* parent,
	double ox, double oy, double oz,
	double zx, double zy, double zz,
	double xx, double xy, double xz) 
{
		typename IFC_NAMESPACE::IfcSchema::IfcLocalPlacement* lp = new typename IFC_NAMESPACE::IfcSchema::IfcLocalPlacement(parent, 
			addPlacement3d(ox, oy, oz, zx, zy, zz, xx, xy, xz));

		addEntity(lp);
		return lp;
}


typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* IfcHierarchyHelper::addOwnerHistory() {
	typename IFC_NAMESPACE::IfcSchema::IfcPerson* person = new typename IFC_NAMESPACE::IfcSchema::IfcPerson(boost::none, boost::none, std::string(""), 
		boost::none, boost::none, boost::none, boost::none, boost::none);

	typename IFC_NAMESPACE::IfcSchema::IfcOrganization* organization = new typename IFC_NAMESPACE::IfcSchema::IfcOrganization(boost::none, 
		"IfcOpenShell", boost::none, boost::none, boost::none);

	typename IFC_NAMESPACE::IfcSchema::IfcPersonAndOrganization* person_and_org = new typename IFC_NAMESPACE::IfcSchema::IfcPersonAndOrganization(person, organization, boost::none);
	typename IFC_NAMESPACE::IfcSchema::IfcApplication* application = new typename IFC_NAMESPACE::IfcSchema::IfcApplication(organization, 
		IFCOPENSHELL_VERSION, "IfcOpenShell", "IfcOpenShell");

	int timestamp = (int) time(0);
	typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = new typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory(person_and_org, application, 
		boost::none, IFC_NAMESPACE::IfcSchema::IfcChangeActionEnum::IfcChangeAction_ADDED, timestamp, person_and_org, application, timestamp);

	addEntity(person);
	addEntity(organization);
	addEntity(person_and_org);
	addEntity(application);
	addEntity(owner_hist);

	return owner_hist;
}


typename IFC_NAMESPACE::IfcSchema::IfcProject* IfcHierarchyHelper::addProject(typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist) {
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext::list::ptr rep_contexts (new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext::list);

	IfcEntityList::ptr units (new IfcEntityList);
	typename IFC_NAMESPACE::IfcSchema::IfcDimensionalExponents* dimexp = new typename IFC_NAMESPACE::IfcSchema::IfcDimensionalExponents(0, 0, 0, 0, 0, 0, 0);
	typename IFC_NAMESPACE::IfcSchema::IfcSIUnit* unit1 = new typename IFC_NAMESPACE::IfcSchema::IfcSIUnit(IFC_NAMESPACE::IfcSchema::IfcUnitEnum::IfcUnit_LENGTHUNIT, 
		IFC_NAMESPACE::IfcSchema::IfcSIPrefix::IfcSIPrefix_MILLI, IFC_NAMESPACE::IfcSchema::IfcSIUnitName::IfcSIUnitName_METRE);
	typename IFC_NAMESPACE::IfcSchema::IfcSIUnit* unit2a = new typename IFC_NAMESPACE::IfcSchema::IfcSIUnit(IFC_NAMESPACE::IfcSchema::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, 
		boost::none, IFC_NAMESPACE::IfcSchema::IfcSIUnitName::IfcSIUnitName_RADIAN);
	typename IFC_NAMESPACE::IfcSchema::IfcMeasureWithUnit* unit2b = new typename IFC_NAMESPACE::IfcSchema::IfcMeasureWithUnit(
		new typename IFC_NAMESPACE::IfcSchema::IfcPlaneAngleMeasure(0.017453293), unit2a);
	typename IFC_NAMESPACE::IfcSchema::IfcConversionBasedUnit* unit2 = new typename IFC_NAMESPACE::IfcSchema::IfcConversionBasedUnit(dimexp, 
		IFC_NAMESPACE::IfcSchema::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, "Degrees", unit2b);

	units->push(unit1);
	units->push(unit2);

	typename IFC_NAMESPACE::IfcSchema::IfcUnitAssignment* unit_assignment = new typename IFC_NAMESPACE::IfcSchema::IfcUnitAssignment(units);

	typename IFC_NAMESPACE::IfcSchema::IfcProject* project = new typename IFC_NAMESPACE::IfcSchema::IfcProject(IfcParse::IfcGlobalId(), owner_hist, boost::none, boost::none, 
		boost::none, boost::none, boost::none, rep_contexts, unit_assignment);

	addEntity(dimexp);
	addEntity(unit1);
	addEntity(unit2a);
	addEntity(unit2b);
	addEntity(unit2);
	addEntity(unit_assignment);
	addEntity(project);

	return project;
}


void IfcHierarchyHelper::relatePlacements(typename IFC_NAMESPACE::IfcSchema::IfcProduct* parent, typename IFC_NAMESPACE::IfcSchema::IfcProduct* product) {
	typename IFC_NAMESPACE::IfcSchema::IfcObjectPlacement* place = product->hasObjectPlacement() ? product->ObjectPlacement() : 0;
	if (place && place->declaration().is(IFC_NAMESPACE::IfcSchema::IfcLocalPlacement::Class())) {
		typename IFC_NAMESPACE::IfcSchema::IfcLocalPlacement* local_place = (typename IFC_NAMESPACE::IfcSchema::IfcLocalPlacement*) place;
		if (parent->hasObjectPlacement()) {
			local_place->setPlacementRelTo(parent->ObjectPlacement());
		}
	}
}


typename IFC_NAMESPACE::IfcSchema::IfcSite* IfcHierarchyHelper::addSite(typename IFC_NAMESPACE::IfcSchema::IfcProject* proj, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist) {
	if (! owner_hist) {
		owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
	}
	if (! owner_hist) {
		owner_hist = addOwnerHistory();
	}
	if (! proj) {
		proj = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcProject>();
	}
	if (! proj) {
		proj = addProject(owner_hist);
	}

	typename IFC_NAMESPACE::IfcSchema::IfcSite* site = new typename IFC_NAMESPACE::IfcSchema::IfcSite(IfcParse::IfcGlobalId(), owner_hist, boost::none, 
		boost::none, boost::none, addLocalPlacement(), 0, boost::none, 
		IFC_NAMESPACE::IfcSchema::IfcElementCompositionEnum::IfcElementComposition_ELEMENT, 
		boost::none, boost::none, boost::none, boost::none, 0);

	addEntity(site);
	addRelatedObject<typename IFC_NAMESPACE::IfcSchema::IfcRelAggregates>(proj, site);
	return site;
}


typename IFC_NAMESPACE::IfcSchema::IfcBuilding* IfcHierarchyHelper::addBuilding(typename IFC_NAMESPACE::IfcSchema::IfcSite* site, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist) {
	if (! owner_hist) {
		owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
	}
	if (! owner_hist) {
		owner_hist = addOwnerHistory();
	}
	if (! site) {
		site = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcSite>();
	}
	if (! site) {
		site = addSite(0, owner_hist);
	}
	typename IFC_NAMESPACE::IfcSchema::IfcBuilding* building = new typename IFC_NAMESPACE::IfcSchema::IfcBuilding(IfcParse::IfcGlobalId(), owner_hist, boost::none, boost::none, boost::none, 
		addLocalPlacement(), 0, boost::none, IFC_NAMESPACE::IfcSchema::IfcElementCompositionEnum::IfcElementComposition_ELEMENT, 
		boost::none, boost::none, 0);

	addEntity(building);
	addRelatedObject<typename IFC_NAMESPACE::IfcSchema::IfcRelAggregates>(site, building);
	relatePlacements(site, building);

	return building;
}


typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* IfcHierarchyHelper::addBuildingStorey(typename IFC_NAMESPACE::IfcSchema::IfcBuilding* building, 
	typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist) 
{
	if (! owner_hist) {
		owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
	}
	if (! owner_hist) {
		owner_hist = addOwnerHistory();
	}
	if (! building) {
		building = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcBuilding>();
	}
	if (! building) {
		building = addBuilding(0, owner_hist);
	}
	typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* storey = new typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey(IfcParse::IfcGlobalId(), 
		owner_hist, boost::none, boost::none, boost::none, addLocalPlacement(), 0, boost::none, 
		IFC_NAMESPACE::IfcSchema::IfcElementCompositionEnum::IfcElementComposition_ELEMENT, boost::none);

	addEntity(storey);
	addRelatedObject<typename IFC_NAMESPACE::IfcSchema::IfcRelAggregates>(building, storey);
	relatePlacements(building, storey);

	return storey;
}


typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* IfcHierarchyHelper::addBuildingProduct(typename IFC_NAMESPACE::IfcSchema::IfcProduct* product, 
	typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* storey, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist) 
{
	if (! owner_hist) {
		owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
	}
	if (! owner_hist) {
		owner_hist = addOwnerHistory();
	}
	if (! storey) {
		storey = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey>();
	}
	if (! storey) {
		storey = addBuildingStorey(0, owner_hist);
	}
	addEntity(product);

	// CV-2x3-158: Don't add decompositions directly to a building storey
	const bool is_decomposition = product->Decomposes()->size() > 0;

	if (!is_decomposition) {
		addRelatedObject<typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure>(storey, product);
		relatePlacements(storey, product);
	}
	return storey;
}


void IfcHierarchyHelper::addExtrudedPolyline(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, const std::vector<std::pair<double, double> >& points, double h, 
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* /*place*/, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2, 
	typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* /*context*/) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list::ptr cartesian_points (new typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list);
	for (std::vector<std::pair<double, double> >::const_iterator i = points.begin(); i != points.end(); ++i) {
		cartesian_points->push(addDoublet<typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint>(i->first, i->second));
	}
	if (cartesian_points->size()) cartesian_points->push(*cartesian_points->begin());
	typename IFC_NAMESPACE::IfcSchema::IfcPolyline* line = new typename IFC_NAMESPACE::IfcSchema::IfcPolyline(cartesian_points);
	typename IFC_NAMESPACE::IfcSchema::IfcArbitraryClosedProfileDef* profile = new typename IFC_NAMESPACE::IfcSchema::IfcArbitraryClosedProfileDef(
		IFC_NAMESPACE::IfcSchema::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, line);

	typename IFC_NAMESPACE::IfcSchema::IfcExtrudedAreaSolid* solid = new typename IFC_NAMESPACE::IfcSchema::IfcExtrudedAreaSolid(
		profile, place2 ? place2 : addPlacement3d(), dir ? dir : addTriplet<typename IFC_NAMESPACE::IfcSchema::IfcDirection>(0, 0, 1), h);

	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items = rep->Items();
	items->push(solid);
	rep->setItems(items);

	addEntity(line);
	addEntity(profile);
	addEntity(solid);
}


typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* IfcHierarchyHelper::addExtrudedPolyline(const std::vector<std::pair<double, double> >& points, double h, 
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2, typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir, 
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps (new typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list);
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items (new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep = new typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(context 
		? context 
		: getRepresentationContext("Model"), std::string("Body"), std::string("SweptSolid"), items);
	reps->push(rep);
	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* shape = new typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape(boost::none, boost::none, reps);
	addEntity(rep);
	addEntity(shape);
	addExtrudedPolyline(rep, points, h, place, place2, dir, context);

	return shape;
}


void IfcHierarchyHelper::addBox(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, double w, double d, double h, 
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2, 
	typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context) 
{
	if (false) { // TODO What's this?
		typename IFC_NAMESPACE::IfcSchema::IfcRectangleProfileDef* profile = new typename IFC_NAMESPACE::IfcSchema::IfcRectangleProfileDef(
			IFC_NAMESPACE::IfcSchema::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, place ? place : addPlacement2d(), w, d);
		typename IFC_NAMESPACE::IfcSchema::IfcExtrudedAreaSolid* solid = new typename IFC_NAMESPACE::IfcSchema::IfcExtrudedAreaSolid(profile, 
			place2 ? place2 : addPlacement3d(), dir ? dir : addTriplet<typename IFC_NAMESPACE::IfcSchema::IfcDirection>(0, 0, 1), h);

		addEntity(profile);
		addEntity(solid);
		typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items = rep->Items();
		items->push(solid);
		rep->setItems(items);
	} else {
		std::vector<std::pair<double, double> > points;
		points.push_back(std::make_pair(-w/2, -d/2));
		points.push_back(std::make_pair(w/2, -d/2));
		points.push_back(std::make_pair(w/2, d/2));
		points.push_back(std::make_pair(-w/2, d/2));
		// The call to addExtrudedPolyline() closes the polyline
		addExtrudedPolyline(rep, points, h, place, place2, dir, context);
	}
}


void IfcHierarchyHelper::addAxis(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, double l, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* /*context*/) {
	typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p1 = addDoublet<typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint>(-l / 2., 0.);
	typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint* p2 = addDoublet<typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint>(+l / 2., 0.);
	typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list::ptr pts(new typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint::list);
	pts->push(p1); pts->push(p2);
	typename IFC_NAMESPACE::IfcSchema::IfcPolyline* poly = new typename IFC_NAMESPACE::IfcSchema::IfcPolyline(pts);
	addEntity(poly);
	
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items = rep->Items();
	items->push(poly);
	rep->setItems(items);
}


typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* IfcHierarchyHelper::addBox(double w, double d, double h, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place, 
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2, typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps (new typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list);
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items (new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);		
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep = new typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(
		context ? context : getRepresentationContext("Model"), std::string("Body"), std::string("SweptSolid"), items);
	reps->push(rep);
	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* shape = new typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape(boost::none, boost::none, reps);
	addEntity(rep);
	addEntity(shape);
	addBox(rep, w, d, h, place, place2, dir, context);
	return shape;
}


typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* IfcHierarchyHelper::addAxisBox(double w, double d, double h, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps(new typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list);
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr body_items(new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr axis_items(new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* body_rep = new typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(
		context ? context : getRepresentationContext("Model"), std::string("Body"), std::string("SweptSolid"), body_items);

	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* axis_rep = new typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(
		context ? context : getRepresentationContext("Plan"), std::string("Axis"), std::string("Curve2D"), axis_items);

	reps->push(axis_rep);
	reps->push(body_rep);

	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* shape = new typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape(boost::none, boost::none, reps);
	addEntity(shape);
	addEntity(body_rep);
	addBox(body_rep, w, d, h, 0, 0, 0, context);
	addEntity(axis_rep);
	addAxis(axis_rep, w);
	
	return shape;
}


void IfcHierarchyHelper::clipRepresentation(typename IFC_NAMESPACE::IfcSchema::IfcProductRepresentation* shape, 
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place, bool agree) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps = shape->Representations();
	for (typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::it j = reps->begin(); j != reps->end(); ++j) {
		clipRepresentation(*j, place, agree);
	}
}


void IfcHierarchyHelper::clipRepresentation(typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* rep, 
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place, bool agree) 
{
	if (rep->RepresentationIdentifier() != "Body") return;
	typename IFC_NAMESPACE::IfcSchema::IfcPlane* plane = new typename IFC_NAMESPACE::IfcSchema::IfcPlane(place);
	typename IFC_NAMESPACE::IfcSchema::IfcHalfSpaceSolid* half_space = new typename IFC_NAMESPACE::IfcSchema::IfcHalfSpaceSolid(plane, agree);
	addEntity(plane);
	addEntity(half_space);
	rep->setRepresentationType("Clipping");		
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items = rep->Items();
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr new_items (new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);
	for (typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::it i = items->begin(); i != items->end(); ++i) {
		typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem* item = *i;
		typename IFC_NAMESPACE::IfcSchema::IfcBooleanClippingResult* clip = new typename IFC_NAMESPACE::IfcSchema::IfcBooleanClippingResult(
			IFC_NAMESPACE::IfcSchema::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE, item, half_space);
		addEntity(clip);
		new_items->push(clip);
	}
	rep->setItems(new_items);
}


typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* IfcHierarchyHelper::addStyleAssignment(double r, double g, double b, double a) {
	typename IFC_NAMESPACE::IfcSchema::IfcColourRgb* colour = new typename IFC_NAMESPACE::IfcSchema::IfcColourRgb(boost::none, r, g, b);
	typename IFC_NAMESPACE::IfcSchema::IfcSurfaceStyleRendering* rendering = a == 1.0
		? new typename IFC_NAMESPACE::IfcSchema::IfcSurfaceStyleRendering(colour, boost::none, 0, 0, 0, 0, 
			0, 0, IFC_NAMESPACE::IfcSchema::IfcReflectanceMethodEnum::IfcReflectanceMethod_FLAT)
		: new typename IFC_NAMESPACE::IfcSchema::IfcSurfaceStyleRendering(colour, 1.0-a, 0, 0, 0, 0, 
			0, 0, IFC_NAMESPACE::IfcSchema::IfcReflectanceMethodEnum::IfcReflectanceMethod_FLAT);

	IfcEntityList::ptr styles(new IfcEntityList());
	styles->push(rendering);
	typename IFC_NAMESPACE::IfcSchema::IfcSurfaceStyle* surface_style = new typename IFC_NAMESPACE::IfcSchema::IfcSurfaceStyle(
		boost::none, IFC_NAMESPACE::IfcSchema::IfcSurfaceSide::IfcSurfaceSide_BOTH, styles);
	IfcEntityList::ptr surface_styles(new IfcEntityList());
	surface_styles->push(surface_style);
	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment = 
		new typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment(surface_styles);
	addEntity(colour);
	addEntity(rendering);
	addEntity(surface_style);
	addEntity(style_assignment);
	return style_assignment;
}


typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* IfcHierarchyHelper::setSurfaceColour(
	typename IFC_NAMESPACE::IfcSchema::IfcProductRepresentation* shape, double r, double g, double b, double a) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment = addStyleAssignment(r, g, b, a);
	setSurfaceColour(shape, style_assignment);
	return style_assignment;
}


typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* IfcHierarchyHelper::setSurfaceColour(
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* shape, double r, double g, double b, double a) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment = addStyleAssignment(r, g, b, a);
	setSurfaceColour(shape, style_assignment);
	return style_assignment;
}


void IfcHierarchyHelper::setSurfaceColour(typename IFC_NAMESPACE::IfcSchema::IfcProductRepresentation* shape, 
	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr reps = shape->Representations();
	for (typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::it j = reps->begin(); j != reps->end(); ++j) {
		setSurfaceColour(*j, style_assignment);
	}
}
#ifdef USE_23
IFC_NAMESPACE::IfcSchema::IfcStyledItem* create_styled_item(IFC_NAMESPACE::IfcSchema::IfcRepresentationItem* item, IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment) {
	IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment::list::ptr style_assignments(new IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment::list);
	style_assignments->push(style_assignment);
	return new IFC_NAMESPACE::IfcSchema::IfcStyledItem(item, style_assignments, boost::none);
}
#else
IFC_NAMESPACE::IfcSchema::IfcStyledItem* create_styled_item(IFC_NAMESPACE::IfcSchema::IfcRepresentationItem* item, IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment) {
  IfcEntityList::ptr style_assignments(new IfcEntityList);
  style_assignments->push(style_assignment);
  return new IFC_NAMESPACE::IfcSchema::IfcStyledItem(item, style_assignments, boost::none);
}
#endif
 

void IfcHierarchyHelper::setSurfaceColour(typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* rep, 
	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment) 
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items = rep->Items();
	for (typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::it i = items->begin(); i != items->end(); ++i) {
		typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem* item = *i;
		typename IFC_NAMESPACE::IfcSchema::IfcStyledItem* styled_item = create_styled_item(item, style_assignment);
		addEntity(styled_item);
	}
}


typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* IfcHierarchyHelper::addMappedItem(
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, 
	typename IFC_NAMESPACE::IfcSchema::IfcCartesianTransformationOperator3D* transform,
	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* def)
{
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationMap::list::ptr maps = rep->RepresentationMap();
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationMap* map;
	if (maps->size() == 1) {
		map = *maps->begin();
	} else {
		map = new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationMap(addPlacement3d(), rep);
		addEntity(map);
	}

	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list::ptr representations(new typename IFC_NAMESPACE::IfcSchema::IfcRepresentation::list);
	if (def) representations = def->Representations();

	if (!transform) {
		transform = new typename IFC_NAMESPACE::IfcSchema::IfcCartesianTransformationOperator3D(0, 0, addTriplet<typename IFC_NAMESPACE::IfcSchema::IfcCartesianPoint>(0,0,0), boost::none, 0);
		addEntity(transform);
	}
	typename IFC_NAMESPACE::IfcSchema::IfcMappedItem* item = new typename IFC_NAMESPACE::IfcSchema::IfcMappedItem(map, transform);
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items(new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);
	items->push(item);
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* new_rep = new typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(rep->ContextOfItems(), boost::none, std::string("MappedRepresentation"), items);
	if (rep->hasRepresentationIdentifier()) {
		new_rep->setRepresentationIdentifier(rep->RepresentationIdentifier());
	}	
	addEntity(item);
	addEntity(new_rep);
	representations->push(new_rep);
	if (!def) {
		def = new typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape(boost::none, boost::none, representations);
		addEntity(def);
	} else {
		def->setRepresentations(representations);
	}
	return def;
}


typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* IfcHierarchyHelper::addMappedItem(
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation::list::ptr reps, 
	typename IFC_NAMESPACE::IfcSchema::IfcCartesianTransformationOperator3D* transform)
{
	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* def = 0;
	for (typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation::list::it it = reps->begin(); it != reps->end(); ++it) {
		def = addMappedItem(*it, transform, def);
	}
	return def;
}


typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* IfcHierarchyHelper::addEmptyRepresentation(const std::string& repid, const std::string& reptype) {
	typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list::ptr items(new typename IFC_NAMESPACE::IfcSchema::IfcRepresentationItem::list);
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* shape_rep = new typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation(getRepresentationContext(reptype == "Curve2D" ? "Plan" : "Model"), repid, reptype, items);
	addEntity(shape_rep);
	return shape_rep;
}


typename IFC_NAMESPACE::IfcSchema::IfcGeometricRepresentationContext* IfcHierarchyHelper::getRepresentationContext(const std::string& s) {
	typename std::map<std::string, typename IFC_NAMESPACE::IfcSchema::IfcGeometricRepresentationContext*>::const_iterator it = contexts.find(s);
	if (it != contexts.end()) return it->second;
	else {
		typename IFC_NAMESPACE::IfcSchema::IfcProject* project = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcProject>();
		if (!project) {
			project = addProject();
		}
		typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext::list::ptr project_contexts = project->RepresentationContexts();
		typename IFC_NAMESPACE::IfcSchema::IfcGeometricRepresentationContext* context = new typename IFC_NAMESPACE::IfcSchema::IfcGeometricRepresentationContext(
			boost::none, s, 3, 1e-5, addPlacement3d(), addDoublet<typename IFC_NAMESPACE::IfcSchema::IfcDirection>(0, 1));
		addEntity(context);
		project_contexts->push(context);
		project->setRepresentationContexts(project_contexts);
		return contexts[s] = context;
	}
}

//template IFC_PARSE_API class IfcHierarchyHelper<IfcSchema>;
}
