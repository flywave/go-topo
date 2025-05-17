#ifdef BIND
#undef BIND
#endif

#define BIND(T) \
	process_mapping<IfcSchema::T>(matched, item, inst);

#include <ifcgeom/mapping/mapping.i>
