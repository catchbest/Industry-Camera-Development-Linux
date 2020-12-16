#ifndef __KSJ_API_OBSOLETE_H__
#define __KSJ_API_OBSOLETE_H__

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


// �򿪻�ر�GammaУ������Ӱ��Ԥ����Ӱ��ɼ�
KSJ_API KSJ_GammaOn(int nChannel, bool bOn);    // Not Support Now.


// ���ù̶�֡��(ͨ������sensor�Ĵ���,ʹsensor����̶�֡��)��ֻ��MUC36C/M(MGYY)��MU3E130C/M(CGYY)֧��
// V4.0.86.12�汾��ʼ��bEnable������Ч��ͨ���û�����KSJ_TRIGGER_FIXFRAMERATEģʽ�������Ƿ�ʹ�ܡ�
KSJ_API KSJ_SetFixedFrameRate(int nChannel, bool bEnable, float fFrameRate);
KSJ_API KSJ_GetFixedFrameRate(int nChannel, bool *pbEnable, float *pfFrameRate);

// ������ź������ʵ������������ʱ���ã��ݲ�֧�֣�
KSJ_API KSJ_StrobeDelaySet(int nChannel, unsigned short wDelay);
KSJ_API KSJ_StrobeDelayGet(int nChannel, unsigned short *pwDelay);
KSJ_API KSJ_StrobeDelayGetRange(int nChannel, unsigned short *wMin, unsigned short *wMax);


// ����ͼ�񴫸����Ĺ�����ʽ���ݲ�֧�֣�
enum KSJ_SENSORMODE { KSJ_SM_TRIGGER_MODE, KSJ_SM_FREERUN_MODE, KSJ_SM_GRR_MODE };
KSJ_API KSJ_SensorModeSet(int nChannel, KSJ_SENSORMODE SensorMode);
KSJ_API KSJ_SensorModeGet(int nChannel, KSJ_SENSORMODE *SensorMode);

///////////////////////////////////////////////Color Correction////////////////////////////////////////////////////////////////
typedef void(__stdcall *KSJ_CCCALLBACK)(bool bSuccess, int nRShift, int nGShift, int nBShift, void *lpContext);

// ���º���Ϊ�����ɫУ��
KSJ_API KSJ_ColorCorrectSetCallback( int nChannel, KSJ_CCCALLBACK fpCCCallback, void *lpContext );

enum KSJ_COLORCORRECT { KSJ_CC_NONE, KSJ_CC_SHIFTRGB, KSJ_CC_EQRGB, KSJ_CC_EQALL, KSJ_CC_WB };
KSJ_API KSJ_ColorCorrectSet  ( int nChannel, KSJ_COLORCORRECT ColorCorrect, int nRTarget, int nGTarget, int nBTarget );
KSJ_API KSJ_ColorCorrectGet  ( int nChannel, KSJ_COLORCORRECT *pColorCorrect );
KSJ_API KSJ_ColorCorrectGetEx( int nChannel, KSJ_COLORCORRECT *pColorCorrect, int *pnRTarget, int *pnGTarget, int *pnBTarget );

KSJ_API KSJ_ColorCorrectTableSave( int nChannel, const TCHAR *pszFileName );
KSJ_API KSJ_ColorCorrectTableLoad( int nChannel, const TCHAR *pszFileName );
KSJ_API KSJ_IsColorCorrectTableLoad( int nChannel, bool *bLoad );

// KSJ_IR ����ƣ� KSJ_UV ����ƣ�KSJ_VI �ɼ����
enum KSJ_LED { KSJ_IR = 0, KSJ_UV, KSJ_VI };
// KSJ_ON ������KSJ_OFF �ƹ�
enum KSJ_LEDSTATUS { KSJ_OFF = 0, KSJ_ON };

// ���õƵ�״̬
KSJ_API KSJ_LedSetStatus( int nChannel, KSJ_LED Led, KSJ_LEDSTATUS LedStatus );
KSJ_API KSJ_LedGetStatus( int nChannel, KSJ_LED Led, KSJ_LEDSTATUS *pLedStatus );


#if 0

KSJ_API KSJ_IsSupportLUT( int nChannel );                      // Use KSJ_QueryFunction
KSJ_API KSJ_EnableLUT( int nChannel, bool bEnable );           // Use KSJ_LutSetEnable
KSJ_API KSJ_IsEnableLUT( int nChannel, bool *pbEnable );       // Use KSJ_LutGetEnable


// ���������ʹ��������ұ�д�뵽24LC1024��LUT_BASE_ADDRESSΪ��ַ��ulOffsetAddressΪƫ�Ƶĵ�ַ��
KSJ_API KSJ_ReadLUT ( int nChannel, unsigned short usOffsetAddress, int nBytes, unsigned char *pData   );
// nBytes���벻����64�ֽڣ�usOffsetAddress ��0��ʼ��
KSJ_API KSJ_WriteLUT( int nChannel, unsigned short usOffsetAddress, unsigned char *pData, int nBytes  );

// ����Ӱ���
// �����Ҫͨ�����Ӽ�ר�õ�Ӱ������ɹ�������, �˺�������ݲ��ұ�Ĳ�ͬ���ͽ�����Ӧ�ļ���
// ����12bit->8bit����10bit->8bitӳ���, �⺯����������16bit���ݴ���ģʽʱ,ͨ��Ӱ��֮�������ʾ���˹�����PC�˼�����ɡ�
KSJ_API KSJ_LoadMapTableFile( int nChannel, bool bLoad, const TCHAR *pszTableName );    // Use KSJ_LutFileDownload
/*
KSJ_API KSJ_WhiteBalanceAutoSetOnce( int nChannel, bool bOnce );               // You should call KSJ_WhiteBalanceSetEnable after call this function.
KSJ_API KSJ_WhiteBalanceAutoSetContinuous( int nChannel, bool bContinuous );   // You should call KSJ_WhiteBalanceSetEnable after call this function.

KSJ_API KSJ_WhiteBalanceAutoGetOnce( int nChannel, bool *pbOnce );             // You should call KSJ_WhiteBalanceSetEnable after call this function.
KSJ_API KSJ_WhiteBalanceAutoGetContinuous( int nChannel, bool *pbContinuous );

KSJ_API KSJ_WhiteBalanceSetEnable( int nChannel, bool bEnable );
KSJ_API KSJ_WhiteBalanceGetEnable( int nChannel, bool *pbEnable );
*/

// ��ƽ���������ɫУ������
//enum KSJ_COLORCORRECTION { KSJCC_NONE = 0, KSJCC_WARMLIGHT, KSJCC_COOLLIGHT, KSJCC_SUNLIGHT, KSJCC_OV, KSJCC_KODAK };
//KSJ_API KSJ_ColorCorrectionSet( int nChannel, KSJ_COLORCORRECTION  ColorCorrect  );
//KSJ_API KSJ_ColorCorrectionGet( int nChannel, KSJ_COLORCORRECTION *pColorCorrect );


// KSJ_API KSJ_ColorCorrectionSetEnable( int nChannel, bool bEnable );
// KSJ_API KSJ_ColorCorrectionGetEnable( int nChannel, bool *pbEnable );


#endif
#ifdef __cplusplus
}
#endif

#endif