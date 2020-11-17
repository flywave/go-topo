#include "IfcRegisterUndef.h"
#define CURVE(T) \
	if ( l->declaration().is(IFC_NAMESPACE::IfcSchema::T::Class()) ) return convert((IFC_NAMESPACE::IfcSchema::T*)l,r);
#include "IfcRegisterDef.h"

#include "IfcRegister.h"