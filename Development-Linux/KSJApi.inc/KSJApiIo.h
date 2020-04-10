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

// ����GPIO���ŵ��������״̬��btDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJ_API  KSJ_GpioSetDirection( int nIndex, unsigned char btDirection );
// ��ȡGPIO���ŵ��������״̬��pbtDirectionλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO�����=0��ʾ��GPIO����)
KSJ_API  KSJ_GpioGetDirection( int nIndex, unsigned char *pbtDirection );

// ����GPIO���������ֻ��btDirection��Ӧλ����Ϊ1�����Ų���ͨ���˺����������������btGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
KSJ_API  KSJ_GpioSetStatus   ( int nIndex, unsigned char btGpioStatus );
// ��ȡGPIO����״̬��*pbtGpioStatusλѰַ��BIT0��ӦGPIO0, BIT1��ӦGPIO1, BIT2��ӦGPIO2, BIT3��ӦGPIO3(=1��ʾ��GPIO���TTL�ߵ�ƽ��=0��ʾ��GPIO���TTL�͵�ƽ)
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

// ���º���ֻ������YYO�ͺ����(֡�������)
// ͨ����ѯ���ܵ������º���
// ע�⣺���ⴥ��ģʽ�£�����������ΪKSJ_GPIOIN_NORMAL�������л������ⴥ��ģʽʱ���á�
// ���û���������Ϊ�ⴥ��ģʽʱ���Զ�����ΪKSJ_GPIOIN_EXTERNALTRIGGER��
// KSJ_QueryFunction (KSJ_SUPPORT_GPIO_NORMAL)
// When call KSJ_GpioSetDirection(, bit0 = 0 ) == KSJ_GpioInModeSet(, KSJ_GPIOIN_NORMAL)
// When call KSJ_GpioSetDirection(, bit0 = 1 ) == KSJ_GpioInModeSet(, KSJ_GPIOIN_EXTERNALTRIGGER)
enum KSJ_GPIOIN_MODE 
{ 
	KSJ_GPIOIN_EXTERNALTRIGGER, 
	KSJ_GPIOIN_NORMAL
};
// �ⴥ����������Ĭ��Ϊ�ⴥ�����룬Ҳ��������Ϊ��ͨIO���룬ͨ����ȡ�������ж�ȡ��
KSJ_API  KSJ_GpioInModeSet(int nIndex, KSJ_GPIOIN_MODE GpioInMode);
KSJ_API  KSJ_GpioInModeGet(int nIndex, KSJ_GPIOIN_MODE *pGpioInMode);
// ���ⴥ������������Ϊ��ͨIOʱ������ͨ���˺������ж�ȡ��BIT0Ϊ�����ŵ�ƽ״̬��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ��
// ע�⣺ֻ��������ΪKSJ_GPIOIN_NORMALģʽ�²ſ��Զ�ȡ��
KSJ_API  KSJ_GpioInStatusGet(int nIndex, unsigned char *pbtValue);

// ͨ����ѯKSJ_SUPPORT_FLASHOUT_ASIO���ܵ������º���
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

// ע�⣺ֻ����KSJ_NORMAL_OUTģʽ�£��ſ������á�
KSJ_API  KSJ_GpioOutStatusSet(int nIndex, unsigned char btValue);

// �����˲�ʱ�䣬��λΪUs���������Ϊ0����Ӳ������200ns�����˲���
KSJ_API  KSJ_GpioFilterSet(int nIndex, unsigned short wFilterTimeUs);
KSJ_API  KSJ_GpioFilterGet(int nIndex, unsigned short *pwFilterTimeUs);



#ifdef __cplusplus
}
#endif

#endif