#ifndef __KSJ_API_IO_H__
#define __KSJ_API_IO_H__

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
extern "C" {
#endif

// KSJ_QueryFunction ( KSJ_SUPPORT_SNAP_BUTTON )
enum KSJ_SNAPBUTTONSTATUS 
{ 
	KSJ_UP, 
	KSJ_DOWN 
};
// Get Snap Pin Status
// When KSJ_SUPPORT_GPIO_NORMAL is True, KSJ_SUPPORT_SNAP_BUTTON will Enable after Set External Trigger Pin as Normal Input Pin.
KSJ_API  KSJ_SnapButtonStatus( int nIndex, KSJ_SNAPBUTTONSTATUS *pSnapButtonStatus );

// 设置GPIO引脚的输入输出状态，btDirection位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出，=0表示此GPIO输入)
KSJ_API  KSJ_GpioSetDirection( int nIndex, unsigned char btDirection );
// 获取GPIO引脚的输入输出状态，pbtDirection位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出，=0表示此GPIO输入)
KSJ_API  KSJ_GpioGetDirection( int nIndex, unsigned char *pbtDirection );

// 控制GPIO引脚输出，只有btDirection相应位设置为1的引脚才能通过此函数控制引脚输出。btGpioStatus位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出TTL高电平，=0表示此GPIO输出TTL低电平)
KSJ_API  KSJ_GpioSetStatus   ( int nIndex, unsigned char btGpioStatus );
// 读取GPIO引脚状态，*pbtGpioStatus位寻址，BIT0对应GPIO0, BIT1对应GPIO1, BIT2对应GPIO2, BIT3对应GPIO3(=1表示此GPIO输出TTL高电平，=0表示此GPIO输出TTL低电平)
KSJ_API  KSJ_GpioGetStatus   ( int nIndex, unsigned char *pbtGpioStatus );

// About Flash. nMode not valid.
KSJ_API  KSJ_FlashControlSet(int nIndex, bool bEnable, bool bInvert, int nMode);
KSJ_API  KSJ_FlashControlGet(int nIndex, bool *pbEnable, bool *pbInvert, int *pnMode);

KSJ_API  KSJ_FlashEnableSet(int nIndex, bool bEnable);
KSJ_API  KSJ_FlashEnableGet(int nIndex, bool *pbEnable);

KSJ_API  KSJ_FlashInvertSet(int nIndex, bool bInvert);
KSJ_API  KSJ_FlashInvertGet(int nIndex, bool *pbInvert);

enum KSJ_FLASHMODE
{
	KSJ_FM_TROW,
	KSJ_FM_SIMULTANEOUSEXPOSURE,
	KSJ_FM_SHUTTERWIDTH
};
KSJ_API  KSJ_FlashSetMode(int nIndex, KSJ_FLASHMODE FlashMode);
KSJ_API  KSJ_FlashGetMode(int nIndex, KSJ_FLASHMODE *pFlashMode);

// 如下函数只适用于YYO型号相机(帧存带光耦)
// 通过查询功能调用如下函数
// 注意：在外触发模式下，不可以设置为KSJ_GPIOIN_NORMAL，必须切换到非外触发模式时设置。
// 在用户调用设置为外触发模式时，自动设置为KSJ_GPIOIN_EXTERNALTRIGGER。
// KSJ_QueryFunction (KSJ_SUPPORT_GPIO_NORMAL)
// When call KSJ_GpioSetDirection(, bit0 = 0 ) == KSJ_GpioInModeSet(, KSJ_GPIOIN_NORMAL)
// When call KSJ_GpioSetDirection(, bit0 = 1 ) == KSJ_GpioInModeSet(, KSJ_GPIOIN_EXTERNALTRIGGER)
enum KSJ_GPIOIN_MODE 
{ 
	KSJ_GPIOIN_EXTERNALTRIGGER, 
	KSJ_GPIOIN_NORMAL
};
// 外触发输入引脚默认为外触发输入，也可以设置为普通IO输入，通过读取函数进行读取。
KSJ_API  KSJ_GpioInModeSet(int nIndex, KSJ_GPIOIN_MODE GpioInMode);
KSJ_API  KSJ_GpioInModeGet(int nIndex, KSJ_GPIOIN_MODE *pGpioInMode);
// 当外触发输入引脚作为普通IO时，可以通过此函数进行读取，BIT0为该引脚电平状态。1为高电平，0为低电平。
// 注意：只有在设置为KSJ_GPIOIN_NORMAL模式下才可以读取。
KSJ_API  KSJ_GpioInStatusGet(int nIndex, unsigned char *pbtValue);

// 通过查询KSJ_SUPPORT_FLASHOUT_ASIO功能调用如下函数
// When call KSJ_GpioSetDirection(, bit1 = 1 ) == KSJ_GpioOutModeSet(, KSJ_GPIOOUT_FLASH)
// When call KSJ_GpioSetDirection(, bit1 = 0 ) == KSJ_GpioOutModeSet(, KSJ_GPIOOUT_NORMAL)
// 
enum KSJ_GPIOOUT_MODE
{ 
	KSJ_GPIOOUT_FLASH, 
	KSJ_GPIOOUT_NORMAL 
};
KSJ_API  KSJ_GpioOutModeSet(int nIndex, KSJ_GPIOOUT_MODE GpioOutMode);
KSJ_API  KSJ_GpioOutModeGet(int nIndex, KSJ_GPIOOUT_MODE *pGpioOutMode);

// 注意：只有在KSJ_NORMAL_OUT模式下，才可以设置。
KSJ_API  KSJ_GpioOutStatusSet(int nIndex, unsigned char btValue);

// 设置滤波时间，单位为Us，如果设置为0，则硬件将以200ns进行滤波。
KSJ_API  KSJ_GpioFilterSet(int nIndex, unsigned short wFilterTimeUs);
KSJ_API  KSJ_GpioFilterGet(int nIndex, unsigned short *pwFilterTimeUs);



#ifdef __cplusplus
}
#endif

#endif