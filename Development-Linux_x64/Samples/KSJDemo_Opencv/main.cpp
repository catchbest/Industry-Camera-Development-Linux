#include <stdio.h>
#include "stdlib.h"
#include <pthread.h>
#include <sys/types.h>

#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "KSJApi.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;


int main(int argc, char ** argv)
{
	bool bSaveImage = false;
	KSJ_BAYERMODE bayerMode = KSJ_RGGB_BGR24; 

	int nRet = 0;

	if (argc > 1) bSaveImage = (atoi(argv[1]) != 0);
	if (argc > 2) bayerMode = (KSJ_BAYERMODE)atoi(argv[2]);

	//1、初始化KSJAPI库
	nRet = KSJ_Init();
	printf("===== KSJ_Init nRet = %d =====\r\n", nRet);

	if (nRet != RET_SUCCESS)
	{
		printf("===== Init failed! exit... ===== \n");
		exit(1);
	}

	//2、获得相机的个数
	int nCamCount = KSJ_DeviceGetCount();
	printf("===== KSJ_DeviceGetCount found number = %d! =====\n", nCamCount);

	if (nCamCount <= 0)
	{
		printf("===== KSJ_DeviceGetCount: Not found any camare ! exit... ===== \n");
		KSJ_UnInit();
		exit(1);
	}

	int nCamIndex = 0; // 操作第1个相机

	// ** 打开log输出
	//KSJ_LogSet(true, NULL);

	//3、设置触发模式
	nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_INTERNAL);
	//nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_EXTERNAL);
	//nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_FIXFRAMERATE);
	printf("===== KSJ_TriggerModeSet  ret = %d =====\r\n", nRet);

	//3.1、设置固定帧率
	//nRet = KSJ_SetFixedFrameRateEx(nCamIndex, 20);
	//printf("===== KSJ_SetFixedFrameRateEx  ret = %d =====\r\n", nRet);

	//3.2、设置触发方式为上升沿
	//nRet = KSJ_TriggerMethodSet(nCamIndex, KSJ_TRIGGER_RISINGEDGE);
	//printf("===== KSJ_TriggerMethodSet  ret = %d =====\r\n", nRet);

	//3.3、设置设置IO口为闪光灯模式
	//nRet = KSJ_GpioOutModeSet(nCamIndex, KSJ_GPIOOUT_FLASH);
	//printf("===== KSJ_GpioOutModeSet  ret = %d =====\r\n", nRet);

	//3.4、设置闪光灯使能
	//nRet = KSJ_FlashEnableSet(nCamIndex, true);
	//printf("===== KSJ_FlashEnableSet  ret = %d =====\r\n", nRet);

	// ** 设置超时时间
	//nRet = KSJ_CaptureSetTimeOut(nCamIndex, 4000);
	//printf("===== KSJ_CaptureSetTimeOut  ret = %d =====\r\n", nRet);

	// ** 打印一下超时时间
	unsigned int dwTimeOut = 0;
	nRet = KSJ_CaptureGetTimeOut(nCamIndex, &dwTimeOut);
	printf("===== KSJ_CaptureSetTimeOut  dwTimeOut=%d  ret = %d =====\r\n", dwTimeOut, nRet);

	//4、设置曝光时间
	//nRet = KSJ_SetParam(nCamIndex, KSJ_EXPOSURE_LINES, 2000);
	//printf("===== KSJ_SetParam  KSJ_EXPOSURE_LINES=1  ret = %d =====\r\n", nRet);

	unsigned short pusDeviceType;
	int            pnSerials;
	unsigned short pusFirmwareVersion;
	unsigned short pusFpgaVersion;

	// ** 打印一下设备信息
	nRet = KSJ_DeviceGetInformationEx(nCamIndex, &pusDeviceType, &pnSerials, &pusFirmwareVersion, &pusFpgaVersion);
	if (nRet != RET_SUCCESS) printf("===== Device%d Info: 0x%08X - 0x%08X - 0x%08X - 0x%08X =====\n", nCamIndex+1, pusDeviceType, pnSerials, pusFirmwareVersion, pusFpgaVersion);

	// 取得当前的路径，一会儿保存在这个路径
	char working_path[256] = {0};
	getcwd(working_path, sizeof(working_path));

	//KSJ_WhitreBalanceSet(nCamIndex, KSJ_HWB_PRESETTINGS);

	KSJ_BayerSetMode(nCamIndex, bayerMode);

	int nWidth;
	int nHeight;
	int nBitCount;
	int nBufferSize = 0;
	unsigned char* pImageBuffer = NULL;

	if (KSJ_CaptureGetSizeEx(nCamIndex, &nWidth, &nHeight, &nBitCount) != RET_SUCCESS)
	{
		printf("===== KSJ_CaptureGetSizeEx: get camera image iinfo failed ! exit... ===== \n");
		KSJ_UnInit();
		exit(1);
	}

	int nShowImgW = 600;
	int nShowImgH = 600.0f / nWidth * nHeight;

	nBufferSize = nWidth*nHeight*nBitCount / 8;
	
	pImageBuffer = new unsigned char[nBufferSize];

	int nIndex = 0;

	struct timeval  t0;
	struct timeval  t1;

	float ffps = 0;
	float fruntt = 0;

	gettimeofday(&t0, NULL);
	
	int nMode = 0;

	while (1)
	{
		nRet = KSJ_CaptureRgbData(nCamIndex, pImageBuffer);

		if (nRet == RET_SUCCESS)
		{
			Mat matImage(cvSize(nWidth, nHeight), nBitCount == 8 ? CV_8UC1 : CV_8UC3, pImageBuffer);
			
			Mat matShow;

			resize(matImage, matShow, cvSize(nShowImgW, nShowImgH), 0, 0, INTER_LINEAR);

			imshow("Opencv_Demo", matShow);

			if (bSaveImage)
			{
				char szFilePath[260] = { 0 };

				sprintf(szFilePath, "%s/capture_%02d.bmp", working_path, nIndex % 20);

				if (KSJ_HelperSaveToBmp(pImageBuffer, nWidth, nHeight, nBitCount, szFilePath) == RET_SUCCESS)
				{
					printf("===== camare save image to %s ok =====\n", szFilePath);
				}
				else
				{
					printf("===== camare save image to %s failed =====\n", szFilePath);
				}
			}
			
			waitKey(5);
		}
		else
		{
			printf("===== KSJ_CaptureRgbData failed : ret = %d, index = %d =====\n", nRet, nIndex);

		}

		++nIndex;

		if (nIndex & 0x0080)
		{
			
			//KSJ_BayerSetMode(0, (KSJ_BAYERMODE)nMode++);
			//if (nMode >= 4) nMode = 0;

			gettimeofday(&t1, NULL);
			
			fruntt = (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;

			if (fruntt > 50)
			{
				ffps = 1000 * nIndex / fruntt;

				printf("===== fps = %.1f =====\n", ffps);

				nIndex = 0;
				t0 = t1;
			}
		}
	}

	if (pImageBuffer != NULL)
	{
		delete[]pImageBuffer;
		pImageBuffer = NULL;
	}

	nRet = KSJ_UnInit();

	printf("===== exit app ... =====\n");

	return 0;
}



