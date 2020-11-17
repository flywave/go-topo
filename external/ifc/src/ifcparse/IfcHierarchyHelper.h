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

#ifndef IFCHIERARCHYHELPER_H
#define IFCHIERARCHYHELPER_H

#include <map>

#include "ifc_parse_api.h"

#ifndef INCLUDE_PARENT_DIR
#define INCLUDE_PARENT_DIR(x) STRINGIFY(../ifcparse/x.h)
#include INCLUDE_PARENT_DIR(IfcSchema)
#endif
#undef INCLUDE_PARENT_DIR


#include "../ifcparse/IfcFile.h"
#include "../ifcparse/IfcWrite.h"
#include "../ifcparse/IfcGlobalId.h"

namespace {
	IFC_NAMESPACE::IfcUtil::IfcBaseClass* get_parent_of_relation(IFC_NAMESPACE::IfcUtil::IfcBaseClass* t) {
		return *t->data().getArgument(
			t->declaration().as_entity()->attribute_index("RelatingObject")
		);
	}

	// Ifc4x1::IfcObjectDefinition* get_parent_of_relation(Ifc4x1::IfcRelContainedInSpatialStructure* t) {
	// 	return t->RelatingStructure();
	// }

	// Ifc4x2::IfcObjectDefinition* get_parent_of_relation(Ifc4x2::IfcRelContainedInSpatialStructure* t) {
	// 	return t->RelatingStructure();
	// }

	// Ifc4x3_rc1::IfcObjectDefinition* get_parent_of_relation(Ifc4x3_rc1::IfcRelContainedInSpatialStructure* t) {
	// 	return t->RelatingStructure();
	// }

	IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(IFC_NAMESPACE::IfcUtil::IfcBaseClass* t) {
		return *t->data().getArgument(
			t->declaration().as_entity()->attribute_index("RelatedElements")
			);
	}


	// IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc4x1::IfcRelContainedInSpatialStructure* t) {
	// 	return t->RelatedElements()->generalize();
	// }

	// IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc4x2::IfcRelContainedInSpatialStructure* t) {
	// 	return t->RelatedElements()->generalize();
	// }

	// IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc4x3_rc1::IfcRelContainedInSpatialStructure* t) {
	// 	return t->RelatedElements()->generalize();
	// }

//  	Ifc2x3::IfcObjectDefinition* get_parent_of_relation(Ifc2x3::IfcRelContainedInSpatialStructure* t) {
// 		return t->RelatingStructure();
// 	}
 	
// 	IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc2x3::IfcRelContainedInSpatialStructure* t) {
// 	return t->RelatedElements()->generalize();
// }
  
// 	IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc2x3::IfcRelAggregates* t) {
// 		return t->RelatedObjects()->generalize();
// 	}
 
	IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* get_parent_of_relation(IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure* t) {
		return t->RelatingStructure();
	}
	IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure* t) {
		return t->RelatedElements()->generalize();
	}
	IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(IFC_NAMESPACE::IfcSchema::IfcRelAggregates* t) {
		return t->RelatedObjects()->generalize();
	} 

	// IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc4x1::IfcRelAggregates* t) {
	// 	return t->RelatedObjects()->generalize();
	// }

	// IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc4x2::IfcRelAggregates* t) {
	// 	return t->RelatedObjects()->generalize();
	// }

	// IFC_NAMESPACE::IfcEntityList::ptr get_children_of_relation(Ifc4x3_rc1::IfcRelAggregates* t) {
	// 	return t->RelatedObjects()->generalize();
	// }

	void set_children_of_relation(IFC_NAMESPACE::IfcUtil::IfcBaseClass* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
		IFC_NAMESPACE::IfcWrite::IfcWriteArgument* attr = new IFC_NAMESPACE::IfcWrite::IfcWriteArgument;
		attr->set(cs);
		t->data().setArgument(
			t->declaration().as_entity()->attribute_index("RelatedElements"),
			attr
		);
	}

	void set_children_of_relation(IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
		t->setRelatedElements(cs->as<IFC_NAMESPACE::IfcSchema::IfcProduct>());
	}

	// void set_children_of_relation(Ifc4::IfcRelContainedInSpatialStructure* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedElements(cs->as<Ifc4::IfcProduct>());
	// }
	
	// void set_children_of_relation(Ifc4x1::IfcRelContainedInSpatialStructure* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedElements(cs->as<Ifc4x1::IfcProduct>());
	// }

	// void set_children_of_relation(Ifc4x2::IfcRelContainedInSpatialStructure* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedElements(cs->as<Ifc4x2::IfcProduct>());
	// }

	// void set_children_of_relation(Ifc4x3_rc1::IfcRelContainedInSpatialStructure* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedElements(cs->as<Ifc4x3_rc1::IfcProduct>());
	// }

	void set_children_of_relation(IFC_NAMESPACE::IfcSchema::IfcRelAggregates* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
		t->setRelatedObjects(cs->as<IFC_NAMESPACE::IfcSchema::IfcObjectDefinition>());
	}

 

	// void set_children_of_relation(Ifc4x1::IfcRelAggregates* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedObjects(cs->as<Ifc4x1::IfcObjectDefinition>());
	// }

	// void set_children_of_relation(Ifc4x2::IfcRelAggregates* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedObjects(cs->as<Ifc4x2::IfcObjectDefinition>());
	// }

	// void set_children_of_relation(Ifc4x3_rc1::IfcRelAggregates* t, IFC_NAMESPACE::IfcEntityList::ptr& cs) {
	// 	t->setRelatedObjects(cs->as<Ifc4x3_rc1::IfcObjectDefinition>());
	// }
}
namespace IFC_NAMESPACE{
class IFC_PARSE_API IfcHierarchyHelper : public IfcParse::IfcFile {
public:
	IfcHierarchyHelper() : IfcParse::IfcFile(&IFC_NAMESPACE::IfcSchema::get_schema()) {}

	template <class T> 
	T* addTriplet(double x, double y, double z) {
		std::vector<double> a; a.push_back(x); a.push_back(y); a.push_back(z);
		T* t = new T(a);
		addEntity(t);
		return t;
	}

	template <class T> 
	T* addDoublet(double x, double y) {
		std::vector<double> a; a.push_back(x); a.push_back(y);
		T* t = new T(a);
		addEntity(t);
		return t;
	}

	template <class T>
	T* getSingle() {
		typename T::list::ptr ts = instances_by_type<T>();
		if (ts->size() != 1) return 0;
		return *ts->begin();
	}
	
	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* addPlacement3d(double ox=0.0, double oy=0.0, double oz=0.0,
		double zx=0.0, double zy=0.0, double zz=1.0,
		double xx=1.0, double xy=0.0, double xz=0.0);

	typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* addPlacement2d(double ox=0.0, double oy=0.0,
		double xx=1.0, double xy=0.0);

	typename IFC_NAMESPACE::IfcSchema::IfcLocalPlacement* addLocalPlacement(typename IFC_NAMESPACE::IfcSchema::IfcObjectPlacement* parent = 0,
		double ox=0.0, double oy=0.0, double oz=0.0,
		double zx=0.0, double zy=0.0, double zz=1.0,
		double xx=1.0, double xy=0.0, double xz=0.0);

	template <class T>
	void addRelatedObject(typename IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* relating_object, 
		typename IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* related_object, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = 0)
	{
		typename T::list::ptr li = instances_by_type<T>();
		bool found = false;
		for (typename T::list::it i = li->begin(); i != li->end(); ++i) {
			T* rel = *i;
            try {
                if (get_parent_of_relation(rel) == relating_object) {
                    IFC_NAMESPACE::IfcEntityList::ptr products = get_children_of_relation(rel);
                    products->push(related_object);
                    set_children_of_relation(rel, products);
                    found = true;
                    break;
                }
            } catch (std::exception& e) {
				Logger::Error(e);
			} catch (...) {
				Logger::Error("Unknown error in addRelatedObject()");
			}
		}
		if (! found) {
			if (! owner_hist) {
				owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
			}
			if (! owner_hist) {
				owner_hist = addOwnerHistory();
			}

			IFC_NAMESPACE::IfcEntityList::ptr related_objects (new IFC_NAMESPACE::IfcEntityList);
			related_objects->push(related_object);

			IfcEntityInstanceData* data = new IfcEntityInstanceData(&T::Class());
			{ IFC_NAMESPACE::IfcWrite::IfcWriteArgument* attr = new IFC_NAMESPACE::IfcWrite::IfcWriteArgument(); attr->set<std::string>(IfcParse::IfcGlobalId()); data->setArgument(0, attr); }
			{ IFC_NAMESPACE::IfcWrite::IfcWriteArgument* attr = new IFC_NAMESPACE::IfcWrite::IfcWriteArgument(); attr->set(owner_hist); data->setArgument(1, attr); }
			int relating_index = 4, related_index = 5;
			if (T::Class().name() == "IfcRelContainedInSpatialStructure") {
				// IfcRelContainedInSpatialStructure has attributes reversed.
				std::swap(relating_index, related_index);
			}
			{ IFC_NAMESPACE::IfcWrite::IfcWriteArgument* attr = new IFC_NAMESPACE::IfcWrite::IfcWriteArgument(); attr->set(relating_object); data->setArgument(relating_index, attr); }
			{ IFC_NAMESPACE::IfcWrite::IfcWriteArgument* attr = new IFC_NAMESPACE::IfcWrite::IfcWriteArgument(); attr->set(related_objects); data->setArgument(related_index, attr); }
			
			T* t = (T*)IFC_NAMESPACE::IfcSchema::get_schema().instantiate(data);
			addEntity(t);
		}
	}

	typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* addOwnerHistory();	
	typename IFC_NAMESPACE::IfcSchema::IfcProject* addProject(typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = 0);
	void relatePlacements(typename IFC_NAMESPACE::IfcSchema::IfcProduct* parent, typename IFC_NAMESPACE::IfcSchema::IfcProduct* product);	
	typename IFC_NAMESPACE::IfcSchema::IfcSite* addSite(typename IFC_NAMESPACE::IfcSchema::IfcProject* proj = 0, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = 0);	
	typename IFC_NAMESPACE::IfcSchema::IfcBuilding* addBuilding(typename IFC_NAMESPACE::IfcSchema::IfcSite* site = 0, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = 0);

	typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* addBuildingStorey(typename IFC_NAMESPACE::IfcSchema::IfcBuilding* building = 0, 
		typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = 0);

	typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* addBuildingProduct(typename IFC_NAMESPACE::IfcSchema::IfcProduct* product, 
		typename IFC_NAMESPACE::IfcSchema::IfcBuildingStorey* storey = 0, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist = 0);

	void addExtrudedPolyline(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, const std::vector<std::pair<double, double> >& points, double h, 
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place=0, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2=0, 
		typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir=0, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context=0);

	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* addExtrudedPolyline(const std::vector<std::pair<double, double> >& points, double h, 
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place=0, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2=0, typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir=0, 
		typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context=0);

	void addBox(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, double w, double d, double h, 
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place=0, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2=0, 
		typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir=0, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context=0);

	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* addBox(double w, double d, double h, typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement2D* place=0, 
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place2=0, typename IFC_NAMESPACE::IfcSchema::IfcDirection* dir=0, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context=0);

	void addAxis(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* rep, double l, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context=0);

	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* addAxisBox(double w, double d, double h, typename IFC_NAMESPACE::IfcSchema::IfcRepresentationContext* context=0);

	void clipRepresentation(typename IFC_NAMESPACE::IfcSchema::IfcProductRepresentation* shape, 
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place, bool agree);

	void clipRepresentation(typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* shape, 
		typename IFC_NAMESPACE::IfcSchema::IfcAxis2Placement3D* place, bool agree);

	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* addStyleAssignment(double r, double g, double b, double a=1.0);

	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* setSurfaceColour(typename IFC_NAMESPACE::IfcSchema::IfcProductRepresentation* shape, 
		double r, double g, double b, double a=1.0);

	typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* setSurfaceColour(typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* shape, 
		double r, double g, double b, double a=1.0);

	void setSurfaceColour(typename IFC_NAMESPACE::IfcSchema::IfcProductRepresentation* shape, 
		typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment);

	void setSurfaceColour(typename IFC_NAMESPACE::IfcSchema::IfcRepresentation* shape, 
		typename IFC_NAMESPACE::IfcSchema::IfcPresentationStyleAssignment* style_assignment);

	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* addMappedItem(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation*, 
		typename IFC_NAMESPACE::IfcSchema::IfcCartesianTransformationOperator3D* transform = 0,
		typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* def = 0);

	typename IFC_NAMESPACE::IfcSchema::IfcProductDefinitionShape* addMappedItem(typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation::list::ptr, 
		typename IFC_NAMESPACE::IfcSchema::IfcCartesianTransformationOperator3D* transform = 0);
	
	typename IFC_NAMESPACE::IfcSchema::IfcShapeRepresentation* addEmptyRepresentation(const std::string& repid = "Body", const std::string& reptype = "SweptSolid");

	typename IFC_NAMESPACE::IfcSchema::IfcGeometricRepresentationContext* getRepresentationContext(const std::string&);

private:
	std::map<std::string, typename IFC_NAMESPACE::IfcSchema::IfcGeometricRepresentationContext*> contexts;
};

/*
template <>
inline void IfcHierarchyHelper::addRelatedObject <typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure> (typename IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* relating_structure, 
	typename IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* related_object, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist)
{
	typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure::list::ptr li = instances_by_type<typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure>();
	bool found = false;
	for (typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure::list::it i = li->begin(); i != li->end(); ++i) {
		typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure* rel = *i;
		if (rel->RelatingStructure() == relating_structure) {
			typename IFC_NAMESPACE::IfcSchema::IfcProduct::list::ptr products = rel->RelatedElements();
			products->push((typename IFC_NAMESPACE::IfcSchema::IfcProduct*)related_object);
			rel->setRelatedElements(products);
			found = true;
			break;
		}
	}
	if (! found) {
		if (! owner_hist) {
			owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
		}
		if (! owner_hist) {
			owner_hist = addOwnerHistory();
		}
		typename IFC_NAMESPACE::IfcSchema::IfcProduct::list::ptr related_objects (new IfcTemplatedEntityList<typename IFC_NAMESPACE::IfcSchema::IfcProduct>());
		related_objects->push((typename IFC_NAMESPACE::IfcSchema::IfcProduct*)related_object);
		typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure* t = new typename IFC_NAMESPACE::IfcSchema::IfcRelContainedInSpatialStructure(IfcParse::IfcGlobalId(), owner_hist, 
			boost::none, boost::none, related_objects, (typename IFC_NAMESPACE::IfcSchema::IfcSpatialStructureElement*)relating_structure);

		addEntity(t);
	}
}

template <>
inline void IfcHierarchyHelper::addRelatedObject <typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType> (typename IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* relating_type, 
	typename IFC_NAMESPACE::IfcSchema::IfcObjectDefinition* related_object, typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory* owner_hist)
{
	typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType::list::ptr li = instances_by_type<typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType>();
	bool found = false;
	for (typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType::list::it i = li->begin(); i != li->end(); ++i) {
		typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType* rel = *i;
		if (rel->RelatingType() == relating_type) {
			typename IFC_NAMESPACE::IfcSchema::IfcObject::list::ptr objects = rel->RelatedObjects();
			objects->push((typename IFC_NAMESPACE::IfcSchema::IfcObject*)related_object);
			rel->setRelatedObjects(objects);
			found = true;
			break;
		}
	}
	if (! found) {
		if (! owner_hist) {
			owner_hist = getSingle<typename IFC_NAMESPACE::IfcSchema::IfcOwnerHistory>();
		}
		if (! owner_hist) {
			owner_hist = addOwnerHistory();
		}
		typename IFC_NAMESPACE::IfcSchema::IfcObject::list::ptr related_objects (new IfcTemplatedEntityList<typename IFC_NAMESPACE::IfcSchema::IfcObject>());
		related_objects->push((typename IFC_NAMESPACE::IfcSchema::IfcObject*)related_object);
		typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType* t = new typename IFC_NAMESPACE::IfcSchema::IfcRelDefinesByType(IfcParse::IfcGlobalId(), owner_hist, 
			boost::none, boost::none, related_objects, (typename IFC_NAMESPACE::IfcSchema::IfcTypeObject*)relating_type);

		addEntity(t);
	}
}
*/
}
#endif
