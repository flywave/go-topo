#include <ifcgeom/AbstractKernel.h>

#include <ifcgeom/IfcGeomElement.h>
#include <ifcgeom/ConversionSettings.h>
#include <ifcgeom/abstract_mapping.h>
#include <ifcgeom/function_item_evaluator.h>

#include <ifcgeom/kernels/OpenCascadeKernel.h>
#undef Handle

using namespace ifcopenshell::geometry;

bool ifcopenshell::geometry::kernels::AbstractKernel::convert(const taxonomy::ptr item, IfcGeom::ConversionResults& results) {
	auto with_exception_handling = [&](auto fn) {
		try {
			return fn();
		} catch (std::exception& e) {
			Logger::Error(e, item->instance);
			return false;
		} catch (...) {
			// @todo we can't log OCCT exceptions here, can we do some reraising to solve this?
			return false;
		}
	};
	auto without_exception_handling = [](auto fn) {
		return fn();
	};
	auto process_with_upgrade = [&]() {
		try {
			return dispatch_conversion<0>::dispatch(this, item->kind(), item, results);
		} catch (const not_implemented_error&) {
			return dispatch_with_upgrade<0>::dispatch(this, item, results);
		}
	};

	if (propagate_exceptions) {
		return without_exception_handling(process_with_upgrade);
	} else {
		return with_exception_handling(process_with_upgrade);
	}
}

const Settings& ifcopenshell::geometry::kernels::AbstractKernel::settings() const
{
	return settings_;
}


bool is_valid_for_kernel(const ifcopenshell::geometry::kernels::AbstractKernel* k, const IfcGeom::ConversionResult& shp) {
	return dynamic_cast<ifcopenshell::geometry::OpenCascadeShape*>(shp.Shape().get()) != nullptr;
}

class HybridKernel : public ifcopenshell::geometry::kernels::AbstractKernel {
	std::vector<std::unique_ptr<AbstractKernel>> kernels_;
	ifcopenshell::geometry::abstract_mapping* mapping_;
public:
	HybridKernel(IfcParse::IfcFile* file, Settings& settings, std::vector<std::unique_ptr<AbstractKernel>>&& kernels)
		: AbstractKernel(settings)
		, kernels_(std::move(kernels))
		, mapping_(ifcopenshell::geometry::impl::mapping_implementations().construct(file, settings))
	{}
	virtual bool convert(const taxonomy::ptr item, IfcGeom::ConversionResults& rs) {
		auto ops = mapping_->find_openings(item->instance->as<IfcUtil::IfcBaseEntity>());
		bool has_openings = ops && ops->size();
		for (auto& k : kernels_) {
			bool success = false;
			try {
				success = k->convert(item, rs);
			} catch(...) {}
			if (success) {
				return true;
			}
		}
		return false;
	}
	virtual bool apply_layerset(IfcGeom::ConversionResults& items, const ifcopenshell::geometry::layerset_information& layers) {
		for (auto& k : kernels_) {
			bool success = false;
			try {
				success = k->apply_layerset(items, layers);
			} catch (...) {}
			if (success) {
				return true;
			}
		}
		return false;
	}
	virtual bool apply_folded_layerset(IfcGeom::ConversionResults& items, const ifcopenshell::geometry::layerset_information& layers, const std::map<IfcUtil::IfcBaseEntity*, ifcopenshell::geometry::layerset_information>& folds) {
		for (auto& k : kernels_) {
			bool success = false;
			try {
				success = k->apply_folded_layerset(items, layers, folds);
			} catch (...) {}
			if (success) {
				return true;
			}
		}
		return false;
	}
	virtual bool convert_openings(const IfcUtil::IfcBaseEntity* entity, const std::vector<std::pair<taxonomy::ptr, ifcopenshell::geometry::taxonomy::matrix4>>& openings,
		const IfcGeom::ConversionResults& entity_shapes, const ifcopenshell::geometry::taxonomy::matrix4& entity_trsf, IfcGeom::ConversionResults& cut_shapes)
	{
		for (auto& k : kernels_) {
			bool is_valid = true;
			for (auto& s : entity_shapes) {
				if (!is_valid_for_kernel(k.get(), s)) {
					is_valid = false;
					break;
				}
			}
			if (!is_valid) {
				continue;
			}
			bool success = false;
			try {
				success = k->convert_openings(entity, openings, entity_shapes, entity_trsf, cut_shapes);
			} catch (...) {}
			if (success) {
				return true;
			}
		}
		return false;
	}
};

ifcopenshell::geometry::kernels::AbstractKernel* ifcopenshell::geometry::kernels::construct(IfcParse::IfcFile* file,  Settings& conv_settings) {
	return new IfcGeom::OpenCascadeKernel(conv_settings);
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::collection::ptr collection, IfcGeom::ConversionResults& r) {
	auto s = r.size();
	for (auto& c : collection->children) {
		if (!convert(c, r) && !partial_success_is_success) {
			return false;
		}
	}
	for (auto i = s; i < r.size(); ++i) {
		if (collection->matrix) {
			r[i].prepend(collection->matrix);
		}
		if (!r[i].hasStyle() && collection->surface_style) {
			r[i].setStyle(collection->surface_style);
		}
	}
	return r.size() > s;
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::function_item::ptr item, IfcGeom::ConversionResults& cs) {
   function_item_evaluator evaluator(settings(),item);
   auto expl = evaluator.evaluate();
	expl->instance = item->instance;
	return convert(expl, cs);
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::functor_item::ptr item, IfcGeom::ConversionResults& cs) {
    function_item_evaluator evaluator(settings(), item);
    auto expl = evaluator.evaluate();
    expl->instance = item->instance;
    return convert(expl, cs);
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::piecewise_function::ptr item, IfcGeom::ConversionResults& cs) {
    function_item_evaluator evaluator(settings(), item);
    auto expl = evaluator.evaluate();
    expl->instance = item->instance;
    return convert(expl, cs);
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::gradient_function::ptr item, IfcGeom::ConversionResults& cs) {
    function_item_evaluator evaluator(settings(), item);
    auto expl = evaluator.evaluate();
    expl->instance = item->instance;
    return convert(expl, cs);
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::cant_function::ptr item, IfcGeom::ConversionResults& cs) {
    function_item_evaluator evaluator(settings(), item);
    auto expl = evaluator.evaluate();
    expl->instance = item->instance;
    return convert(expl, cs);
}

bool ifcopenshell::geometry::kernels::AbstractKernel::convert_impl(const taxonomy::offset_function::ptr item, IfcGeom::ConversionResults& cs) {
    function_item_evaluator evaluator(settings(), item);
    auto expl = evaluator.evaluate();
    expl->instance = item->instance;
    return convert(expl, cs);
}
