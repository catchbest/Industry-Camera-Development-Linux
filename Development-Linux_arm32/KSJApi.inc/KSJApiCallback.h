#ifndef __KSJ_API_CALLBACK_H__
#define __KSJ_API_CALLBACK_H__

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
#define __stdcall
#else
#define KSJ_API KSJAPI_IMPORT_EXPORT int KSJAPI_CALLTYPE
#endif

#ifdef __cplusplus
extern "C"{
#endif

     // Preview Callback
	typedef void(__stdcall *KSJ_PREVIEWCALLBACK)(unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext);
    KSJ_API  KSJ_PreviewSetCallback( int nChannel, KSJ_PREVIEWCALLBACK pfPreviewCallback, void *lpContext );

	typedef void(__stdcall *KSJ_PREVIEWCALLBACKEX)(void*  hDC, unsigned char *pImageData, int nWidth, int nHeight, int nBitCount, void *lpContext);
    KSJ_API  KSJ_PreviewSetCallbackEx( int nChannel, KSJ_PREVIEWCALLBACKEX pfPreviewCallbackEx, void *lpContext );


#ifdef __cplusplus
}
#endif

#endif