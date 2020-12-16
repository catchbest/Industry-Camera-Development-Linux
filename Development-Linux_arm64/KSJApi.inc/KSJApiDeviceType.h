#pragma once
#pragma execution_character_set("utf-8")

#ifndef __KSJ_API_DEVICE_TYPE_H__
#define __KSJ_API_DEVICE_TYPE_H__

// 这个文件不影响编译，只是为了兼容之前的版本，提供给用户参考。每次添加设备时，可以直接添加，无需编译。
// Device Type
enum KSJ_DEVICETYPE
{
	KSJ_UC130C_MRNN = 0,   // 0 Guass2
	KSJ_UC130M_MRNN,       // 1 Guass2
	KSJ_RESERVED0,         // 2 Not Support
	KSJ_UC320C_MRNN,       // 3 Guass2
	KSJ_UC130C_MRYN,       // 4 Guass2
	KSJ_UC130M_MRYN,       // 5 Guass2
	KSJ_RESERVED1,         // 6 Not Support
	KSJ_UC320C_MRYN,       // 7 Guass2
	KSJ_UC500C_MRNN,       // 8 Guass2
	KSJ_UC500M_MRNN,       // 9 Guass2
	KSJ_UC500C_MRYN,       // 10 Guass2
	KSJ_UC500M_MRYN,       // 11 Guass2
	KSJ_UC320_OCR,         // 12 Not Support
	KSJ_UC900C_MRNN,       // 13 Not Support
	KSJ_UC1000C_MRNN,      // 14 Not Support
	KSJ_UC900C_MRYN,       // 15 Not Support
	KSJ_UC1000C_MRYN,      // 16 Not Support
	KSJ_MUC120C_MRYYO,     // 17 Jelly2 V6.0.121.16
	KSJ_MUC120M_MRYYO,     // 18 Jelly2 V6.0.121.16
	KSJ_UD140C_SRNN,       // 19 Not Support
	KSJ_UD140M_SRNN,       // 20 Not Support
	KSJ_UC36C_MGNN,        // 21 Elanus2 Not Support
	KSJ_UC36M_MGNN,        // 22 Elanus2 Not Support
	KSJ_UC36C_MGYN,        // 23 Elanus2 Not Support
	KSJ_UC36M_MGYN,        // 24 Elanus2 Not Support
	KSJ_UC900C_MRYY,       // 25 Elanus2
	KSJ_UC1000C_MRYY,      // 26 Elanus2
	KSJ_UC1400C_MRYY,      // 27 Elanus2
	KSJ_UC36C_MGYY,        // 28 Elanus2 Not Support
	KSJ_UC36M_MGYY,        // 29 Elanus2 Not Support
	KSJ_UC320C_MRYY,       // 30 Elanus2 Not Support
	KSJ_UC500C_MRYY,       // 31 Elanus2 Not Support
	KSJ_UC500M_MRYY,       // 32 Elanus2 Not Support
	KSJ_MUC130C_MRYN,      // 33 OEM
	KSJ_MUC130M_MRYN,      // 34 OEM.

	KSJ_MUC320C_MRYN,      // 35 OEM
	KSJ_MUC36C_MGYYO,      // 36 Jelly2
	KSJ_MUC36M_MGYYO,      // 37 Jelly2 
	KSJ_MUC130C_MRYY,      // 38 Not Support
	KSJ_MUC130M_MRYY,      // 39 Not Support
	KSJ_MUC320C_MRYY,      // 40 Not Support
	KSJ_MUC500C_MRYYO,     // 41 Jelly2
	KSJ_MUC500M_MRYYO,     // 42 Jelly2
	KSJ_MUC900C_MRYY,      // 43 Not Support
	KSJ_MUC1000C_MRYY,     // 44 Not Support
	KSJ_MUC1400C_MRYY,     // 45 Not Support
	KSJ_UD205C_SGYY,       // 46 Elanus2
	KSJ_UD205M_SGYY,       // 47 Elanus2
	KSJ_UD274C_SGYY,       // 48 Elanus2
	KSJ_UD274M_SGYY,       // 49 Elanus2
	KSJ_UD285C_SGYY,       // 50 Elanus2
	KSJ_UD285M_SGYY,       // 51 Elanus2
	KSJ_MU3C500C_MRYYO,    // 52 Jelly3 
	KSJ_MU3C500M_MRYYO,    // 53 Jelly3
	KSJ_MU3C1000C_MRYYO,   // 54 Jelly3
	KSJ_MU3C1400C_MRYYO,   // 55 Jelly3
	KSJ_MU3V130C_CGYYO,    // 56 Jelly3
	KSJ_MU3V130M_CGYYO,    // 57 Jelly3
	KSJ_MU3E130C_EGYYO,    // 58 Jelly3
	KSJ_MU3E130M_EGYYO,    // 59 Jelly3
	KSJ_MUC36C_MGYFO,      // 60 Jelly1
	KSJ_MUC36M_MGYFO,      // 61 Jelly1
	KSJ_MU3C120C_MGYYO,    // 62 Jelly3
	KSJ_MU3C120M_MGYYO,    // 63 Jelly3
	KSJ_MU3E200C_EGYYO,    // 64 Jelly3
	KSJ_MU3E200M_EGYYO,    // 65 Jelly3
	KSJ_MUC130C_MRYNO,     // 66 Jelly1
	KSJ_MUC130M_MRYNO,     // 67 Jelly1
	KSJ_MUC320C_MRYNO,     // 68 Jelly1
	KSJ_U3C130C_MRYNO,     // 69 Not Support
	KSJ_U3C130M_MRYNO,     // 70 Not Support
	KSJ_U3C320C_MRYNO,     // 71 Not Support
	KSJ_U3C500C_MRYNO,     // 72 Guass3
	KSJ_U3C500M_MRYNO,     // 73 Guass3
	KSJ_MU3C1401C_MRYYO,   // 74 DELETE Not Support 
	KSJ_MU3C1001C_MRYYO,   // 75 DELETE Not Support
	KSJ_MUC131M_MRYN,      // 76 OEM Device
	KSJ_MU3C501C_MRYYO,    // 77 DELETE Not Support
	KSJ_MU3C501M_MRYYO,    // 78 DELETE Not Support
	KSJ_MUC120C_MGYYO,     // 79 Jelly2
	KSJ_MUC120M_MGYYO,     // 80 Jelly2
	KSJ_MU3E131C_EGYYO,    // 81 DELETE Not Support
	KSJ_MU3E131M_EGYYO,    // 82 DELETE Not Support
	KSJ_MU3E201C_EGYYO,    // 83 DELETE Not Support
	KSJ_MU3E201M_EGYYO,    // 84 DELETE Not Support   
	KSJ_MISSING_DEVICE,	   // 85 Device Lost Program
	KSJ_MU3S230C_SGYYO,    // 86 Jelly3 Sony IMX174
	KSJ_MU3S230M_SGYYO,    // 87 Jelly3 Sony IMX174
	KSJ_MU3S640C_SRYYO,    // 88 Jelly3 Sony IMX178
	KSJ_MU3S640M_SRYYO,    // 89 Jelly3 Sony IMX178
	KSJ_CUD285C_SGYYO,     // 90
	KSJ_CUD285M_SGYYO,     // 91
	KSJ_MU3S231C_SGYYO,    // 92 Jelly3 Sony IMX249
	KSJ_MU3S231M_SGYYO,    // 93 Jelly3 Sony IMX249
	KSJ_MU3S500C_SGYYO,    // 94
	KSJ_MU3S500M_SGYYO,    // 95
	KSJ_MU3S1200C_SRYYO,   // 96
	KSJ_MU3S1200M_SRYYO,   // 97
	KSJ_MU3L2K7C_AGYYO,    // 98
	KSJ_MU3L2K7M_AGYYO,    // 99
	KSJ_MU3L4K3C_AGYYO,    // 100
	KSJ_MU3L4K3M_AGYYO,    // 101
	KSJ_MU3HS2000C_SRYYO,  // 102
	KSJ_MU3HS2000M_SRYYO,  // 103
	KSJ_MU3HS500C_SGYYO,   // 104
	KSJ_MU3HS500M_SGYYO,   // 105
	KSJ_MU3HS230C_SGYYO,   // 106 imx174 
	KSJ_MU3HS230M_SGYYO,   // 107
	KSJ_MU3HI400C_IGYYO,   // 108
	KSJ_MU3HI400M_IGYYO,   // 109
	KSJ_TEST_CAMERA,       // 110
	KSJ_MU3HI401C_IGYYO,
	KSJ_MU3HI401M_IGYYO,
	KSJ_MU3S40C_SGYYO,
	KSJ_MU3S40M_SGYYO,     // 114
	KSJ_MU3S210C_SRYYO,    // 115
	KSJ_MU3S210M_SRYYO,    // 116
	KSJ_MU3I130C_IGYYO,    // 117
	KSJ_MU3I130M_IGYYO,    // 118
	KSJ_MU3S321C_SGYYO,    // 119
	KSJ_MU3S321M_SGYYO,     // 120
	KSJ_MU3S641M_SRYYO,
	KSJ_MU3S1201M_SRYYO,
	KSJ_MU3HS2001M_SRYYO,
	KSJ_MU3S211M_SRYYO,
	KSJ_MU3C36C_MGYY,
	KSJ_MU3C36M_MGYY,
	KSJ_MU3HS1200C_SRYYO,
	KSJ_MU3HS1200M_SRYYO

};


#endif