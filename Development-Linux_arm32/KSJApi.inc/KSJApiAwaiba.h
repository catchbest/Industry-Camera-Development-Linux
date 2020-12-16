#ifndef __KSJ_API_AWAIBA_H__
#define __KSJ_API_AWAIBA_H__


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

	KSJ_API    KSJ_AWAIBA_IsUsed( int nChannel, bool *bUsed );
	KSJ_API    KSJ_AWAIBA_GetSegmentNum(int nChannel, int *pnSegNum );

	KSJ_API    KSJ_AWAIBA_GetGainRange(int nChannel, int nSegIndex, int *pnMin, int *pnMax);
	KSJ_API    KSJ_AWAIBA_SetGain(int nChannel, int nSegIndex, int nGain);
	KSJ_API    KSJ_AWAIBA_GetGain(int nChannel, int nSegIndex, int *pnGain);

	KSJ_API    KSJ_AWAIBA_GetBlackLevelRange(int nChannel, int nSegIndex, int *pnMin, int *pnMax);
	KSJ_API    KSJ_AWAIBA_SetBlackLevel(int nChannel, int nSegIndex, int nBlackLevel);
	KSJ_API    KSJ_AWAIBA_GetBlackLevel (int nChannel, int nSegIndex, int *pnBlackLevel);
	KSJ_API    KSJ_AWAIBA_AutoBlackLevel(int nChannel, int nSegIndex);

	KSJ_API    KSJ_AWAIBA_SetSplitSegment(int nChannel, bool bSplit);
	KSJ_API    KSJ_AWAIBA_GetSplitSegment(int nChannel, bool *pbSplit);

	// 如下函数未实现
	/*
	KSJ_API    KSJ_AWAIBA_SetAntiBlooming(int nChannel, bool bEnable);
	KSJ_API    KSJ_AWAIBA_GetAntiBlooming(int nChannel, bool *bEnable);

	KSJ_API    KSJ_AWAIBA_SetAntiCorona(int nChannel, bool bEnable);
	KSJ_API    KSJ_AWAIBA_GetAntiCorona(int nChannel, bool *bEnable);

	enum KSJ_AWAIBA_ANALOGUE_GAIN {KSJ_AAG_X1, KSJ_AAG_X4};
	KSJ_API    KSJ_AWAIBA_SetAnalogueGain(int nChannel, KSJ_AWAIBA_ANALOGUE_GAIN Gain);
	KSJ_API    KSJ_AWAIBA_GetAnalogueGain(int nChannel, KSJ_AWAIBA_ANALOGUE_GAIN *pGain);
	*/



#ifdef __cplusplus
}
#endif

#endif