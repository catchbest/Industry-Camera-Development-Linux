#ifndef __KSJ_API_16BITS_H__
#define __KSJ_API_16BITS_H__

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

	// Get AD Resolution. Valid bits in 16 bits.
	KSJ_API  KSJ_GetADCResolution(int nIndex, int *pnADCResolution);
	// Set 16bits Transfer, Image Data Bytes Number doubled.
	KSJ_API  KSJ_SetData16Bits(int nIndex, bool bEnable);
	// Get If 16bits Transfer
	KSJ_API  KSJ_GetData16Bits(int nIndex, bool *bEnable);
	// Get Capture Image Information. nBitsPerSample = 8 when not 16bits. = 16 when 16 bits.
	// Allocate Capture buffer according to these information.
	KSJ_API  KSJ_CaptureGetSizeExEx(int nIndex, int *pnWidth, int *pnHeight, int *pnBitCount, int *nBitsPerSample);
	// Save to Tiff Format.
	// When Not 16Bits, nBitPerSample = 8; When 16 Bits, nBitPerSample = 16
	// when BitCount = 8, nSamplesPerPixel = 1; When Bitcount = 24, nSamplesPerPixel = 3; When Bitcount = 32, nSamplesPerPixel = 4
	KSJ_API  KSJ_HelperSaveToTiff(unsigned char *pData, int nWidth, int nHeight, int nBitPerSample, int nSamplesPerPixel, const TCHAR *pszFileName);

#ifdef __cplusplus
}
#endif

#endif