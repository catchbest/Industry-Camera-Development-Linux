#ifndef __KSJ_API_MATRIX_H__
#define __KSJ_API_MATRIX_H__

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

	// SWB - Software White Balance; HWB - Hardware White Balance
	enum KSJ_WB_MODE
	{
		KSJ_WB_DISABLE,
		KSJ_SWB_PRESETTINGS,
		KSJ_SWB_AUTO_ONCE,
		KSJ_SWB_AUTO_CONITNUOUS,
		KSJ_SWB_MANUAL,
		KSJ_HWB_PRESETTINGS,
		KSJ_HWB_AUTO_ONCE,
		KSJ_HWB_AUTO_CONITNUOUS,
		KSJ_HWB_MANUAL
	};

	// Set White Balance Matrix Mode
	KSJ_API  KSJ_WhiteBalanceSet(int nIndex, KSJ_WB_MODE WbMode);
	// Get White Balance Matrix Mode
	KSJ_API  KSJ_WhiteBalanceGet(int nIndex, KSJ_WB_MODE *pWbMode);

	// Set nPhi when KSJ_SWB_AUTO_ONCE or KSJ_SWB_AUTO_CONITNUOUS
	KSJ_API  KSJ_WhiteBalanceAutoSet(int nIndex, int nPhi);
	KSJ_API  KSJ_WhiteBalanceAutoGet(int nIndex, int *pnPhi);


	// Set when KSJ_SWB_MANUAL or KSJ_HWB_MANUAL
	// Rw = fMatrix[0] * R, Gw = fMatrix[1] * G, Bw = fMatrix[1] * B
	// Range 0 - 5
	KSJ_API  KSJ_WhiteBalanceMatrixSet(int nIndex, float fMatrix[3]);
	// You can get current White Balance Matrix on Image
	KSJ_API  KSJ_WhiteBalanceMatrixGet(int nIndex, float fMatrix[3]);

	// Call Callback Function When KSJ_AWB_AUTO_ONCE or KSJ_AWB_AUTO_CONITNUOUS Done. Finall Matrix will Return.
	typedef void(__stdcall *KSJ_WB_CALLBACK)(float fMatrix[3], void *lpContext);
	KSJ_API  KSJ_WhiteBalanceAutoSetCallBack(int nIndex, KSJ_WB_CALLBACK    pfCallBack, void *lpContext);      // The nPhi decide auto calculate Matrix.

	// Call Callback Function When KSJ_AWB_AUTO_ONCE or KSJ_AWB_AUTO_CONITNUOUS Done. Finall Matrix will Return.
	typedef void(__stdcall *KSJ_WB_CALLBACK_EX)(float fMatrixR, float fMatrixG, float fMatrixB, void *lpContext);
	KSJ_API  KSJ_WhiteBalanceAutoSetCallBackEx(int nIndex, KSJ_WB_CALLBACK_EX pfCallBackEx, void *lpContext);

	enum KSJ_COLOR_TEMPRATURE
	{
		KSJ_CT_5000K,
		KSJ_CT_6500K,
		KSJ_CT_2800K
	};
	// Set Preseting White Balance Matrix according to Color Temprature when in KSJ_SWB_PRESETTINGS or KSJ_HWB_PRESETTINGS.
	KSJ_API  KSJ_WhiteBalancePresettingSet(int nIndex, KSJ_COLOR_TEMPRATURE WbPresetting);
	KSJ_API  KSJ_WhiteBalancePresettingGet(int nIndex, KSJ_COLOR_TEMPRATURE *pWbPresetting);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// SCCM - Software Color Correction Matrix; HCCM - Hardware Color Correction Matrix
	enum KSJ_CCM_MODE
	{
		KSJ_CCM_DISABLE,
		KSJ_SCCM_PRESETTINGS,
		KSJ_SCCM_MANUAL,
		KSJ_HCCM_PRESETTINGS,
		KSJ_HCCM_MANUAL
	};

	KSJ_API  KSJ_ColorCorrectionSet(int nIndex, KSJ_CCM_MODE CcmMode);
	KSJ_API  KSJ_ColorCorrectionGet(int nIndex, KSJ_CCM_MODE *pCcmMode);


	// Set Color Correction Matrix when in KSJ_SCCM_MANUAL or KSJ_HCCM_MANUAL
	// Rc = fMatrix[0][0] * Rw + fMatrix[0][1] * Gw + fMatrix[0][2] * Bw
	// Range -5 - 5
	KSJ_API  KSJ_ColorCorrectionMatrixSet(int nIndex, float fMatrix[3][3]);
	// Get current Color Correction Matrix on Image
	KSJ_API  KSJ_ColorCorrectionMatrixGet(int nIndex, float fMatrix[3][3]);


	// Set Preseting Color Correction Matrix according to Color Temprature when KSJ_SCCM_PRESETTINGS or KSJ_HCCM_PRESETTINGS.
	KSJ_API  KSJ_ColorCorrectionPresettingSet(int nIndex, KSJ_COLOR_TEMPRATURE CcmPresetting);
	KSJ_API  KSJ_ColorCorrectionPresettingGet(int nIndex, KSJ_COLOR_TEMPRATURE *pCcmPresetting);


#ifdef __cplusplus
}
#endif

#endif