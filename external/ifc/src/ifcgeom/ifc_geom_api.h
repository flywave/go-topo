#ifndef IFC_GEOM_API_H
#define IFC_GEOM_API_H

#ifdef IFC_SHARED_BUILD
  #ifdef _WIN32
    #ifdef IFC_GEOM_EXPORTS
      #define IFC_GEOM_API __declspec(dllexport)
    #else
      #define IFC_GEOM_API __declspec(dllimport)
    #endif
  #else // simply assume *nix + GCC-like compiler
    #define IFC_GEOM_API __attribute__((visibility("default")))
  #endif
#else
  #define IFC_GEOM_API
#endif

#endif
