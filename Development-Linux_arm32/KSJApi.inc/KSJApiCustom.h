#ifndef __KSJ_API_CUSTOM_H__
#define __KSJ_API_CUSTOM_H__

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

	// ��pData(���ΪnWidth, �߶�ΪnHeight, ����λ��ΪnBitCount)��ͼ����������Ϊ���ΪnStretchWidh, �߶�ΪnStretchHeight�����ݲ���䵽�û������pStretchData������,����λ������
	KSJ_API  KSJ_HelperStretchBmp(unsigned char *pData, int nWidth, int nHeight, int nBitCount, unsigned char *pStretchData, int nStretchWidth, int nStretchHeight);
	// ����ͼ��ı�����ȵõ�BMPͼ����ļ�ͷ,��Ϣͷ,����ɫ���ܵ��ֽ���Ŀ
	KSJ_API  KSJ_HelperGetBmpFileHeaderSize(int nBitCount, int *pnTotalBytes);
	// �õ�BMPͼ����ļ�ͷ����Ϣͷ
	KSJ_API  KSJ_HelperGetBmpFileHeader(int nWidth, int nHeight, int nBitCount, void *pHeader);
	// �ɼ�һ֡ͼ��ϵͳ������
	KSJ_API  KSJ_CaptureRgbDataToClipboard(int nIndex);

	// ����FFC�ӳ�
	KSJ_API  KSJ_SetFlatFieldCorrectionFieldOfView(int nIndex, int nColStart, int nRowStart, int nColSize, int nRowSize, KSJ_ADDRESSMODE ColAddressMode, KSJ_ADDRESSMODE RowAddressMode, unsigned short wMultiFrameNum);

	// ��ȡFFC���ӳ����ӳ�������ͬ�ſ��Խ���У����
	KSJ_API  KSJ_GetFlatFieldCorrectionFieldOfView(int nIndex, int *pnColStart, int *pnRowStart, int *pnColSize, int *pnRowSize, KSJ_ADDRESSMODE *pAmCol, KSJ_ADDRESSMODE *pAmRow, unsigned short *pwMultiFrameNum);

	// ���ݲɼ��ӳ��ɼ�nDarkFrames��ͼ��ƽ������ΪDarkFrame
	KSJ_API  KSJ_MakeDarkFrame(int nIndex, int nDarkFrames);
	// ���ݲɼ��ӳ��ɼ�nFlatFieldFrames��ͼ��ƽ������ΪFlatFieldImage
	KSJ_API  KSJ_MakeFlatFieldFrame(int nIndex, int nFlatFieldFrames);

	// Ԥ��ʱ�Ƿ�ʹ��
	KSJ_API  KSJ_PreviewSetFlatFieldCorrection(int nIndex, bool bEnable);

	KSJ_API  KSJ_PreviewGetFlatFieldCorrection(int nIndex, bool *pbEnable);
	// �ɼ�ʱ�Ƿ�ʹ��
	KSJ_API  KSJ_CaptureSetFlatFieldCorrection(int nIndex, bool bEnable);

	KSJ_API  KSJ_CaptureGetFlatFieldCorrection(int nIndex, bool *pbEnable);

	KSJ_API  KSJ_SaveFlatFieldCorrection(int nIndex, TCHAR *pszFilePath);

	KSJ_API  KSJ_LoadFlatFieldCorrection(int nIndex, TCHAR *pszFilePath);

	// Ԥ��ʱ�Ƿ�ʹ��
	KSJ_API  KSJ_PreviewSetCalibration(int nIndex, bool bEnable);

	KSJ_API  KSJ_PreviewGetCalibration(int nIndex, bool *pbEnable);
	// �ɼ�ʱ�Ƿ�ʹ��
	KSJ_API  KSJ_CaptureSetCalibration(int nIndex, bool bEnable);

	KSJ_API  KSJ_CaptureGetCalibration(int nIndex, bool *pbEnable);

	KSJ_API  KSJ_LoadCalibrationMapFile(int nIndex, const TCHAR *pszFilePath);

	enum KSJ_MAPMODE
	{
		KSJ_MM_NEARESTNEIGHBOR,
		KSJ_MM_BILINEAR
	};

	KSJ_API  KSJ_SetCalibrationMapMode(int nIndex, KSJ_MAPMODE MapMode);
	KSJ_API  KSJ_GetCalibrationMapMode(int nIndex, KSJ_MAPMODE *pMapMode);


#ifdef __cplusplus
}
#endif

#endif