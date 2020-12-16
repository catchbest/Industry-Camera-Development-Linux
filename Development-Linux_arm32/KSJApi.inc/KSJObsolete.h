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


// 打开或关闭Gamma校正，即影响预览又影响采集
KSJ_API KSJ_GammaOn(int nChannel, bool bOn);    // Not Support Now.


// 设置固定帧速(通过设置sensor寄存器,使sensor输出固定帧率)，只有MUC36C/M(MGYY)和MU3E130C/M(CGYY)支持
// V4.0.86.12版本开始，bEnable参数无效，通过用户设置KSJ_TRIGGER_FIXFRAMERATE模式来决定是否使能。
KSJ_API KSJ_SetFixedFrameRate(int nChannel, bool bEnable, float fFrameRate);
KSJ_API KSJ_GetFixedFrameRate(int nChannel, bool *pbEnable, float *pfFrameRate);

// 闪光灯信号输出到实际相机输出的延时设置（暂不支持）
KSJ_API KSJ_StrobeDelaySet(int nChannel, unsigned short wDelay);
KSJ_API KSJ_StrobeDelayGet(int nChannel, unsigned short *pwDelay);
KSJ_API KSJ_StrobeDelayGetRange(int nChannel, unsigned short *wMin, unsigned short *wMax);


// 设置图像传感器的工作方式（暂不支持）
enum KSJ_SENSORMODE { KSJ_SM_TRIGGER_MODE, KSJ_SM_FREERUN_MODE, KSJ_SM_GRR_MODE };
KSJ_API KSJ_SensorModeSet(int nChannel, KSJ_SENSORMODE SensorMode);
KSJ_API KSJ_SensorModeGet(int nChannel, KSJ_SENSORMODE *SensorMode);

///////////////////////////////////////////////Color Correction////////////////////////////////////////////////////////////////
typedef void(__stdcall *KSJ_CCCALLBACK)(bool bSuccess, int nRShift, int nGShift, int nBShift, void *lpContext);

// 如下函数为软件颜色校正
KSJ_API KSJ_ColorCorrectSetCallback( int nChannel, KSJ_CCCALLBACK fpCCCallback, void *lpContext );

enum KSJ_COLORCORRECT { KSJ_CC_NONE, KSJ_CC_SHIFTRGB, KSJ_CC_EQRGB, KSJ_CC_EQALL, KSJ_CC_WB };
KSJ_API KSJ_ColorCorrectSet  ( int nChannel, KSJ_COLORCORRECT ColorCorrect, int nRTarget, int nGTarget, int nBTarget );
KSJ_API KSJ_ColorCorrectGet  ( int nChannel, KSJ_COLORCORRECT *pColorCorrect );
KSJ_API KSJ_ColorCorrectGetEx( int nChannel, KSJ_COLORCORRECT *pColorCorrect, int *pnRTarget, int *pnGTarget, int *pnBTarget );

KSJ_API KSJ_ColorCorrectTableSave( int nChannel, const TCHAR *pszFileName );
KSJ_API KSJ_ColorCorrectTableLoad( int nChannel, const TCHAR *pszFileName );
KSJ_API KSJ_IsColorCorrectTableLoad( int nChannel, bool *bLoad );

// KSJ_IR 红外灯， KSJ_UV 紫外灯，KSJ_VI 可见光灯
enum KSJ_LED { KSJ_IR = 0, KSJ_UV, KSJ_VI };
// KSJ_ON 灯亮，KSJ_OFF 灯关
enum KSJ_LEDSTATUS { KSJ_OFF = 0, KSJ_ON };

// 设置灯的状态
KSJ_API KSJ_LedSetStatus( int nChannel, KSJ_LED Led, KSJ_LEDSTATUS LedStatus );
KSJ_API KSJ_LedGetStatus( int nChannel, KSJ_LED Led, KSJ_LEDSTATUS *pLedStatus );


#if 0

KSJ_API KSJ_IsSupportLUT( int nChannel );                      // Use KSJ_QueryFunction
KSJ_API KSJ_EnableLUT( int nChannel, bool bEnable );           // Use KSJ_LutSetEnable
KSJ_API KSJ_IsEnableLUT( int nChannel, bool *pbEnable );       // Use KSJ_LutGetEnable


// 这个函数会使相机将查找表写入到24LC1024的LUT_BASE_ADDRESS为基址的ulOffsetAddress为偏移的地址。
KSJ_API KSJ_ReadLUT ( int nChannel, unsigned short usOffsetAddress, int nBytes, unsigned char *pData   );
// nBytes必须不大于64字节，usOffsetAddress 从0开始。
KSJ_API KSJ_WriteLUT( int nChannel, unsigned short usOffsetAddress, unsigned char *pData, int nBytes  );

// 加载影射表
// 这个表要通过凯视佳专用的影射表生成工具生成, 此函数会根据查找表的不同类型进行相应的加载
// 对于12bit->8bit或者10bit->8bit映射表, 库函数会在设置16bit数据传输模式时,通过影射之后进行显示，此功能由PC端计算完成。
KSJ_API KSJ_LoadMapTableFile( int nChannel, bool bLoad, const TCHAR *pszTableName );    // Use KSJ_LutFileDownload
/*
KSJ_API KSJ_WhiteBalanceAutoSetOnce( int nChannel, bool bOnce );               // You should call KSJ_WhiteBalanceSetEnable after call this function.
KSJ_API KSJ_WhiteBalanceAutoSetContinuous( int nChannel, bool bContinuous );   // You should call KSJ_WhiteBalanceSetEnable after call this function.

KSJ_API KSJ_WhiteBalanceAutoGetOnce( int nChannel, bool *pbOnce );             // You should call KSJ_WhiteBalanceSetEnable after call this function.
KSJ_API KSJ_WhiteBalanceAutoGetContinuous( int nChannel, bool *pbContinuous );

KSJ_API KSJ_WhiteBalanceSetEnable( int nChannel, bool bEnable );
KSJ_API KSJ_WhiteBalanceGetEnable( int nChannel, bool *pbEnable );
*/

// 白平衡后再做颜色校正处理
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