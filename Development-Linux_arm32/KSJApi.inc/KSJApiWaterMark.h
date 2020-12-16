#ifndef __KSJ_API_WATER_MARK__H__
#define __KSJ_API_WATER_MARK__H__

#if defined (_WIN32)
#  ifdef KSJAPI_EXPORTS
#    define KSJAPI_IMPORT_EXPORT __declspec(dllexport)
#  else
#    define KSJAPI_IMPORT_EXPORT __declspec(dllimport)
#  endif

#  if defined (_M_IX86) || defined (__i386__)
#    define KSJAPI_CALLTYPE __stdcall
#  else
#    define KSJAPI_CALLTYPE  
#  endif

#elif defined (__GNUC__) && (__GNUC__ >= 4) && (defined (__linux__) || defined (__APPLE__))
#  define KSJAPI_IMPORT_EXPORT __attribute__((visibility("default")))
#  if defined (__i386__)
#    define KSJAPI_CALLTYPE __attribute__((stdcall))
#  else
#    define KSJAPI_CALLTYPE /* default */
#  endif
#  ifndef EXTERN_C
#    define EXTERN_C extern "C"
#  endif

#else
#  error Unknown platform, file needs adaption
#endif


#ifndef _WIN32
#define KSJ_API int
#else
#define KSJ_API KSJAPI_IMPORT_EXPORT int KSJAPI_CALLTYPE
#endif

#ifdef __cplusplus
extern "C"{
#endif

// 相关功能查询KSJ_SUPPORT_WATERMAK
enum KSJ_WATERMARKMODE { KSJ_WMM_TIMESTAMP, KSJ_WMM_DISTINGUISH_EXTERNAL_TRIGGER, KSJ_WMM_ANALYSIS_EXTERNAL_TRIGGER };

KSJ_API  KSJ_WaterMarkSetMode(int nIndex, KSJ_WATERMARKMODE WaterMarkMode);
KSJ_API  KSJ_WaterMarkGetMode(int nIndex, KSJ_WATERMARKMODE *pWaterMarkMode);

KSJ_API  KSJ_WaterMarkSetEnable(int nIndex, bool bEnable);
KSJ_API  KSJ_WaterMarkGetEnable(int nIndex, bool *pbEnable);

KSJ_API  KSJ_WaterMarkGetInfo(int nIndex, unsigned short *pwId, unsigned long *pdwTimestampLowPart, unsigned long *pdwTimestampHighPart);

#ifdef __cplusplus
}
#endif

#endif
