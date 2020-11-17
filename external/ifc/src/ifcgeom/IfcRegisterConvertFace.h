#include "IfcRegisterUndef.h"
#define FACE(T) \
	if ( l->declaration().is(IFC_NAMESPACE::IfcSchema::T::Class()) ) return convert((IFC_NAMESPACE::IfcSchema::T*)l,r);
#include "IfcRegisterDef.h"

#include "IfcRegister.h"