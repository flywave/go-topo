#ifndef GO_PLATE_PLATE_C_API_H
#define GO_PLATE_PLATE_C_API_H

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define PLATECAPICALL __declspec(dllexport)
#else
#define PLATECAPICALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _plate_plate_t plate_plate_t;

#ifdef __cplusplus
}
#endif

#endif
