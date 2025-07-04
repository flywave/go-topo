#include "read_data.h"
#include <ifcparse/IfcSIPrefix.h>
#include <ifcparse/IfcException.h>

using namespace ifcopenshell;
using namespace ifcopenshell::data;

namespace {
std::string qualify_unrooted_instance(IfcUtil::IfcBaseInterface *inst) {
  return inst->declaration().name() + "_" +
         boost::lexical_cast<std::string>(
             inst->as<IfcUtil::IfcBaseEntity>()->id());
}



void parseAttr(IfcProperty &prop,AttributeValue attr){
   if (attr.type() == IfcUtil::Argument_STRING) {
            prop.value = (std::string)(attr);
          } else if (attr.type() == IfcUtil::Argument_INT) {
            prop.value = static_cast<int>(attr);
          } else if (attr.type() == IfcUtil::Argument_DOUBLE) {
            prop.value = static_cast<double>(attr);
          } else if (attr.type() == IfcUtil::Argument_BOOL) {
            prop.value = static_cast<bool>(attr);
          } else if (attr.type() == IfcUtil::Argument_BINARY) {
            prop.value = static_cast<boost::dynamic_bitset<>>(attr);
          } else if (attr.type() == IfcUtil::Argument_AGGREGATE_OF_INT) {
            prop.value = static_cast<std::vector<int>>(attr);
          } else if (attr.type() == IfcUtil::Argument_AGGREGATE_OF_DOUBLE) {
            prop.value = static_cast<std::vector<double>>(attr);
          } else if (attr.type() == IfcUtil::Argument_AGGREGATE_OF_STRING) {
            prop.value = static_cast<std::vector<std::string>>(attr);
          } else if (attr.type() == IfcUtil::Argument_AGGREGATE_OF_BINARY) {
            prop.value =
                static_cast<std::vector<boost::dynamic_bitset<>>>(attr);
          } else if (attr.type() ==
                     IfcUtil::Argument_AGGREGATE_OF_AGGREGATE_OF_INT) {
            prop.value = static_cast<std::vector<std::vector<int>>>(attr);
          } else if (attr.type() ==
                     IfcUtil::Argument_AGGREGATE_OF_AGGREGATE_OF_DOUBLE) {
            prop.value = static_cast<std::vector<std::vector<double>>>(attr);
          }else if(attr.type()==IfcUtil::Argument_ENTITY_INSTANCE){
             auto val=((IfcUtil::IfcBaseClass *)(attr))->data().get_attribute_value(0);
             parseAttr(prop,val);
          }else if(attr.type()==IfcUtil::Argument_LOGICAL){
                    IfcUtil::Argument_LOGICAL* logicalArg = 
            static_cast<IfcUtil::Argument_LOGICAL*>(attr);
            if (logicalArg->isTrue()) {
                prop.value = "TRUE";
            }else  if (logicalArg->isFalse()){
                prop.value = "FALSE";
            }else if (logicalArg->isUnknown()){
                prop.value = "UNKNOWN";
            }
          }else{
            std::cerr << "Unknown attribute type: " << attr.type() << std::endl;
          }
}
} // namespace

IfcData POSTFIX_SCHEMA(read_data)(IfcParse::IfcFile *file) {
  IfcData data;

  // 读取文件头信息
  try {
    auto &header = file->header();
    data.header.file_description.implementation_level =
        header.file_description().implementation_level();
    data.header.file_description.description =
        header.file_description().description();

    data.header.file_name.name = header.file_name().name();
    data.header.file_name.author = header.file_name().author();
    data.header.file_name.organization = header.file_name().organization();
    data.header.file_name.time_stamp = header.file_name().time_stamp();
    data.header.file_name.preprocessor_version =
        header.file_name().preprocessor_version();
    data.header.file_name.originating_system =
        header.file_name().originating_system();
    data.header.file_name.authorization = header.file_name().authorization();

    data.header.file_schema.schema_identifiers =
        header.file_schema().schema_identifiers();
  } catch (const IfcParse::IfcException &ex) {
    std::cerr << "Error reading IFC file header: " << ex.what() << std::endl;
  }

  auto project = *file->instances_by_type<IfcSchema::IfcProject>()->begin();
  auto unit_assignments = project->UnitsInContext()->Units();
  for (auto it = unit_assignments->begin(); it != unit_assignments->end();
       ++it) {
    IfcUnit unit;

    if ((*it)->declaration().is(IfcSchema::IfcNamedUnit::Class())) {
      auto named_unit = (*it)->as<IfcSchema::IfcNamedUnit>();
      unit.type = named_unit->declaration().name();

      std::string unit_name;

      if (named_unit->declaration().is(IfcSchema::IfcSIUnit::Class())) {
        IfcSchema::IfcSIUnit *unit = named_unit->as<IfcSchema::IfcSIUnit>();
        unit_name = IfcSchema::IfcSIUnitName::ToString(unit->Name());
        if (unit->Prefix()) {
          unit_name =
              IfcSchema::IfcSIPrefix::ToString(*unit->Prefix()) + unit_name;
        }
      } else {
        IfcSchema::IfcConversionBasedUnit *unit =
            named_unit->as<IfcSchema::IfcConversionBasedUnit>();
        unit_name = unit->Name();
      }

      unit.name = unit_name;
      unit.SI_equivalent = IfcParse::get_SI_equivalent<IfcSchema>(named_unit);
      data.units.push_back(unit);
    } else if ((*it)->declaration().is(IfcSchema::IfcMonetaryUnit::Class())) {
      auto monetary_unit = (*it)->as<IfcSchema::IfcMonetaryUnit>();
      unit.type = "IfcMonetaryUnit";

      std::string unit_name;

      if (monetary_unit->declaration().is(IfcSchema::IfcSIUnit::Class())) {
        IfcSchema::IfcSIUnit *unit = monetary_unit->as<IfcSchema::IfcSIUnit>();
        unit_name = IfcSchema::IfcSIUnitName::ToString(unit->Name());
        if (unit->Prefix()) {
          unit_name =
              IfcSchema::IfcSIPrefix::ToString(*unit->Prefix()) + unit_name;
        }
      } else {
        IfcSchema::IfcConversionBasedUnit *unit =
            monetary_unit->as<IfcSchema::IfcConversionBasedUnit>();
        unit_name = unit->Name();
      }
      unit.name = unit_name;
      data.units.push_back(unit);
    }
  }

  // 读取属性集
  auto psets = file->instances_by_type<IfcSchema::IfcPropertySet>();
  for (auto it = psets->begin(); it != psets->end(); ++it) {
    IfcPropertySet pset;
    pset.id = (*it)->GlobalId();
    pset.name = (*it)->Name().get_value_or("");

    auto props = (*it)->HasProperties();
    for (auto prop_it = props->begin(); prop_it != props->end(); ++prop_it) {
      IfcProperty prop;
      prop.name = (*prop_it)->Name(); 
      auto attr = (*prop_it)->data().get_attribute_value(2);
       try {
        if (!attr.isNull()) {
          parseAttr(prop,attr);
        } else {
          prop.value = boost::blank();
         }
       } catch (IfcParse::IfcException &e) {
        prop.value = boost::blank();
       }
      prop.type = (*prop_it)->declaration().name();
      pset.properties.push_back(prop);
    }
    data.properties.push_back(pset);
  }

  // 读取工程量信息
  auto qtosets = file->instances_by_type<IfcSchema::IfcElementQuantity>();
  for (auto it = qtosets->begin(); it != qtosets->end(); ++it) {
    IfcElementQuantity qto;
    qto.id = (*it)->GlobalId();
    qto.name = (*it)->Name().get_value_or("");

    auto quantities = (*it)->Quantities();
    for (auto qty_it = quantities->begin(); qty_it != quantities->end();
         ++qty_it) {
      try {
        IfcQuantity qty;
        qty.name = (*qty_it)->Name();
        qty.type = (*qty_it)->declaration().name();
        qty.value = (*qty_it)->data().get_attribute_value(2);
        IfcSchema::IfcPhysicalSimpleQuantity *qt =
            (*qty_it)->as<IfcSchema::IfcPhysicalSimpleQuantity>();
        qty.unit = qt->Unit()->UnitType();
        qto.quantities.push_back(qty);
      } catch (...) {
      }
    }
    data.quantities.push_back(qto);
  }

  // 读取工作计划
  auto work_plans = file->instances_by_type<IfcSchema::IfcWorkPlan>();
  for (auto it = work_plans->begin(); it != work_plans->end(); ++it) {
    IfcWorkPlan plan;
    plan.id = (*it)->GlobalId();
    plan.name = (*it)->Name().get_value_or("");

#ifdef SCHEMA_IfcWorkControl_HAS_Purpose
    plan.purpose = (*it)->Purpose().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkPlan_HAS_StartTime
    plan.start_time = (*it)->StartTime().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkPlan_HAS_FinishTime
    plan.finish_time = (*it)->FinishTime().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkPlan_HAS_Duration
    plan.duration = (*it)->Duration().get_value_or(0.0);
#endif

#ifdef SCHEMA_IfcWorkPlan_HAS_TotalFloat
    plan.total_float = (*it)->TotalFloat().get_value_or(0.0);
#endif

#ifdef SCHEMA_IfcWorkPlan_HAS_Creators
    auto creators = (*it)->Creators();
    if (creators) {
      for (auto creator : *creators) {
        plan.creators.push_back(creator);
      }
    }
#endif

#ifdef SCHEMA_IfcObjectDefinition_HAS_IsDecomposedBy
    auto decomposed_by = (*it)->IsDecomposedBy();
    for (auto rel_it = decomposed_by->begin(); rel_it != decomposed_by->end();
         ++rel_it) {
      auto related_objects = (*rel_it)->RelatedObjects();
      for (auto obj_it = related_objects->begin();
           obj_it != related_objects->end(); ++obj_it) {
        if ((*obj_it)->declaration().is(IfcSchema::IfcWorkSchedule::Class())) {
          plan.work_schedule_ids.push_back((*obj_it)->GlobalId());
        }
      }
    }
#endif

    data.work_plans.push_back(plan);
  }

  // 读取工作进度表
  auto work_schedules = file->instances_by_type<IfcSchema::IfcWorkSchedule>();
  for (auto it = work_schedules->begin(); it != work_schedules->end(); ++it) {
    IfcWorkSchedule schedule;
    schedule.id = (*it)->GlobalId();
    schedule.name = (*it)->Name().get_value_or("");

#ifdef SCHEMA_IfcWorkControl_HAS_Purpose
    schedule.purpose = (*it)->Purpose().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkSchedule_HAS_StartTime
    schedule.start_time = (*it)->StartTime().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkSchedule_HAS_FinishTime
    schedule.finish_time = (*it)->FinishTime().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkSchedule_HAS_Duration
    schedule.duration = (*it)->Duration().get_value_or(0.0);
#endif

#ifdef SCHEMA_IfcWorkSchedule_HAS_TotalFloat
    schedule.total_float = (*it)->TotalFloat().get_value_or(0.0);
#endif

#ifdef SCHEMA_IfcWorkSchedule_HAS_Creators
    auto creators = (*it)->Creators();
    if (creators) {
      for (auto creator : *creators) {
        schedule.creators.push_back(creator);
      }
    }
#endif

#ifdef SCHEMA_IfcControl_HAS_Controls
    auto controls = (*it)->Controls();
    for (auto rel_it = controls->begin(); rel_it != controls->end(); ++rel_it) {
      auto related_objects = (*rel_it)->RelatedObjects();
      for (auto obj_it = related_objects->begin();
           obj_it != related_objects->end(); ++obj_it) {
        if ((*obj_it)->declaration().is(IfcSchema::IfcTask::Class())) {
          IfcTask task;
          auto task_obj = (*obj_it)->as<IfcSchema::IfcTask>();
          task.id = task_obj->GlobalId();
          task.name = task_obj->Name().get_value_or("");
          task.status = task_obj->Status().get_value_or("");
          task.description = task_obj->Description().get_value_or("");
          task.object_type = task_obj->ObjectType().get_value_or("");
          task.work_method = task_obj->WorkMethod().get_value_or("");
          task.priority = task_obj->Priority().get_value_or(0);
          task.is_milestone = task_obj->IsMilestone();

          auto predecessors = task_obj->IsPredecessorTo();
          for (auto rel : *predecessors) {
            task.predecessor_tasks.push_back(rel->RelatedProcess()->GlobalId());
          }

          auto successors = task_obj->IsSuccessorFrom();
          for (auto rel : *successors) {
            task.successor_tasks.push_back(rel->RelatingProcess()->GlobalId());
          }

#ifdef SCHEMA_IfcTask_HAS_TaskTime
          if (task_obj->TaskTime()) {
            auto task_time = task_obj->TaskTime();
            IfcTaskTime tt;
            tt.schedule_start = task_time->ScheduleStart().get_value_or("");
            tt.schedule_finish = task_time->ScheduleFinish().get_value_or("");
            tt.actual_start = task_time->ActualStart().get_value_or("");
            tt.actual_finish = task_time->ActualFinish().get_value_or("");
            tt.free_float = task_time->FreeFloat().get_value_or("");
            tt.total_float = task_time->TotalFloat().get_value_or("");
            tt.is_critical = task_time->IsCritical().get_value_or(false);
            task.task_time = tt;
          }
#endif

          schedule.tasks.push_back(task);
        }
      }
    }
#endif

    data.work_schedules.push_back(schedule);
  }

// 读取工作日历
#ifdef SCHEMA_HAS_IfcWorkCalendar
  auto calendars = file->instances_by_type<IfcSchema::IfcWorkCalendar>();
  for (auto it = calendars->begin(); it != calendars->end(); ++it) {
    IfcWorkCalendar calendar;
    calendar.id = (*it)->GlobalId();
    calendar.name = (*it)->Name().get_value_or("");

    auto working_times = (*it)->WorkingTimes();
    if (working_times) {
      auto wt_vector = working_times->get();
      for (auto wt_it = wt_vector->begin(); wt_it != wt_vector->end();
           ++wt_it) {
        IfcWorkTime wt;
        wt.name = (*wt_it)->Name().get_value_or("");
        // RecurrencePattern

#ifdef SCHEMA_IfcWorkTime_HAS_Start
        wt.start_time = (*wt_it)->Start().get_value_or("");
#endif
#ifdef SCHEMA_IfcWorkTime_HAS_Finish
        wt.finish_time = (*wt_it)->Finish().get_value_or("");
#endif

#ifdef SCHEMA_IfcWorkTime_HAS_RecurrencePattern
        if ((*wt_it)->RecurrencePattern()) {
          auto pattern = (*wt_it)->RecurrencePattern();
          IfcRecurrencePattern rp;
          rp.position = pattern->Position().get_value_or(0);
          rp.interval = pattern->Interval().get_value_or(1);
          rp.occurrences = pattern->Occurrences().get_value_or(0);

          // 读取日、工作日和月组件
          auto day_comp = pattern->DayComponent();
          if (day_comp) {
            for (auto day : *day_comp) {
              rp.day_component.push_back(day);
            }
          }

          auto weekday_comp = pattern->WeekdayComponent();
          if (weekday_comp) {
            for (auto weekday : *weekday_comp) {
              rp.weekday_component.push_back(weekday);
            }
          }

          auto month_comp = pattern->MonthComponent();
          if (month_comp) {
            for (auto month : *month_comp) {
              rp.month_component.push_back(month);
            }
          }
#ifdef SCHEMA_IfcRecurrencePattern_HAS_TimePeriods
          if (pattern->TimePeriods()) {
            auto tps = pattern->TimePeriods();
            auto tps_ptr = tps->get(); // 获取shared_ptr指向的实际对象
            for (auto tp_it = tps_ptr->begin(); tp_it != tps_ptr->end();
                 ++tp_it) {
              IfcTimePeriod tp;
              tp.start_time = (*tp_it)->StartTime();
              tp.end_time = (*tp_it)->EndTime();
              rp.time_periods.push_back(tp);
            }
          }
#endif
          wt.recurrence_pattern = rp;
        }
#endif

        calendar.working_times.push_back(wt);
      }
    }

    data.calendars.push_back(calendar);
  }
#endif

  // 读取连接关系
  auto connections =
      file->instances_by_type<IfcSchema::IfcRelConnectsElements>();
  for (auto it = connections->begin(); it != connections->end(); ++it) {
    IfcConnection conn;
    conn.id = (*it)->GlobalId();

    if ((*it)->RelatingElement()) {
      conn.relating_element_id = (*it)->RelatingElement()->GlobalId();
    }
    if ((*it)->RelatedElement()) {
      conn.related_element_id = (*it)->RelatedElement()->GlobalId();
    }

    data.connections.push_back(conn);
  }

  // 读取类型对象
  auto type_objects = file->instances_by_type<IfcSchema::IfcTypeObject>();
  for (auto it = type_objects->begin(); it != type_objects->end(); ++it) {
    IfcTypeObject type;
    type.id = (*it)->GlobalId();
    type.name = (*it)->Name().get_value_or("");

#ifdef SCHEMA_IfcTypeObject_HAS_HasPropertySets
    auto property_sets = (*it)->HasPropertySets();
    if (property_sets) {
      auto pvs = property_sets.get();
      for (auto ps_it = pvs->begin(); ps_it != pvs->end(); ++ps_it) {
        if ((*ps_it)->declaration().is(IfcSchema::IfcPropertySet::Class())) {
          IfcPropertySet pset;
          pset.id = (*ps_it)->GlobalId();
          pset.name = (*ps_it)->Name().get_value_or("");

          auto props =
              (*ps_it)->as<IfcSchema::IfcPropertySet>()->HasProperties();
          for (auto prop_it = props->begin(); prop_it != props->end();
               ++prop_it) {
            IfcProperty prop;
            prop.name = (*prop_it)->Name();
            auto attr = (*prop_it)->data().get_attribute_value(2);
            try {
            if (!attr.isNull())  {
                parseAttr(prop,attr);
            } else {
              prop.value = boost::blank();
            }
            } catch (...) {
                prop.value = boost::blank();
              }
            prop.type = (*prop_it)->declaration().name();
            pset.properties.push_back(prop);
          }
          type.property_sets.push_back(pset);
        }
      }
    }
#endif

    data.types.push_back(type);
  }

  // 读取图层信息
  auto layers =
      file->instances_by_type<IfcSchema::IfcPresentationLayerAssignment>();
  for (auto it = layers->begin(); it != layers->end(); ++it) {
    IfcLayer layer;
    layer.id = (*it)->Identifier().get_value_or("");
    layer.name = (*it)->Name();
    layer.description = (*it)->Description().get_value_or("");

    auto assigned_items = (*it)->AssignedItems();
    for (auto item_it = assigned_items->begin();
         item_it != assigned_items->end(); ++item_it) {
      if ((*item_it)->declaration().is(IfcSchema::IfcProduct::Class())) {
        layer.assigned_elements.push_back(
            (*item_it)->data().get_attribute_value(0));
      }
    }
    data.layers.push_back(layer);
  }

  // 读取材料信息
  auto material_associations =
      file->instances_by_type<IfcSchema::IfcRelAssociatesMaterial>();
  for (auto it = material_associations->begin();
       it != material_associations->end(); ++it) {
    auto mat_select = (*it)->RelatingMaterial();

    if (mat_select->as<IfcSchema::IfcMaterial>()) {
      auto mat = mat_select->as<IfcSchema::IfcMaterial>();
      IfcMaterial material;
      material.id = qualify_unrooted_instance(mat);
      material.name = mat->Name();
#ifdef SCHEMA_IfcMaterial_HAS_Description
      material.description = mat->Description().get_value_or("");
#endif
#ifdef SCHEMA_IfcMaterial_HAS_Category
      material.category = mat->Category().get_value_or("");
#endif
      data.materials.push_back(material);
    } else if (mat_select->as<IfcSchema::IfcMaterialLayer>()) {
      auto mat = mat_select->as<IfcSchema::IfcMaterialLayer>();
      IfcMaterial material;
      material.id = qualify_unrooted_instance(mat);
#ifdef SCHEMA_IfcMaterialLayer_HAS_Name
      material.name = mat->Name().get_value_or("");
#endif
#ifdef SCHEMA_IfcMaterialLayer_HAS_Description
      material.description = mat->Description().get_value_or("");
#endif
#ifdef SCHEMA_IfcMaterialLayer_HAS_Category
      material.category = mat->Category().get_value_or("");
#endif
      data.materials.push_back(material);
    }
  }
  // 读取组信息
  auto groups = file->instances_by_type<IfcSchema::IfcGroup>();
  for (auto it = groups->begin(); it != groups->end(); ++it) {
    IfcGroup group;
    group.id = (*it)->GlobalId();
    group.name = (*it)->Name().get_value_or("");

#ifdef SCHEMA_IfcGroup_HAS_IsGroupedBy
    auto grouped_by = (*it)->IsGroupedBy();
    for (auto rel_it = grouped_by->begin(); rel_it != grouped_by->end();
         ++rel_it) {
      auto related_objects = (*rel_it)->RelatedObjects();
      for (auto obj_it = related_objects->begin();
           obj_it != related_objects->end(); ++obj_it) {
        group.member_ids.push_back((*obj_it)->GlobalId());
      }
    }
#endif
   data.groups.push_back(group);
  }

#ifdef SCHEMA_HAS_IfcRelDefinesByType
    auto rdts = file->instances_by_type<IfcSchema::IfcRelDefinesByType>();
    for (auto rdt_it = rdts->begin();  rdt_it != rdts->end(); ++rdt_it) {
        IfcRelDefinesByType rel;
        rel.id =(std::string) (*rdt_it)->data().get_attribute_value(0);
        auto attr1 = (*rdt_it)->data().get_attribute_value(2);
        if (!attr1.isNull()){
                  rel.name = (std::string)attr1;
        }
        auto attr2 = (*rdt_it)->data().get_attribute_value(3);
        if (!attr2.isNull()){
                  rel.desc = (std::string)attr2;
        }
#ifdef SCHEMA_IfcRelDefinesByType_HAS_RelatingType
        rel.type_object_id = (*rdt_it)->RelatingType()->GlobalId();
        auto relaatedObj = (*rdt_it)->data().get_attribute_value(4);
        if(!relaatedObj.isNull()){
             if (relaatedObj.type()==IfcUtil::Argument_ENTITY_INSTANCE){
                auto attr = ((IfcUtil::IfcBaseClass*)(relaatedObj))->data().get_attribute_value(0);
                rel.object_ids.push_back((std::string)attr);
             }else  if (relaatedObj.type()==IfcUtil::Argument_AGGREGATE_OF_ENTITY_INSTANCE){
                aggregate_of_instance::ptr entity_list_attribute = relaatedObj;
              for (auto it = entity_list_attribute->begin();  it != entity_list_attribute->end(); ++it) {
                  // 获取每个实体实例的GlobalId
                  auto attr = (*it)->data().get_attribute_value(0);
                  if (!attr.isNull()) {
                      rel.object_ids.push_back((std::string)attr);
                   }
              }
             }

        }
#endif
          data.rel_defines_by_types.push_back(rel);
    }
#endif


#ifdef SCHEMA_HAS_IfcRelDefinesByProperties
    auto rdps = file->instances_by_type<IfcSchema::IfcRelDefinesByProperties>();
    for (auto rdt_it = rdps->begin();  rdt_it != rdps->end(); ++rdt_it) {
        IfcRelDefinesByProperties rel;
        rel.id =(std::string) (*rdt_it)->data().get_attribute_value(0);
        auto attr1 = (*rdt_it)->data().get_attribute_value(2);
        if (!attr1.isNull()){
          rel.name = (std::string)attr1;
        }
        auto attr2 = (*rdt_it)->data().get_attribute_value(3);
        if (!attr2.isNull()){
          rel.desc = (std::string)attr2;
        }

      auto attr3 = (*rdt_it)->data().get_attribute_value(4);
   if(!attr3.isNull()){
             if (attr3.type()==IfcUtil::Argument_ENTITY_INSTANCE){
                auto attr = ((IfcUtil::IfcBaseClass*)(attr3))->data().get_attribute_value(0);
                rel.object_ids.push_back((std::string)attr);
             }else  if (attr3.type()==IfcUtil::Argument_AGGREGATE_OF_ENTITY_INSTANCE){
                aggregate_of_instance::ptr entity_list_attribute = attr3;
              for (auto it = entity_list_attribute->begin();  it != entity_list_attribute->end(); ++it) {
                  // 获取每个实体实例的GlobalId
                  auto attr = (*it)->data().get_attribute_value(0);
                  if (!attr.isNull()) {
                      rel.object_ids.push_back((std::string)attr);
                   }
              }
             }
        }

        
        auto defin = (*rdt_it)->RelatingPropertyDefinition();
        auto attr = defin->data().get_attribute_value(0);
        if (!attr.isNull()){
          rel.propertyset_id = (std::string)attr;
        }
         
         data.rel_defines_by_properties.push_back(rel);
    }
#endif


  return data;
} 
