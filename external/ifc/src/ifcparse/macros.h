#ifndef IFCOPENSHELL_MACROS_H
#define IFCOPENSHELL_MACROS_H

#define POSTFIX_SCHEMA__(a, b) a##_##b
#define POSTFIX_SCHEMA_(a, b) POSTFIX_SCHEMA__(a, b)
#define POSTFIX_SCHEMA(t) POSTFIX_SCHEMA_(t, IfcSchema)

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#define MAKE_INIT_FN__(a, b) init_##a##_##b
#define MAKE_INIT_FN_(a, b) MAKE_INIT_FN__(a, b)
#define MAKE_INIT_FN(t) MAKE_INIT_FN_(t, IfcSchema)

#endif
