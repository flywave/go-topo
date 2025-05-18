#ifndef IFC_PARSE_API_H
#define IFC_PARSE_API_H

#ifdef IFC_SHARED_BUILD
#ifdef _WIN32
#ifdef IFC_PARSE_EXPORTS
#define IFC_PARSE_API __declspec(dllexport)
#else
#define IFC_PARSE_API __declspec(dllimport)
#endif
#else // simply assume *nix + GCC-like compiler
#define IFC_PARSE_API __attribute__((visibility("default")))
#endif
#else
#define IFC_PARSE_API
#endif

#if defined(__clang__)
#define my_thread_local thread_local
#elif defined(__GNUC__)
#define my_thread_local __thread
#elif __STDC_VERSION__ >= 201112L
#define my_thread_local _Thread_local
#elif defined(_MSC_VER)
#define my_thread_local __declspec(thread)
#elif defined(SWIG)
#else
#error Cannot define thread_local
#endif

#endif
