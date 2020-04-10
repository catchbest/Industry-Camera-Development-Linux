#include <stdio.h>
#include "stdlib.h"
#include <pthread.h>
#include <sys/types.h>

#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "KSJApi.h"
using namespace std;


int main(int argc, char ** argv)
{
	bool bSaveImage = false;

	int nRet = 0;

	if (argc > 1) bSaveImage = (atoi(argv[1]) != 0);

	nRet = KSJ_Init();

	printf("===== KSJ_Init nRet = %d =====\r\n", nRet);

	if (nRet != RET_SUCCESS)
	{
		printf("===== Init failed! exit... ===== \n");
		return 0;
	}

	int nCamCount = KSJ_DeviceGetCount();

	printf("===== KSJ_DeviceGetCount found number = %d! =====\n", nCamCount);

	if (nCamCount <= 0)
	{
		printf("===== KSJ_DeviceGetCount: cann't found any camare ! exit... ===== \n");
		nRet = KSJ_UnInit();
		exit(1);
	}

	//KSJ_LogSet(false, NULL);

	//nRet = KSJ_TriggerModeSet(0, KSJ_TRIGGER_EXTERNAL);
	nRet = KSJ_TriggerModeSet(0, KSJ_TRIGGER_INTERNAL);
	//nRet = KSJ_TriggerModeSet(0, KSJ_TRIGGER_FIXFRAMERATE);
	printf("===== KSJ_TriggerModeSet  ret = %d =====\r\n", nRet);

	nRet = KSJ_SetFixedFrameRateEx(0, 20);
	printf("===== KSJ_SetFixedFrameRateEx  ret = %d =====\r\n", nRet);

	unsigned int dwTimeOut = 0;
	nRet = KSJ_CaptureGetTimeOut(0, &dwTimeOut);
	printf("===== KSJ_CaptureSetTimeOut  dwTimeOut=%d  ret = %d =====\r\n", dwTimeOut, nRet);

	//nRet = KSJ_CaptureSetTimeOut(0, 4000);
	//printf("===== KSJ_CaptureSetTimeOut  ret = %d =====\r\n", nRet);

	nRet = KSJ_CaptureGetTimeOut(0, &dwTimeOut);
	printf("===== KSJ_CaptureSetTimeOut  dwTimeOut=%d  ret = %d =====\r\n", dwTimeOut, nRet);

	nRet = KSJ_TriggerMethodSet(0, KSJ_TRIGGER_RISINGEDGE);
	printf("===== KSJ_TriggerMethodSet  ret = %d =====\r\n", nRet);

	nRet = KSJ_GpioOutModeSet(0, KSJ_GPIOOUT_FLASH);
	printf("===== KSJ_GpioOutModeSet  ret = %d =====\r\n", nRet);

	nRet = KSJ_FlashEnableSet(0, true);
	printf("===== KSJ_FlashEnableSet  ret = %d =====\r\n", nRet);

	nRet = KSJ_SetParam(0, KSJ_EXPOSURE_LINES, 1);
	printf("===== KSJ_SetParam  KSJ_EXPOSURE_LINES=1  ret = %d =====\r\n", nRet);

	unsigned short pusDeviceType;
	int            pnSerials;
	unsigned short pusFirmwareVersion;
	unsigned short pusFpgaVersion;


	nRet = KSJ_DeviceGetInformationEx(0, &pusDeviceType, &pnSerials, &pusFirmwareVersion, &pusFpgaVersion);
	if (nRet != RET_SUCCESS) printf("===== Device 1 Info: 0x%08X - 0x%08X - 0x%08X - 0x%08X =====\n", pusDeviceType, pnSerials, pusFirmwareVersion, pusFpgaVersion);

	char working_path[128];
	getcwd(working_path, sizeof(working_path));

	int nIndex = 0;

	int nWidth;
	int nHeight;
	int nBitCount;
	int nBufferSize = 0;
	unsigned char* pImageBuffer = NULL;

	struct timeval  t0;
	struct timeval  t1;

	float ffps = 0;
	float fruntt = 0;

	gettimeofday(&t0, NULL);

	KSJ_TRIGGERSTATUS status = KSJ_NO;

	struct timeval  start;
	struct timeval  end;

	while (1)
	{
		/*
		nRet = KSJ_TriggerStatusGet(0, &status);

		printf("===== KSJ_TriggerStatusGet nRet=%d status=%d =====\n", nRet, status);
		
		if (nRet != RET_SUCCESS)
		{
			usleep(1000000);
			continue;
		}

		if (status != KSJ_HAVE)
		{
			usleep(1000000);
			continue;
		}
		*/

		nRet = KSJ_CaptureGetSizeEx(0, &nWidth, &nHeight, &nBitCount);
		
		if (nRet == RET_SUCCESS)
		{
			if (nBufferSize < (nWidth*nHeight*nBitCount / 8))
			{
				if (pImageBuffer != NULL)
				{
					delete[]pImageBuffer;
					pImageBuffer = NULL;
				}

				nBufferSize = nWidth*nHeight*nBitCount / 8;
				pImageBuffer = new unsigned char[nBufferSize];
			}
		
			gettimeofday(&start, NULL);

			nRet = KSJ_CaptureRawData(0, pImageBuffer);

			gettimeofday(&end, NULL);

			if (nRet == RET_SUCCESS)
			{
				if (bSaveImage)
				{
					char szFilePath[260] = { 0 };

					sprintf(szFilePath, "%s/c1-img%02d.bmp", working_path, nIndex % 20);

					if (KSJ_HelperSaveToBmp(pImageBuffer, nWidth, nHeight, nBitCount, szFilePath) == RET_SUCCESS)
					{
						printf("===== camare1 save image to %s ok =====\n", szFilePath);
					}
					else
					{
						printf("===== camare1 save image to %s failed =====\n", szFilePath);
					}
				}
	

				float fRunTimeMs = (end.tv_sec - start.tv_sec) * 1000.0f + (end.tv_usec - start.tv_usec) / 1000.0f;

				printf("===== KSJ_CaptureRawData successed : ret = %d, index = %d capture use: %.2fMS =====\n", nRet, nIndex, fRunTimeMs);
			}
			else
			{
				printf("===== KSJ_CaptureRgbData failed : ret = %d, index = %d =====\n", nRet, nIndex);

			}
		}
		else
		{
			printf("===== KSJ_CaptureGetSizeEx failed : ret = %d, index = %d =====\n", nRet, nIndex);
		}

		++nIndex;

		gettimeofday(&t1, NULL);

		if (nIndex&0x0080)
		{
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



