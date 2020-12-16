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

	//1����ʼ��KSJAPI��
	nRet = KSJ_Init();
	printf("===== KSJ_Init nRet = %d =====\r\n", nRet);

	if (nRet != RET_SUCCESS)
	{
		printf("===== Init failed! exit... ===== \n");
		exit(1);
	}

	//2���������ĸ���
	int nCamCount = KSJ_DeviceGetCount();
	printf("===== KSJ_DeviceGetCount found number = %d! =====\n", nCamCount);

	if (nCamCount <= 0)
	{
		printf("===== KSJ_DeviceGetCount: Not found any camare ! exit... ===== \n");
		KSJ_UnInit();
		exit(1);
	}

	int nCamIndex = 0; // ������1�����

	// ** ��log���
	//KSJ_LogSet(true, NULL);

	//3�����ô���ģʽ
	nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_INTERNAL);
	//nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_EXTERNAL);
	//nRet = KSJ_TriggerModeSet(nCamIndex, KSJ_TRIGGER_FIXFRAMERATE);
	printf("===== KSJ_TriggerModeSet  ret = %d =====\r\n", nRet);

	//3.1�����ù̶�֡��
	nRet = KSJ_SetFixedFrameRateEx(nCamIndex, 30);
	//printf("===== KSJ_SetFixedFrameRateEx  ret = %d =====\r\n", nRet);

	//3.2�����ô�����ʽΪ������
	//nRet = KSJ_TriggerMethodSet(nCamIndex, KSJ_TRIGGER_RISINGEDGE);
	nRet = KSJ_TriggerMethodSet(nCamIndex, KSJ_TRIGGER_LOWLEVEL);
	//printf("===== KSJ_TriggerMethodSet  ret = %d =====\r\n", nRet);

	//3.3����������IO��Ϊ�����ģʽ
	//nRet = KSJ_GpioOutModeSet(nCamIndex, KSJ_GPIOOUT_FLASH);
	//printf("===== KSJ_GpioOutModeSet  ret = %d =====\r\n", nRet);

	//3.4�����������ʹ��
	//nRet = KSJ_FlashEnableSet(nCamIndex, true);
	//printf("===== KSJ_FlashEnableSet  ret = %d =====\r\n", nRet);

	// ** ���ó�ʱʱ��
	//nRet = KSJ_CaptureSetTimeOut(nCamIndex, 4000);
	//printf("===== KSJ_CaptureSetTimeOut  ret = %d =====\r\n", nRet);

	// ** ��ӡһ�³�ʱʱ��
	unsigned int dwTimeOut = 0;
	nRet = KSJ_CaptureGetTimeOut(nCamIndex, &dwTimeOut);
	printf("===== KSJ_CaptureSetTimeOut  dwTimeOut=%d  ret = %d =====\r\n", dwTimeOut, nRet);

	//4�������ع�ʱ��
	int nExpLines = 2000;
	nRet = KSJ_SetParam(nCamIndex, KSJ_EXPOSURE_LINES, nExpLines);
	printf("===== KSJ_SetParam  KSJ_EXPOSURE_LINES=%d  ret = %d =====\r\n", nExpLines, nRet);

	unsigned short pusDeviceType;
	int            pnSerials;
	unsigned short pusFirmwareVersion;
	unsigned short pusFpgaVersion;

	// ** ��ӡһ���豸��Ϣ
	nRet = KSJ_DeviceGetInformationEx(nCamIndex, &pusDeviceType, &pnSerials, &pusFirmwareVersion, &pusFpgaVersion);
	if (nRet != RET_SUCCESS) printf("===== Device%d Info: 0x%08X - 0x%08X - 0x%08X - 0x%08X =====\n", nCamIndex+1, pusDeviceType, pnSerials, pusFirmwareVersion, pusFpgaVersion);

	// ȡ�õ�ǰ��·����һ������������·��
	char working_path[256] = {0};
	getcwd(working_path, sizeof(working_path));

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

	printf("===== nWidth = %d =====\r\n", nWidth);
	printf("===== nHeight = %d =====\r\n", nHeight);
	printf("===== nBitCount = %d =====\r\n", nBitCount);

	nBufferSize = nWidth*nHeight*nBitCount / 8;
	
	pImageBuffer = new unsigned char[nBufferSize];

	int nIndex = 0;

	struct timeval  t0;
	struct timeval  t1;

	float ffps = 0;
	float fruntt = 0;

	gettimeofday(&t0, NULL);
	
	while (1)
	{
		nRet = KSJ_CaptureRgbData(nCamIndex, pImageBuffer);

		if (nRet == RET_SUCCESS)
		{
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
		}
		else
		{
			printf("===== KSJ_CaptureRgbData failed : ret = %d, index = %d =====\n", nRet, nIndex);

		}

		++nIndex;


		if (nIndex & 0x0080)
		{
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



