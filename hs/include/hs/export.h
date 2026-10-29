#ifndef HS_INCLUDE_HS_EXPORT_H
#define HS_INCLUDE_HS_EXPORT_H

#if defined (_WIN32) && defined (HS_SHARED_LIBRARY)
#if defined(HS_BUILDING_LIBRARY)
#define HS_API __declspec(dllexport)
#else
#define HS_API __declspec(dllimport)
#endif

#elif defined(__GNUC__) && defined(HS_SHARED_LIBRARY)
#define HS_API __attribute__((visibility("default")))
#else
#define HS_API
#endif

#endif