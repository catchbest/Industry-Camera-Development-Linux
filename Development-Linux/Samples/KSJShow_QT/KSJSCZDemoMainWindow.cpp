

#include <QPainter>
#include <QResizeEvent>
#include <QScrollBar>
#include <QSettings>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>

#include "KSJSCZDemoMainWindow.h"
#include "ui_KSJSCZDemoMainWindow.h"

#include "KSJApi.h"

#ifndef _WIN32
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <process.h>

#ifdef _DEBUG
#pragma comment( lib, "KSJApid.lib" )

#pragma comment(lib, "Qt5Widgetsd.lib")
#pragma comment(lib, "Qt5Guid.lib")
#pragma comment(lib, "Qt5Cored.lib")
#pragma comment(lib, "qtmaind.lib")
#else
#pragma comment( lib, "KSJApi.lib" )

#pragma comment(lib, "Qt5Widgets.lib")
#pragma comment(lib, "Qt5Gui.lib")
#pragma comment(lib, "Qt5Core.lib")
#pragma comment(lib, "qtmain.lib")
#endif

#endif

#ifdef _WIN32
unsigned int __stdcall CKSJSCZDemoMainWindow::ThreadForCaptureData(LPVOID arg)
#else
void* CKSJSCZDemoMainWindow::ThreadForCaptureData(void *arg)
#endif
{
	if (NULL == arg)
	{
#ifdef _WIN32
		return -1;
#else
		pthread_exit((char*)"none arg");
		return ((void *)0);
#endif
	}

	CKSJSCZDemoMainWindow* pMainWindow = (CKSJSCZDemoMainWindow*)arg;

	pMainWindow->update();

	int nRet;
	int nWidth;
	int nHeight;
	int nBitCount;
	int nBufferSize = 0;
	unsigned char* pImageBuffer = NULL;

	int nIndex = 0;

	//KSJ_EmptyFrameBuffer(pMainWindow->m_nCamareIndex);

	if (pMainWindow->m_nCamareIndex < 0)
	{
#ifdef _WIN32
		return 0;
#else
		pthread_exit((char*)"error param");
		return ((void *)0);
#endif
	}

	nRet = KSJ_CaptureGetSizeEx(pMainWindow->m_nCamareIndex, &nWidth, &nHeight, &nBitCount);

	if (nRet != RET_SUCCESS)
	{
#ifdef _WIN32
		return 0;
#else
		pthread_exit((char*)"error param");
		return ((void *)0);
#endif
	}

	nBufferSize = nWidth*nHeight*nBitCount / 8;
	pImageBuffer = new unsigned char[nBufferSize];
	
	pMainWindow->m_nClcFpsTickCount = 0;
	pMainWindow->m_nFramesCount = 0;
	pMainWindow->m_nLastFramesCount = 0;

	while (!pMainWindow->m_bStopCaptureThread)
	{
		nRet = KSJ_CaptureRgbData(pMainWindow->m_nCamareIndex, pImageBuffer);

		if (nRet == RET_SUCCESS)
		{
			++pMainWindow->m_nFramesCount;

			if (pMainWindow->m_bShowImage)
			{
				// 采集图像以后，将内存数据转换成QImage数据,这样pImageData的数据就被转移到QImage里面，以后可以自己进行算法操作
				pMainWindow->TransferImageData(pImageBuffer, nWidth, nHeight, nBitCount, 0);
			}
		}
		else
		{
			printf("KSJ_CaptureRgbData failed : ret = %d, index = %d \n", nRet, nIndex);

		}
	}

	pMainWindow->m_nClcFpsTickCount = -1;

#ifdef _WIN32
	return 0;
#else
	pthread_exit(0);
	return ((void *)0);
#endif
}


CKSJSCZDemoMainWindow::CKSJSCZDemoMainWindow(QWidget *parent) :
QDialog(parent)
, ui(new Ui::KSJSCZDemoMainWindow)
, m_pImage(NULL)
, m_nCamareIndex(0)
, m_bSaveImage(false)
, m_nSnapCount(0)
, m_bStopCaptureThread(false)
, m_bCapturingThreadIsWorking(false)
#ifdef _WIN32
, m_hCapturingThread(NULL)
, m_nCapturingThreadId(0)
#else
, m_nCapturingThreadId(0)
#endif
, m_bShowImage(true)
, m_nFramesCount(0)
, m_nLastFramesCount(0)
, m_bIsDoAutoExposure(false)
, m_nImgWidth(0)
, m_nImgHeight(0)
, m_nImgBitCount(0)
, m_pTempImageData(NULL)
, m_bHasNewData(false)
, m_nClcFpsTickCount(-1)
, m_fCaptureUseMS(0.0f)
{
	ui->setupUi(this);
	setMouseTracking(true);

#ifndef _DEBUG
	ui->TestingTab->setHidden(true);
#endif

	InitCnotrol();

	connect(ui->ExitAppPushButton, SIGNAL(clicked()), qApp, SLOT(quit()));

	connect(this, SIGNAL(sigWBADone(float, float, float)), this, SLOT(OnWBADone(float, float, float)));

	connect(this, SIGNAL(sigAEStartMsg(bool)), this, SLOT(OnAEStartMsg(bool)));
	connect(this, SIGNAL(sigAEFinishMsg(int, float)), this, SLOT(OnAEFinishMsg(int, float)));

	// 初始化
	RefreshDevice();

	KSJ_LogSet(true, NULL);

	QDateTime dt = QDateTime::currentDateTime();
	m_strImagePreFix = QCoreApplication::applicationDirPath() + "/" + dt.toString("yyyy-MM-ddhhmmss-");

	m_pClcFpsTimer = new QTimer(this);
	m_pClcFpsTimer->setInterval(2000);
	connect(m_pClcFpsTimer, SIGNAL(timeout()), this, SLOT(OnClcFpsTimer()));
}

CKSJSCZDemoMainWindow::~CKSJSCZDemoMainWindow()
{
	KillCaptureThread();

	KSJ_UnInit();

	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if (m_pTempImageData != NULL)
	{
		delete[]m_pTempImageData;
		m_pTempImageData = NULL;
	}

	delete ui;
}

void CKSJSCZDemoMainWindow::paintEvent(QPaintEvent *)
{
	ProcessCaptureData();

	// 图像不为空，则开始显示
	if (m_pImage != NULL)
	{
		QPainter painter(this);

		int w = size().width() - 320;
		int h = size().height();

		m_ImageLocker.lock();

		int iw = m_pImage->width();
		int ih = m_pImage->height();

		float fw = ((float)(w)) / iw;
		float fh = ((float)(h)) / ih;
		float f = fw < fh ? fw : fh;

		int dw = (int)(f*iw);
		int dh = (int)(f*ih);

		painter.drawImage(QRect(320 + (w - dw) / 2, (h - dh) / 2, dw, dh), *m_pImage, QRect(0, 0, iw, ih));

		m_ImageLocker.unlock();
	}
}

bool CKSJSCZDemoMainWindow::StartCaptureThread()
{
	if (m_bCapturingThreadIsWorking) return true;

	m_bStopCaptureThread = false;
	m_bCapturingThreadIsWorking = true;

#ifdef _WIN32
	m_hCapturingThread = (HANDLE)_beginthreadex(NULL, 0, ThreadForCaptureData, this, 0, &m_nCapturingThreadId);

	return (m_hCapturingThread != NULL);
#else
	pthread_attr_t  attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&m_nCapturingThreadId, &attr, ThreadForCaptureData, (void *)this);
	pthread_attr_destroy(&attr);
#endif

	return true;
}

bool CKSJSCZDemoMainWindow::KillCaptureThread()
{
#ifdef _WIN32
	if (m_hCapturingThread == NULL) return true;
	if (!m_bCapturingThreadIsWorking) return true;

	m_bStopCaptureThread = true;

#ifdef OLD_KSJAPI
	KSJ_SendPktEnd(m_nCamareIndex);
	//KSJ_EmptyFrameBuffer(m_nCamareIndex);
#endif

	if (WaitForSingleObject(m_hCapturingThread, 10000) != WAIT_OBJECT_0)
	{
		TerminateThread(m_hCapturingThread, 0);
	}

	m_hCapturingThread = NULL;

	m_bCapturingThreadIsWorking = false;
#else
	m_bStopCaptureThread = true;
	m_bCapturingThreadIsWorking = false;
#endif
	return true;
}

void CKSJSCZDemoMainWindow::on_PreViewPushButton_clicked()
{
	if (m_nCamareIndex >= 0)
	{
		if (m_bCapturingThreadIsWorking) this->StopPreview();
		else                             this->StartPreview();
	}
}

void CKSJSCZDemoMainWindow::on_RefreshPushButton_clicked()
{
	bool bIsCapturing = this->StopPreview();

	RefreshDevice();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_SnapImagePushButton_clicked()
{
	m_fCaptureUseMS = -1.f;

	if (m_bCapturingThreadIsWorking)
	{
		m_bSaveImage = true;
	}
	else if (!m_nCamareIndex>=0)
	{
		int nRet;
		int nWidth;
		int nHeight;
		int nBitCount;
		int nBufferSize = 0;

		int nIndex = 0;

		//KSJ_EmptyFrameBuffer(pMainWindow->m_nCamareIndex);

		nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);

		if (nRet != RET_SUCCESS)
		{
			ui->SnapCountLabel->setText(QString("Capture failed: error=%1").arg(nRet));

			return;
		}

		unsigned char* pImageBuffer = NULL;

		nBufferSize = nWidth*nHeight*nBitCount / 8;
		pImageBuffer = new unsigned char[nBufferSize];

#ifdef _WIN32
		QueryPerformanceFrequency(&m_lifrqc);  // 取得高精度运行计数器的频率f,单位是每秒多少次（n/s）,  
		QueryPerformanceCounter(&m_litmp1);    // 取得高精度运行计数器的数值
#else
		gettimeofday(&m_start, NULL);
#endif

		nRet = KSJ_CaptureRgbData(m_nCamareIndex, pImageBuffer);

#ifdef _WIN32
		QueryPerformanceCounter(&m_litmp2); // 取得高精度运行计数器的数值
		m_fCaptureUseMS = (m_litmp2.QuadPart - m_litmp1.QuadPart) * 1000.f / m_lifrqc.QuadPart;//获得对应时间,单位为微秒

		m_litmp1 = m_litmp2;
#else
		gettimeofday(&m_end, NULL);
		m_fCaptureUseMS = (m_end.tv_sec - m_start.tv_sec) * 1000.0f + (m_end.tv_usec - m_start.tv_usec) / 1000.0f;

		m_start = m_end;
#endif

		if (nRet == RET_SUCCESS)
		{
			m_bSaveImage = true;

			TransferImageData(pImageBuffer, nWidth, nHeight, nBitCount, 0);

			//ui->SnapCountLabel->setText(QString("Snap finidhed, use %1 MS").arg(QString::number(fRunTimeS, 'f', 2)));
		}
		else
		{
			ui->SnapCountLabel->setText(QString("Capture failed: error=%1").arg(nRet));
		}
	}
	else
	{
		ui->SnapCountLabel->setText("No any camera");
	}
}

#define KSJ_MSB(x)     ((x&0xff00) >> 8)
#define KSJ_LSB(x)     (x & 0x00ff)

void CKSJSCZDemoMainWindow::RefreshDevice()
{
	m_nCamareIndex = -1;

	ui->DevicesComboBox->clear();

	KSJ_UnInit();

#ifdef _WIN32
	Sleep(1);
#else
	usleep(1000);
#endif

	int nRet = KSJ_Init();

	if (nRet != RET_SUCCESS) return;

#ifdef OLD_KSJAPI
	KSJ_DEVICETYPE pusDeviceType;
#else
	unsigned short pusDeviceType;
#endif
	int            pnSerials;
	unsigned short pusFirmwareVersion;
	unsigned short pusFpgaVersion;

	int nCamCount = KSJ_DeviceGetCount();

	printf(" %s %s %d   count  %d    \n", __FILE__, __FUNCTION__, __LINE__, nCamCount);

	if (nCamCount <= 0)
	{
		return;
	}

	QString strCamare;

	for (int i = 0; i < nCamCount; ++i)
	{
		nRet = KSJ_DeviceGetInformationEx(i, &pusDeviceType, &pnSerials, &pusFirmwareVersion, &pusFpgaVersion);

		if (nRet != RET_SUCCESS)
		{
			strCamare = QString("Camare%1: Unknow").arg(i);
		}
		else
		{
			strCamare = QString("Camare%1: SN(%2)-Type(%3)-FW(%4.%5)-PL(%6.%7)").arg(i).arg(pnSerials).arg(pusDeviceType).arg(KSJ_MSB(pusFirmwareVersion)).arg(KSJ_LSB(pusFirmwareVersion)).arg(KSJ_MSB(pusFpgaVersion)).arg(KSJ_LSB(pusFpgaVersion));
		}

		ui->DevicesComboBox->addItem(strCamare);
	}

	SelectDevice(-1);
}

void CKSJSCZDemoMainWindow::SelectDevice(int nIndex)
{
	bool bIsCapturing = this->StopPreview();

	m_nCamareIndex = -1;

	if (ui->DevicesComboBox->count() <= 0) return;

	if (nIndex <= 0) m_nCamareIndex = 0;
	else             m_nCamareIndex = nIndex;

	//KSJ_CaptureSetFieldOfView(m_nCamareIndex, 0, 0, 1792, 1024, KSJ_SKIPNONE, KSJ_SKIPNONE);

	//KSJ_TriggerModeSet(m_nCamareIndex, KSJ_TRIGGER_SOFTWARE);
	//KSJ_CaptureSetTimeOut(m_nCamareIndex, 8000);
	//KSJ_WhiteBalanceSet(m_nCamareIndex, KSJ_SWB_MANUAL);
	//float fMatrix[3];
	//fMatrix[0] = 2.24; fMatrix[1] = 1.00; fMatrix[2] = 1.59;
	//KSJ_WhiteBalanceMatrixSet(m_nCamareIndex, fMatrix);
	//KSJ_ColorCorrectionSet(m_nCamareIndex, KSJ_CCM_DISABLE);
	//KSJ_TriggerModeSet(m_nCamareIndex, KSJ_TRIGGER_EXTERNAL);
	//KSJ_TriggerMethodSet(m_nCamareIndex, KSJ_TRIGGER_LOWLEVEL);

	//KSJ_CaptureSetFieldOfView(m_nCamareIndex, 0, 0, 1280, 960, KSJ_SKIPNONE, KSJ_SKIPNONE);

	//KSJ_BayerSetMode(m_nCamareIndex, KSJ_BGGR_BGR32_FLIP);
	//KSJ_SetParam(m_nCamareIndex, KSJ_RED, 48);
	//KSJ_SetParam(m_nCamareIndex, KSJ_GREEN, 48);
	//KSJ_SetParam(m_nCamareIndex, KSJ_BLUE, 48);
	//KSJ_TriggerModeSet(m_nCamareIndex, KSJ_TRIGGER_INTERNAL);
	//KSJ_WhiteBalanceSet(m_nCamareIndex, KSJ_SWB_AUTO_ONCE);
	//KSJ_ExposureTimeSet(m_nCamareIndex, 20);
	//KSJ_SetParam(m_nCamareIndex, KSJ_MIRROR, false);
	//KSJ_LutSetEnable(m_nCamareIndex, true);
	//KSJ_SensitivitySetMode(m_nCamareIndex, KSJ_LOW);

	ui->DevicesComboBox->setCurrentIndex(m_nCamareIndex);

	//KSJ_GpioFilterSet(m_nCamareIndex, 100000);  // us为单位 5MS
	//KSJ_WaterMarkSetEnable(m_nCamareIndex, true);

	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_DevicesComboBox_currentIndexChanged(int nIndex)
{
	if (ui->DevicesComboBox->count() <= 0) return;

	bool bIsCapturing = this->StopPreview();

	SelectDevice(nIndex);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_TrigetModeComboBox_currentIndexChanged(int nIndex)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_TriggerModeSet(m_nCamareIndex, KSJ_TRIGGERMODE(nIndex));
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_TrigetMethodComboBox_currentIndexChanged(int nIndex)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_TriggerMethodSet(m_nCamareIndex, KSJ_TRIGGERMETHOD(nIndex));
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_FixFrameRateDoubleSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_SetFixedFrameRateEx(m_nCamareIndex, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_CaptureTimeoutSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_CaptureSetTimeOut(m_nCamareIndex, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_SkipComboBox_currentIndexChanged(int index)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet;
	int nColStart;
	int nRowStart;
	int nColSize;
	int nRowSize;
	unsigned short nsMultiFrameNum;
	KSJ_ADDRESSMODE AmCol;
	KSJ_ADDRESSMODE AmRow;

	nRet = KSJ_CaptureGetFieldOfViewEx(m_nCamareIndex, &nColStart, &nRowStart, &nColSize, &nRowSize, &AmCol, &AmRow, &nsMultiFrameNum);

	if (nRet == RET_SUCCESS)
	{
		AmCol = (KSJ_ADDRESSMODE)index;
		AmRow = (KSJ_ADDRESSMODE)index;

		KSJ_CaptureSetFieldOfViewEx(m_nCamareIndex, nColStart, nRowStart, nColSize, nRowSize, AmCol, AmRow, nsMultiFrameNum);
	}
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_ApplyFovPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet;
	int nColStart;
	int nRowStart;
	int nColSize;
	int nRowSize;
	unsigned short nsMultiFrameNum;
	KSJ_ADDRESSMODE AmCol;
	KSJ_ADDRESSMODE AmRow;

	nRet = KSJ_CaptureGetFieldOfViewEx(m_nCamareIndex, &nColStart, &nRowStart, &nColSize, &nRowSize, &AmCol, &AmRow, &nsMultiFrameNum);

	if (nRet == RET_SUCCESS)
	{
		nColStart = ui->ColStartSpinBox->value();
		nRowStart = ui->ColSizeSpinBox->value();
		nColSize = ui->RowStartSpinBox->value();
		nRowSize = ui->RowSizeSpinBox->value();
		nsMultiFrameNum = ui->MultiFrameNumberSpinBox->value();

		KSJ_CaptureSetFieldOfViewEx(m_nCamareIndex, nColStart, nRowStart, nColSize, nRowSize, AmCol, AmRow, nsMultiFrameNum);
	}
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_ExpoureLineSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet = KSJ_SetParam(m_nCamareIndex, KSJ_EXPOSURE_LINES, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_ExposureTimeSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet = KSJ_ExposureTimeSet(m_nCamareIndex, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_MirrorCheckBox_stateChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_SetParam(m_nCamareIndex, KSJ_MIRROR, (value == Qt::Checked) ? 1 : 0);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_FlipCheckBox_stateChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	//bool bIsCapturing = this->StopPreview();

	KSJ_SetParam(m_nCamareIndex, KSJ_FLIP, (value == Qt::Checked) ? 1 : 0);
	UpdateDeviceInfo();

	//if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_SensitivityComboBox_currentIndexChanged(int index)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_SensitivitySetMode(m_nCamareIndex, (KSJ_SENSITIVITYMODE)index);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();

}

void CKSJSCZDemoMainWindow::on_GainRedSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_SetParam(m_nCamareIndex, KSJ_RED, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_GainGreenSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_SetParam(m_nCamareIndex, KSJ_GREEN, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_GainBlueSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_SetParam(m_nCamareIndex, KSJ_BLUE, value);
	UpdateDeviceInfo();

	if (bIsCapturing) this->StartPreview();
}

typedef union
{
	struct
	{
		unsigned short  bmTriggerMode0 : 1;           // bit0
		//unsigned short  bmExposureMode : 1;           // bit1 = 0 Short Shutter Mode; = 1 Long Shtter Mode
		unsigned short  bmTriggerMode2 : 1;           // bit1
		unsigned short  bmPixCorrectionOn : 1;        // bit2
		unsigned short  bmPixCorrectionThreshold : 1; // bit3
		unsigned short  bm16BitsTransfer : 1;         // bit4
		unsigned short  bmSensitivityMode : 3;        // bit5:7
		unsigned short  bmEmptyFrameBuffer : 1;       // bit8 由固件判断，=1的时候，将START=0。
		unsigned short  bmTriggerMethod : 2;          // bit9:10
		unsigned short  bmLutEnable : 1;              // bit11 是否加载LUT 16->8 查找表
		unsigned short  bmTriggerMode1 : 1;           // bit12
		unsigned short  bmVITASubsampleMode : 3;      // bit13:15
	}bmValue;
	struct
	{
		unsigned short  bmTriggerMode0 : 1;           // bit0
		unsigned short  bmExposureMode : 1;           // bit1 = 0 Short Shutter Mode; = 1 Long Shtter Mode
		unsigned short  bmPixCorrectionOn : 1;        // bit2
		unsigned short  bmPixCorrectionThreshold : 1; // bit3
		unsigned short  bm16BitsTransfer : 1;         // bit4
		unsigned short  bmSensitivityMode : 3;        // bit5:7
		unsigned short  bmEmptyFrameBuffer : 1;       // bit8 由固件判断，=1的时候，将START=0。
		unsigned short  bmTriggerMethod : 2;          // bit9:10
		unsigned short  bmLutEnable : 1;              // bit11 是否加载LUT 16->8 查找表
		unsigned short  bmTriggerMode1 : 1;           // bit12
		unsigned short  bmStrobeEnable : 1;           // bit13
		unsigned short  bmStrobePolarity : 2;         // bit14:15 00：常态为低电平，高电平脉冲触发（10us）, 01：常态为高电平，低电平脉冲触发（10us）, 10：高电平触发，整个曝光过程保持高电平, 11：低电平触发，整个曝光过程保持高电平
	}bmCcdValue;
	unsigned short    wValue;
}UNION_FPGAREG_WORKING_MODE;    // 对应FPGA的0x00寄存器


typedef union
{
	struct
	{
		unsigned char  bmGammaLutEnable : 1;
	}bmValue;
	unsigned short    wValue;
}UNION_FPGAREG_WORKING_MODE_EX;    // 对应FPGA的0x21寄存器，读取地址为0x21 | 0x80


void CKSJSCZDemoMainWindow::on_ProgramLutPushButton_clicked()
{
	if (m_nCamareIndex < 0) return;

    QString strFilePath = QFileDialog::getOpenFileName(this, "Select lut data file", "", "ktb File(*.ktb);;All Files(*.*)");

	if (!strFilePath.isEmpty())
	{
		int nRet = KSJ_LutFileDownload(m_nCamareIndex, strFilePath.toStdString().c_str());

		UNION_FPGAREG_WORKING_MODE WorkingMode;

		KSJ_WorkingModeReadout(m_nCamareIndex, &WorkingMode.wValue);
		if (WorkingMode.wValue == 0xFFFF)  WorkingMode.wValue = 0;
		WorkingMode.bmValue.bmLutEnable ^= 1;

		KSJ_WorkingModeProgram(m_nCamareIndex, WorkingMode.wValue);

		UNION_FPGAREG_WORKING_MODE_EX WorkingModeEx;

		KSJ_WorkingModeExReadout(m_nCamareIndex, &WorkingModeEx.wValue);

		WorkingModeEx.bmValue.bmGammaLutEnable ^= 1;

        KSJ_WorkingModeExProgram(m_nCamareIndex, WorkingModeEx.wValue);

        int nn = KSJ_LutSetEnable(m_nCamareIndex, true);

        bool bEnable =false;

        KSJ_LutGetEnable(m_nCamareIndex, &bEnable);

		TCHAR szErrorInfo[512] = { '\0' };
		KSJ_GetErrorInfo(nRet, szErrorInfo);


        QMessageBox::about(this, "CatchBEST", QString("%1 - %2 -- %3 - %4").arg(nRet).arg(szErrorInfo).arg(nn).arg(bEnable));
	}
}

bool CKSJSCZDemoMainWindow::StopPreview()
{
	if (m_bCapturingThreadIsWorking)
	{
		KillCaptureThread();
		ui->PreViewPushButton->setText(m_bCapturingThreadIsWorking ? "Stop Preview" : "Start Preview");

		m_pClcFpsTimer->stop();

		return true;
	}

	return false;
}

bool CKSJSCZDemoMainWindow::StartPreview()
{
	m_nFramesCount = 0;
	m_nLastFramesCount = 0;

	if (m_nCamareIndex >= 0)
	{
		StartCaptureThread();
		ui->PreViewPushButton->setText(m_bCapturingThreadIsWorking ? "Stop Preview" : "Start Preview");

		m_pClcFpsTimer->start();

		return true;
	}

	return false;
}

void CKSJSCZDemoMainWindow::InitCnotrol()
{
	ui->TrigetModeComboBox->blockSignals(true);
	ui->TrigetModeComboBox->addItem("Internal");
	ui->TrigetModeComboBox->addItem("External");
	ui->TrigetModeComboBox->addItem("Software");
	ui->TrigetModeComboBox->addItem("Fixed Frame Rate");
	ui->TrigetModeComboBox->addItem("High/Low Fixed Frame Rate");
	ui->TrigetModeComboBox->blockSignals(false);

	ui->TrigetMethodComboBox->blockSignals(true);
	ui->TrigetMethodComboBox->addItem("Falling Edge");
	ui->TrigetMethodComboBox->addItem("Rising Edge");
	ui->TrigetMethodComboBox->addItem("High Level");
	ui->TrigetMethodComboBox->addItem("Low Level");
	ui->TrigetMethodComboBox->blockSignals(false);

	ui->SkipComboBox->blockSignals(true);
	ui->SkipComboBox->addItem("Normal");
	ui->SkipComboBox->addItem("2 x 2 Skip");
	ui->SkipComboBox->addItem("3 x 3 Skip");
	ui->SkipComboBox->addItem("4 x 4 Skip");
	ui->SkipComboBox->addItem("8 x 8 Skip");
	ui->SkipComboBox->blockSignals(false);

	ui->SensitivityComboBox->blockSignals(true);
	ui->SensitivityComboBox->addItem("Low");
	ui->SensitivityComboBox->addItem("Mid");
	ui->SensitivityComboBox->addItem("High");
	ui->SensitivityComboBox->addItem("Higher");
	ui->SensitivityComboBox->addItem("Highest");
	ui->SensitivityComboBox->blockSignals(false);

	ui->WBModeComboBox->blockSignals(true);
	ui->WBModeComboBox->addItem("Disable");
	ui->WBModeComboBox->addItem("Software Presettings");
	ui->WBModeComboBox->addItem("Software Auto Once");
	ui->WBModeComboBox->addItem("Software Auto Continuous");
	ui->WBModeComboBox->addItem("Software Manual");
	ui->WBModeComboBox->addItem("Hardware Presettings");
	ui->WBModeComboBox->addItem("Hardware Auto Once");
	ui->WBModeComboBox->addItem("Hardware Auto Continuous");
	ui->WBModeComboBox->addItem("Hardware Manual");
	ui->WBModeComboBox->blockSignals(false);

	ui->WBPresettingComboBox->blockSignals(true);
	ui->WBPresettingComboBox->addItem("Color Temperature 5000K");
	ui->WBPresettingComboBox->addItem("Color Temperature 6500K");
	ui->WBPresettingComboBox->addItem("Color Temperature 2800K");
	ui->WBPresettingComboBox->blockSignals(false);

	ui->CCMModeComboBox->blockSignals(true);
	ui->CCMModeComboBox->addItem("Disable");
	ui->CCMModeComboBox->addItem("Software Presettings");
	ui->CCMModeComboBox->addItem("Software Manual");
	ui->CCMModeComboBox->addItem("Hardware Presettings");
	ui->CCMModeComboBox->addItem("Hardware Manual");
	ui->CCMModeComboBox->blockSignals(false);

	ui->CCMPresettingComboBox->blockSignals(true);
	ui->CCMPresettingComboBox->addItem("Color Temperature 5000K");
	ui->CCMPresettingComboBox->addItem("Color Temperature 6500K");
	ui->CCMPresettingComboBox->addItem("Color Temperature 2800K");
	ui->CCMPresettingComboBox->blockSignals(false);

	ui->BayerModeComboBox->blockSignals(true);
	ui->BayerModeComboBox->addItem("BGGR to BGR24");
	ui->BayerModeComboBox->addItem("GRBG to BGR24");
	ui->BayerModeComboBox->addItem("RGGB to BGR24");
	ui->BayerModeComboBox->addItem("GBRG to BGR24");
	ui->BayerModeComboBox->addItem("BGGR to BGR24 FLIP");
	ui->BayerModeComboBox->addItem("GRBG to BGR24 FLIP");
	ui->BayerModeComboBox->addItem("RGGB to BGR24 FLIP");
	ui->BayerModeComboBox->addItem("GBRG to BGR24 FLIP");
	ui->BayerModeComboBox->addItem("BGGR to BGR32");
	ui->BayerModeComboBox->addItem("GRBG to BGR32");
	ui->BayerModeComboBox->addItem("RGGB to BGR32");
	ui->BayerModeComboBox->addItem("GBRG to BGR32");
	ui->BayerModeComboBox->addItem("BGGR to BGR32 FLIP");
	ui->BayerModeComboBox->addItem("GRBG to BGR32 FLIP");
	ui->BayerModeComboBox->addItem("RGGB to BGR32 FLIP");
	ui->BayerModeComboBox->addItem("GBRG to BGR32 FLIP");
	ui->BayerModeComboBox->addItem("BGGR to GRAY8");
	ui->BayerModeComboBox->addItem("GRBG to GRAY8");
	ui->BayerModeComboBox->addItem("RGGB to GRAY8");
	ui->BayerModeComboBox->addItem("GBRG to GRAY8");
	ui->BayerModeComboBox->addItem("BGGR to GRAY8 FLIP");
	ui->BayerModeComboBox->addItem("GRBG to GRAY8 FLIP");
	ui->BayerModeComboBox->addItem("RGGB to GRAY8 FLIP");
	ui->BayerModeComboBox->addItem("GBRG to GRAY8 FLIP");
	ui->BayerModeComboBox->blockSignals(false);

	ui->BayerFilterComboBox->blockSignals(true);
	ui->BayerFilterComboBox->addItem("Nearest Neighbor");
	ui->BayerFilterComboBox->addItem("Bilinear");
	ui->BayerFilterComboBox->addItem("Smooth Hue");
	ui->BayerFilterComboBox->addItem("Edge Sensing");
	ui->BayerFilterComboBox->addItem("Laplacian");
	ui->BayerFilterComboBox->addItem("Fast Bilinear");
	ui->BayerFilterComboBox->blockSignals(false);
}

void CKSJSCZDemoMainWindow::UpdateDeviceInfo()
{
	if (m_nCamareIndex == -1) return;

	int nRet;

	int nTriggerModeIndex = 0;
	nRet = KSJ_TriggerModeGet(m_nCamareIndex, (KSJ_TRIGGERMODE*)&nTriggerModeIndex);
	ui->TrigetModeComboBox->blockSignals(true);
	ui->TrigetModeComboBox->setCurrentIndex(nTriggerModeIndex);
	ui->TrigetModeComboBox->blockSignals(false);

	int nTriggerMethodIndex = 0;
	nRet = KSJ_TriggerMethodGet(m_nCamareIndex, (KSJ_TRIGGERMETHOD*)&nTriggerMethodIndex);
	ui->TrigetMethodComboBox->blockSignals(true);
	ui->TrigetMethodComboBox->setCurrentIndex(nTriggerMethodIndex);
	ui->TrigetMethodComboBox->blockSignals(false);


	float fFrameRate = 0;
	nRet = KSJ_GetFixedFrameRateEx(m_nCamareIndex, &fFrameRate);
	ui->FixFrameRateDoubleSpinBox->setValue(fFrameRate);

	ui->FixFrameRateDoubleSpinBox->setEnabled((KSJ_TRIGGERMODE(nTriggerModeIndex)) == KSJ_TRIGGER_FIXFRAMERATE);

#ifdef OLD_KSJAPI
	unsigned long nCaptureTimeout = 0;
#else
	unsigned int nCaptureTimeout = 0;
#endif
	nRet = KSJ_CaptureGetTimeOut(m_nCamareIndex, &nCaptureTimeout);
	ui->CaptureTimeoutSpinBox->setValue(nCaptureTimeout);

	int nColStart;
	int nRowStart;
	int nColSize;
	int nRowSize;
	unsigned short nsMultiFrameNum;
	KSJ_ADDRESSMODE AmCol;
	KSJ_ADDRESSMODE AmRow;

	nRet = KSJ_CaptureGetFieldOfViewEx(m_nCamareIndex, &nColStart, &nRowStart, &nColSize, &nRowSize, &AmCol, &AmRow, &nsMultiFrameNum);

	ui->ColStartSpinBox->blockSignals(true);
	ui->ColStartSpinBox->setValue(nColStart);
	ui->ColStartSpinBox->blockSignals(false);

	ui->ColSizeSpinBox->blockSignals(true);
	ui->ColSizeSpinBox->setValue(nRowStart);
	ui->ColSizeSpinBox->blockSignals(false);

	ui->RowStartSpinBox->blockSignals(true);
	ui->RowStartSpinBox->setValue(nColSize);
	ui->RowStartSpinBox->blockSignals(false);

	ui->RowSizeSpinBox->blockSignals(true);
	ui->RowSizeSpinBox->setValue(nRowSize);
	ui->RowSizeSpinBox->blockSignals(false);

	ui->MultiFrameNumberSpinBox->blockSignals(true);
	ui->MultiFrameNumberSpinBox->setValue(nsMultiFrameNum);
	ui->MultiFrameNumberSpinBox->blockSignals(false);

	ui->SkipComboBox->blockSignals(true);
	ui->SkipComboBox->setCurrentIndex((int)AmCol);
	ui->SkipComboBox->blockSignals(false);

	int nExposureLines = 0;
	nRet = KSJ_GetParam(m_nCamareIndex, KSJ_EXPOSURE_LINES, &nExposureLines);

	ui->ExpoureLineSpinBox->blockSignals(true);
	ui->ExpoureLineSpinBox->setValue(nExposureLines);
	ui->ExpoureLineSpinBox->blockSignals(false);

	float fExposureTime = 0;
	nRet = KSJ_ExposureTimeGet(m_nCamareIndex, &fExposureTime);
	ui->ExposureTimeSpinBox->blockSignals(true);
	ui->ExposureTimeSpinBox->setValue(fExposureTime);
	ui->ExposureTimeSpinBox->blockSignals(false);

	int nMirror = 0;
	KSJ_GetParam(m_nCamareIndex, KSJ_MIRROR, &nMirror);

	ui->MirrorCheckBox->blockSignals(true);
	ui->MirrorCheckBox->setChecked(nMirror != 0);
	ui->MirrorCheckBox->blockSignals(false);

	int nFlip = 0;
	nRet = KSJ_GetParam(m_nCamareIndex, KSJ_FLIP, &nFlip);

	ui->FlipCheckBox->blockSignals(true);
	ui->FlipCheckBox->setChecked(nFlip != 0);
	ui->FlipCheckBox->blockSignals(false);

	KSJ_SENSITIVITYMODE SensitivityMode = KSJ_LOW;
	nRet = KSJ_SensitivityGetMode(m_nCamareIndex, &SensitivityMode);

	ui->SensitivityComboBox->blockSignals(true);
	ui->SensitivityComboBox->setCurrentIndex((int)SensitivityMode);
	ui->SensitivityComboBox->blockSignals(false);

	int nValue = 0;
	nRet = KSJ_GetParam(m_nCamareIndex, KSJ_RED, &nValue);

	ui->GainRedSpinBox->blockSignals(true);
	ui->GainRedSpinBox->setValue((int)nValue);
	ui->GainRedSpinBox->blockSignals(false);

	nRet = KSJ_GetParam(m_nCamareIndex, KSJ_GREEN, &nValue);

	ui->GainGreenSpinBox->blockSignals(true);
	ui->GainGreenSpinBox->setValue((int)nValue);
	ui->GainGreenSpinBox->blockSignals(false);

	nRet = KSJ_GetParam(m_nCamareIndex, KSJ_BLUE, &nValue);

	ui->GainBlueSpinBox->blockSignals(true);
	ui->GainBlueSpinBox->setValue((int)nValue);
	ui->GainBlueSpinBox->blockSignals(false);

	nRet = KSJ_WhiteBalanceGet(m_nCamareIndex, (KSJ_WB_MODE*)&nValue);
	ui->WBModeComboBox->blockSignals(true);
	ui->WBModeComboBox->setCurrentIndex(nValue);
	ui->WBModeComboBox->blockSignals(false);

	KSJ_WhiteBalancePresettingGet(m_nCamareIndex, (KSJ_COLOR_TEMPRATURE*)&nValue);
	ui->WBPresettingComboBox->blockSignals(true);
	ui->WBPresettingComboBox->setCurrentIndex(nValue);
	ui->WBPresettingComboBox->blockSignals(false);

	UpdateWhiteBalanceMatrix();

	KSJ_ColorCorrectionGet(m_nCamareIndex, (KSJ_CCM_MODE*)&nValue);
	ui->CCMModeComboBox->blockSignals(true);
	ui->CCMModeComboBox->setCurrentIndex(nValue);
	ui->CCMModeComboBox->blockSignals(false);

	KSJ_ColorCorrectionPresettingGet(m_nCamareIndex, (KSJ_COLOR_TEMPRATURE*)&nValue);
	ui->CCMPresettingComboBox->blockSignals(true);
	ui->CCMPresettingComboBox->setCurrentIndex(nValue);
	ui->CCMPresettingComboBox->blockSignals(false);

	KSJ_BayerGetMode(m_nCamareIndex, (KSJ_BAYERMODE*)&nValue);
	ui->BayerModeComboBox->blockSignals(true);
	ui->BayerModeComboBox->setCurrentIndex(nValue);
	ui->BayerModeComboBox->blockSignals(false);

	KSJ_FilterGetMode(m_nCamareIndex, (KSJ_FILTERMODE*)&nValue);
	ui->BayerFilterComboBox->blockSignals(true);
	ui->BayerFilterComboBox->setCurrentIndex(nValue);
	ui->BayerFilterComboBox->blockSignals(false);

	UpdateColorCorrectionMatrix();

	bool bStart = false;
	bool bSupport = false;

#ifdef OLD_KSJAPI
	KSJ_IsSupportStreamMode(m_nCamareIndex, &bSupport);
	KSJ_StreamIsStart(m_nCamareIndex, &bStart);
#endif

	ui->StreamModeCheckBox->setChecked(bStart);
	ui->StreamModeCheckBox->setEnabled(bSupport);
}

void __stdcall WBACALLBACK(float fMatrix[3], void *lpContext)
{
	((CKSJSCZDemoMainWindow *)lpContext)->WBACallback(fMatrix);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////自动白平衡
void CKSJSCZDemoMainWindow::WBACallback(float fMatrix[3])
{
	emit sigWBADone(fMatrix[0], fMatrix[1], fMatrix[2]);
}


void CKSJSCZDemoMainWindow::on_WBModeComboBox_currentIndexChanged(int index)
{
	if (m_nCamareIndex == -1) return;

	KSJ_WhiteBalanceAutoSetCallBack(m_nCamareIndex, WBACALLBACK, this);

	KSJ_WhiteBalanceSet(m_nCamareIndex, (KSJ_WB_MODE)index);

	int nValue;
	KSJ_WhiteBalanceGet(m_nCamareIndex, (KSJ_WB_MODE*)&nValue);
	ui->WBModeComboBox->blockSignals(true);
	ui->WBModeComboBox->setCurrentIndex(nValue);
	ui->WBModeComboBox->blockSignals(false);

	UpdateWhiteBalanceMatrix();
}

void CKSJSCZDemoMainWindow::on_WBPresettingComboBox_currentIndexChanged(int index)
{
	if (m_nCamareIndex == -1) return;

	KSJ_WhiteBalancePresettingSet(m_nCamareIndex, (KSJ_COLOR_TEMPRATURE)index);

	int nValue;
	KSJ_WhiteBalancePresettingGet(m_nCamareIndex, (KSJ_COLOR_TEMPRATURE*)&nValue);
	ui->WBPresettingComboBox->blockSignals(true);
	ui->WBPresettingComboBox->setCurrentIndex(nValue);
	ui->WBPresettingComboBox->blockSignals(false);

	UpdateWhiteBalanceMatrix();
}

void CKSJSCZDemoMainWindow::on_WBPHiSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	KSJ_WhiteBalanceAutoSet(m_nCamareIndex, value);
}

void CKSJSCZDemoMainWindow::on_WBRedSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3];

	fMatrix[0] = ui->WBRedSpinBox->value();
	fMatrix[1] = ui->WBGreenSpinBox->value();
	fMatrix[2] = ui->WBBlueSpinBox->value();

	KSJ_WhiteBalanceMatrixSet(m_nCamareIndex, fMatrix);

}

void CKSJSCZDemoMainWindow::on_WBGreenSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3];

	fMatrix[0] = ui->WBRedSpinBox->value();
	fMatrix[1] = ui->WBGreenSpinBox->value();
	fMatrix[2] = ui->WBBlueSpinBox->value();

	KSJ_WhiteBalanceMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_WBBlueSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3];

	fMatrix[0] = ui->WBRedSpinBox->value();
	fMatrix[1] = ui->WBGreenSpinBox->value();
	fMatrix[2] = ui->WBBlueSpinBox->value();

	KSJ_WhiteBalanceMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_ProgramWBMatrixPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3];

	fMatrix[0] = ui->WBRedSpinBox->value();
	fMatrix[1] = ui->WBGreenSpinBox->value();
	fMatrix[2] = ui->WBBlueSpinBox->value();

	KSJ_HWBMatrixProgram(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::OnWBADone(float r, float g, float b)
{
	ui->WBRedSpinBox->blockSignals(true);
	ui->WBGreenSpinBox->blockSignals(true);
	ui->WBBlueSpinBox->blockSignals(true);
	ui->WBRedSpinBox->setValue(r);
	ui->WBGreenSpinBox->setValue(g);
	ui->WBBlueSpinBox->setValue(b);
	ui->WBRedSpinBox->blockSignals(false);
	ui->WBGreenSpinBox->blockSignals(false);
	ui->WBBlueSpinBox->blockSignals(false);
}

void CKSJSCZDemoMainWindow::EnableWhiteBalanceMatrixControls(bool bEnable)
{
	ui->WBRedSpinBox->setEnabled(bEnable);
	ui->WBGreenSpinBox->setEnabled(bEnable);
	ui->WBBlueSpinBox->setEnabled(bEnable);
}

void CKSJSCZDemoMainWindow::UpdateWhiteBalanceMatrix()
{
	if (m_nCamareIndex == -1) return;

	int nWbMode = ui->WBModeComboBox->currentIndex();

	if (nWbMode == KSJ_WB_DISABLE)                EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_SWB_AUTO_ONCE)        EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_SWB_AUTO_CONITNUOUS)  EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_SWB_PRESETTINGS)      EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_SWB_MANUAL)           EnableWhiteBalanceMatrixControls(true);
	else if (nWbMode == KSJ_HWB_AUTO_ONCE)        EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_HWB_AUTO_CONITNUOUS)  EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_HWB_PRESETTINGS)      EnableWhiteBalanceMatrixControls(false);
	else if (nWbMode == KSJ_HWB_MANUAL)           EnableWhiteBalanceMatrixControls(true);

	if (nWbMode == KSJ_WB_DISABLE)                ui->WBPresettingComboBox->setEnabled(false);
	else if (nWbMode == KSJ_SWB_AUTO_ONCE)        ui->WBPresettingComboBox->setEnabled(false);
	else if (nWbMode == KSJ_SWB_AUTO_CONITNUOUS)  ui->WBPresettingComboBox->setEnabled(false);
	else if (nWbMode == KSJ_SWB_PRESETTINGS)      ui->WBPresettingComboBox->setEnabled(true);
	else if (nWbMode == KSJ_SWB_MANUAL)           ui->WBPresettingComboBox->setEnabled(false);
	else if (nWbMode == KSJ_HWB_AUTO_ONCE)        ui->WBPresettingComboBox->setEnabled(false);
	else if (nWbMode == KSJ_HWB_AUTO_CONITNUOUS)  ui->WBPresettingComboBox->setEnabled(false);
	else if (nWbMode == KSJ_HWB_PRESETTINGS)      ui->WBPresettingComboBox->setEnabled(true);
	else if (nWbMode == KSJ_HWB_MANUAL)           ui->WBPresettingComboBox->setEnabled(false);

	if (nWbMode == KSJ_WB_DISABLE)
	{
		ui->WBPHiSpinBox->setEnabled(false);
	}
	else if (nWbMode == KSJ_SWB_AUTO_ONCE)
	{
		ui->WBPHiSpinBox->setEnabled(true);
	}
	else if (nWbMode == KSJ_SWB_AUTO_CONITNUOUS)
	{
		ui->WBPHiSpinBox->setEnabled(true);
	}
	else if (nWbMode == KSJ_SWB_PRESETTINGS)
	{
		ui->WBPHiSpinBox->setEnabled(false);
	}
	else if (nWbMode == KSJ_SWB_MANUAL)
	{
		ui->WBPHiSpinBox->setEnabled(false);
	}
	else if (nWbMode == KSJ_HWB_AUTO_ONCE)
	{
		ui->WBPHiSpinBox->setEnabled(false);
	}
	else if (nWbMode == KSJ_HWB_AUTO_CONITNUOUS)
	{
		ui->WBPHiSpinBox->setEnabled(false);
	}
	else if (nWbMode == KSJ_HWB_MANUAL)
	{
		ui->WBPHiSpinBox->setEnabled(false);
	}

	float fWBMatrix[3];
	KSJ_WhiteBalanceMatrixGet(m_nCamareIndex, fWBMatrix);

	ui->WBRedSpinBox->blockSignals(true);
	ui->WBGreenSpinBox->blockSignals(true);
	ui->WBBlueSpinBox->blockSignals(true);
	ui->WBRedSpinBox->setValue(fWBMatrix[0]);
	ui->WBGreenSpinBox->setValue(fWBMatrix[1]);
	ui->WBBlueSpinBox->setValue(fWBMatrix[2]);
	ui->WBRedSpinBox->blockSignals(false);
	ui->WBGreenSpinBox->blockSignals(false);
	ui->WBBlueSpinBox->blockSignals(false);
}

void CKSJSCZDemoMainWindow::on_CCMModeComboBox_currentIndexChanged(int index)
{
	if (m_nCamareIndex == -1) return;

	KSJ_ColorCorrectionSet(m_nCamareIndex, (KSJ_CCM_MODE)index);

	int nValue;
	KSJ_ColorCorrectionGet(m_nCamareIndex, (KSJ_CCM_MODE*)&nValue);
	ui->CCMModeComboBox->blockSignals(true);
	ui->CCMModeComboBox->setCurrentIndex(nValue);
	ui->CCMModeComboBox->blockSignals(false);

	UpdateColorCorrectionMatrix();
}

void CKSJSCZDemoMainWindow::on_CCMPresettingComboBox_currentIndexChanged(int index)
{
	if (m_nCamareIndex == -1) return;

	KSJ_ColorCorrectionPresettingSet(m_nCamareIndex, (KSJ_COLOR_TEMPRATURE)index);

	int nValue;
	KSJ_ColorCorrectionPresettingGet(m_nCamareIndex, (KSJ_COLOR_TEMPRATURE*)&nValue);
	ui->CCMPresettingComboBox->blockSignals(true);
	ui->CCMPresettingComboBox->setCurrentIndex(nValue);
	ui->CCMPresettingComboBox->blockSignals(false);

	UpdateColorCorrectionMatrix();
}

void CKSJSCZDemoMainWindow::on_CCM00SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM01SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM02SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM10SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM11SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM12SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM20SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM21SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_CCM22SpinBox_valueChanged(double)
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_ColorCorrectionMatrixSet(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::on_ProgramCCMMatrixPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	float fMatrix[3][3];

	fMatrix[0][0] = ui->CCM00SpinBox->value();
	fMatrix[0][1] = ui->CCM01SpinBox->value();
	fMatrix[0][2] = ui->CCM02SpinBox->value();
	fMatrix[1][0] = ui->CCM10SpinBox->value();
	fMatrix[1][1] = ui->CCM11SpinBox->value();
	fMatrix[1][2] = ui->CCM12SpinBox->value();
	fMatrix[2][0] = ui->CCM20SpinBox->value();
	fMatrix[2][1] = ui->CCM21SpinBox->value();
	fMatrix[2][2] = ui->CCM22SpinBox->value();

	KSJ_HCCMMatrixProgram(m_nCamareIndex, fMatrix);
}

void CKSJSCZDemoMainWindow::UpdateColorCorrectionMatrix()
{
	if (m_nCamareIndex == -1) return;

	int nCcmMode = ui->CCMModeComboBox->currentIndex();

	if (nCcmMode == KSJ_CCM_DISABLE)           EnableColorCorrectionMatrixControls(false);
	else if (nCcmMode == KSJ_SCCM_PRESETTINGS) EnableColorCorrectionMatrixControls(false);
	else if (nCcmMode == KSJ_SCCM_MANUAL)      EnableColorCorrectionMatrixControls(true);
	else if (nCcmMode == KSJ_HCCM_PRESETTINGS) EnableColorCorrectionMatrixControls(false);
	else if (nCcmMode == KSJ_HCCM_MANUAL)      EnableColorCorrectionMatrixControls(true);

	if (nCcmMode == KSJ_CCM_DISABLE)           ui->CCMPresettingComboBox->setEnabled(false);
	else if (nCcmMode == KSJ_SCCM_PRESETTINGS) ui->CCMPresettingComboBox->setEnabled(true);
	else if (nCcmMode == KSJ_SCCM_MANUAL)      ui->CCMPresettingComboBox->setEnabled(false);
	else if (nCcmMode == KSJ_HCCM_PRESETTINGS) ui->CCMPresettingComboBox->setEnabled(true);
	else if (nCcmMode == KSJ_HCCM_MANUAL)      ui->CCMPresettingComboBox->setEnabled(false);

	float fMatrix[3][3];
	KSJ_ColorCorrectionMatrixGet(m_nCamareIndex, fMatrix);

	ui->CCM00SpinBox->blockSignals(true);
	ui->CCM01SpinBox->blockSignals(true);
	ui->CCM02SpinBox->blockSignals(true);
	ui->CCM10SpinBox->blockSignals(true);
	ui->CCM11SpinBox->blockSignals(true);
	ui->CCM12SpinBox->blockSignals(true);
	ui->CCM20SpinBox->blockSignals(true);
	ui->CCM21SpinBox->blockSignals(true);
	ui->CCM22SpinBox->blockSignals(true);
	ui->CCM00SpinBox->setValue(fMatrix[0][0]);
	ui->CCM01SpinBox->setValue(fMatrix[0][1]);
	ui->CCM02SpinBox->setValue(fMatrix[0][2]);
	ui->CCM10SpinBox->setValue(fMatrix[1][0]);
	ui->CCM11SpinBox->setValue(fMatrix[1][1]);
	ui->CCM12SpinBox->setValue(fMatrix[1][2]);
	ui->CCM20SpinBox->setValue(fMatrix[2][0]);
	ui->CCM21SpinBox->setValue(fMatrix[2][1]);
	ui->CCM22SpinBox->setValue(fMatrix[2][2]);
	ui->CCM00SpinBox->blockSignals(false);
	ui->CCM01SpinBox->blockSignals(false);
	ui->CCM02SpinBox->blockSignals(false);
	ui->CCM10SpinBox->blockSignals(false);
	ui->CCM11SpinBox->blockSignals(false);
	ui->CCM12SpinBox->blockSignals(false);
	ui->CCM20SpinBox->blockSignals(false);
	ui->CCM21SpinBox->blockSignals(false);
	ui->CCM22SpinBox->blockSignals(false);
}

void CKSJSCZDemoMainWindow::EnableColorCorrectionMatrixControls(bool bEnable)
{
	ui->CCM00SpinBox->setEnabled(bEnable);
	ui->CCM01SpinBox->setEnabled(bEnable);
	ui->CCM02SpinBox->setEnabled(bEnable);
	ui->CCM10SpinBox->setEnabled(bEnable);
	ui->CCM11SpinBox->setEnabled(bEnable);
	ui->CCM12SpinBox->setEnabled(bEnable);
	ui->CCM20SpinBox->setEnabled(bEnable);
	ui->CCM21SpinBox->setEnabled(bEnable);
	ui->CCM22SpinBox->setEnabled(bEnable);
}

void CKSJSCZDemoMainWindow::on_PragramSettingsPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet = KSJ_ParamProgram(m_nCamareIndex);

	if (bIsCapturing) this->StartPreview();

	TCHAR szErrorInfo[512] = { '\0' };
	KSJ_GetErrorInfo(nRet, szErrorInfo);
	QMessageBox::about(this, "CatchBEST", szErrorInfo);
}

void CKSJSCZDemoMainWindow::on_ClearSettingsPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet = KSJ_ParamErase(m_nCamareIndex);

	if (bIsCapturing) this->StartPreview();

	TCHAR szErrorInfo[512] = { '\0' };
	KSJ_GetErrorInfo(nRet, szErrorInfo);
	QMessageBox::about(this, "CatchBEST", szErrorInfo);
}

static QVector<QRgb> grayTable;

void CKSJSCZDemoMainWindow::TransferImageData(unsigned char* pImageData, int w, int h, int bc, unsigned int nTimeOutMS)
{
	if (bc != 8 && bc != 24 && bc != 32) return;

	if (m_DataLocker.tryLock(nTimeOutMS))
	{
		if (m_nImgWidth != w || m_nImgHeight != h || m_nImgBitCount != bc)
		{
			m_nImgWidth = w;
			m_nImgHeight = h;
			m_nImgBitCount = bc;

			if (m_pTempImageData != NULL)
			{
				delete[]m_pTempImageData;
				m_pTempImageData = NULL;
			}

			m_pTempImageData = new unsigned char[m_nImgWidth*m_nImgHeight*m_nImgBitCount / 8];
		}

		memcpy(m_pTempImageData, pImageData, m_nImgWidth*m_nImgHeight*m_nImgBitCount / 8);

		m_bHasNewData = true;

		m_DataLocker.unlock();

		update();
	}
}

void CKSJSCZDemoMainWindow::ProcessCaptureData()
{
	if (!m_bHasNewData) return;
	if (m_pTempImageData == NULL) return;

	m_DataLocker.lock();
	m_ImageLocker.lock();

	// 如果图像大小有改变，把老的m_pImage删除掉
	if (m_pImage != NULL && (m_pImage->width() != m_nImgWidth || m_pImage->height() != m_nImgHeight))
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if (m_nImgBitCount == 8)
	{
		if (m_pImage != NULL && m_pImage->format() != QImage::Format_Indexed8)
		{
			delete m_pImage;
			m_pImage = NULL;
		}

		if (m_pImage == NULL)
		{

			m_pImage = new QImage(m_nImgWidth, m_nImgHeight, QImage::Format_Indexed8);

			if (grayTable.size() <= 0)
			{
				for (int i = 0; i < 256; i++) grayTable.push_back(qRgb(i, i, i));
			}

			m_pImage->setColorTable(grayTable);
		}

		memcpy(m_pImage->bits(), m_pTempImageData, m_nImgWidth*m_nImgHeight*m_nImgBitCount / 8);
	}
	else if (m_nImgBitCount == 24)
	{
		if (m_pImage != NULL && m_pImage->format() != QImage::Format_RGB888)
		{
			delete m_pImage;
			m_pImage = NULL;
		}

		if (m_pImage == NULL)
		{
			m_pImage = new QImage(m_nImgWidth, m_nImgHeight, QImage::Format_RGB888);
		}

		unsigned char* pData = m_pImage->bits();

		//memcpy(pData, m_pTempImageData, m_nImgWidth*m_nImgHeight * 3);

		for (int j = 0; j < m_nImgHeight; ++j)
		{
			for (int i = 0; i < m_nImgWidth; ++i)
			{
				pData[(m_nImgHeight - j - 1) * 3 * m_nImgWidth + 3 * i + 0] = m_pTempImageData[j * 3 * m_nImgWidth + 3 * i + 2];
				pData[(m_nImgHeight - j - 1) * 3 * m_nImgWidth + 3 * i + 1] = m_pTempImageData[j * 3 * m_nImgWidth + 3 * i + 1];
				pData[(m_nImgHeight - j - 1) * 3 * m_nImgWidth + 3 * i + 2] = m_pTempImageData[j * 3 * m_nImgWidth + 3 * i + 0];
			}
		}
	}
	else if (m_nImgBitCount == 32)
	{
		if (m_pImage != NULL && m_pImage->format() != QImage::Format_RGBA8888)
		{
			delete m_pImage;
			m_pImage = NULL;
		}

		if (m_pImage == NULL)
		{
			m_pImage = new QImage(m_nImgWidth, m_nImgHeight, QImage::Format_RGBA8888);
		}

		unsigned char* pData = m_pImage->bits();

		memcpy(pData, m_pTempImageData, m_nImgWidth*m_nImgHeight * 4);
	}

	m_bHasNewData = false;

	m_DataLocker.unlock();
	m_ImageLocker.unlock();

	if (m_bSaveImage)
	{
		m_strImagePath = m_strImagePreFix + QString("%1.bmp").arg(m_nSnapCount, 3, 10, QChar('0'));

		++m_nSnapCount;

		if (m_pImage->save(m_strImagePath))
		{
			if (m_fCaptureUseMS > 0.0f)
			{
				ui->SnapCountLabel->setText(QString("Snap finished, capture data use %1 MS").arg(QString::number(m_fCaptureUseMS, 'f', 2)));
			}
			else
			{
				ui->SnapCountLabel->setText("Snap count : " + QString::number(m_nSnapCount));
			}

			m_bSaveImage = false;
		}
	}
}

void CKSJSCZDemoMainWindow::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
	}
}

void CKSJSCZDemoMainWindow::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
	}
}

void CKSJSCZDemoMainWindow::mouseMoveEvent(QMouseEvent * e)
{
}

void CKSJSCZDemoMainWindow::mouseDoubleClickEvent(QMouseEvent * e)
{
}

void CKSJSCZDemoMainWindow::wheelEvent(QWheelEvent * event)
{
}

void CKSJSCZDemoMainWindow::on_EmptyBufferPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet = KSJ_EmptyFrameBuffer(m_nCamareIndex);
	//UpdateDeviceInfo();

	//if (bIsCapturing) this->StartPreview();

	QMessageBox::about(this, "CatchBEST", QString("Result = %1").arg(nRet));
}

void CKSJSCZDemoMainWindow::on_CaptureRGBPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet;
	int nWidth;
	int nHeight;
	int nBitCount;
	int nBufferSize = 0;
	unsigned char* pImageBuffer = NULL;

	nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);

	if (nRet == RET_SUCCESS)
	{
		pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];

		nRet = KSJ_CaptureRgbData(m_nCamareIndex, pImageBuffer);

		if (nRet == RET_SUCCESS)
		{
			// 采集图像以后，将内存数据转换成QImage数据,这样pImageData的数据就被转移到QImage里面，以后可以自己进行算法操作
			TransferImageData(pImageBuffer, nWidth, nHeight, nBitCount, 200);
		}

		delete[]pImageBuffer;
	}

	QMessageBox::about(this, "CatchBEST", QString("Result = %1").arg(nRet));
}

void CKSJSCZDemoMainWindow::on_CaptureRawPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	int nRet;
	int nWidth;
	int nHeight;
	int nBitCount;
	int nBufferSize = 0;
	unsigned char* pImageBuffer = NULL;

	nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);

	if (nRet == RET_SUCCESS)
	{
		pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];

		nRet = KSJ_CaptureRawData(m_nCamareIndex, pImageBuffer);

		if (nRet == RET_SUCCESS)
		{
			// 采集图像以后，将内存数据转换成QImage数据,这样pImageData的数据就被转移到QImage里面，以后可以自己进行算法操作
			TransferImageData(pImageBuffer, nWidth, nHeight, 8, 200);
		}

		delete[]pImageBuffer;
	}

	QMessageBox::about(this, "CatchBEST", QString("Result = %1").arg(nRet));
}
#ifdef OLD_KSJAPI
#include "KSJApiStream.h"
#endif

void CKSJSCZDemoMainWindow::on_TestingPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

#ifdef OLD_KSJAPI

	int nRet;
	int nWidth;
	int nHeight;
	int nBitCount;
	int nBufferSize = 0;
	unsigned char* pImageBuffer = NULL;

	for (int i = 0; i < 5; ++i)
	{
		if (i == 0)
		{
			KSJ_BAYERMODE BayerMode;

			KSJ_BayerGetDefaultMode(0, &BayerMode);
			KSJ_BayerSetMode(0, BayerMode);
		}
		else if (i == 2)
		{
		}

		nRet = KSJ_CaptureSetFieldOfView(0, 616, 0, 1232, 2056, KSJ_SKIPNONE, KSJ_SKIP8);

		nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);

		if (nRet == RET_SUCCESS)
		{
			pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];

			nRet = KSJ_CaptureRgbData(m_nCamareIndex, pImageBuffer);

			if (nRet == RET_SUCCESS)
			{
				// 采集图像以后，将内存数据转换成QImage数据,这样pImageData的数据就被转移到QImage里面，以后可以自己进行算法操作
				TransferImageData(pImageBuffer, nWidth, nHeight, nBitCount, 200);
			}
			else
			{
				int kk = 0;
			}

			delete[]pImageBuffer;
			pImageBuffer = NULL;
		}

		for (int j = 0; j < 1000; ++j)
		{
			Sleep(2);
		}
	}


	//unsigned int nDataSize = 0;

	//for (int i = 0; i < 1; ++i)
	//{
	//	nRet = KSJ_StreamStop(0);
	//	QMessageBox::about(NULL, "KSJ_StreamStop - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_CaptureSetFieldOfView(0, 0, 120, 728, 240, KSJ_SKIPNONE, KSJ_SKIPNONE);
	//	QMessageBox::about(NULL, "KSJ_CaptureSetFieldOfView - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_StreamStart(0);
	//	QMessageBox::about(NULL, "KSJ_StreamStart - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);
	//	QMessageBox::about(NULL, "KSJ_CaptureGetSizeEx - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];
	//	nRet = KSJ_StreamReadRawDataEx(0, pImageBuffer, &nDataSize);
	//	QMessageBox::about(NULL, "KSJ_StreamReadRawDataEx - Result", QString("nRet=%1, nWidth=%2, nHeight=%3, nBitCount=%4, (%5) nDataSize=%6").arg(nRet).arg(nWidth).arg(nHeight).arg(nBitCount).arg(nWidth*nHeight*nBitCount / 8).arg(nDataSize));
	//	delete[]pImageBuffer;

	//	nRet = KSJ_StreamStop(0);
	//	QMessageBox::about(NULL, "KSJ_StreamStop - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_CaptureSetFieldOfView(0, 0, 120, 728, 32, KSJ_SKIPNONE, KSJ_SKIPNONE);
	//	QMessageBox::about(NULL, "KSJ_CaptureSetFieldOfView - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_StreamStart(0);
	//	QMessageBox::about(NULL, "KSJ_StreamStart - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);
	//	QMessageBox::about(NULL, "KSJ_CaptureGetSizeEx - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];
	//	nRet = KSJ_StreamReadRawDataEx(0, pImageBuffer, &nDataSize);
	//	QMessageBox::about(NULL, "KSJ_StreamReadRawDataEx - Result", QString("nRet=%1, nWidth=%2, nHeight=%3, nBitCount=%4, (%5) nDataSize=%6").arg(nRet).arg(nWidth).arg(nHeight).arg(nBitCount).arg(nWidth*nHeight*nBitCount / 8).arg(nDataSize));
	//	delete[]pImageBuffer;

	//	nRet = KSJ_StreamStop(0);
	//	QMessageBox::about(NULL, "KSJ_StreamStop - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_CaptureSetFieldOfView(0, 0, 0, 728, 544, KSJ_SKIPNONE, KSJ_SKIPNONE);
	//	QMessageBox::about(NULL, "KSJ_CaptureSetFieldOfView - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_StreamStart(0);
	//	QMessageBox::about(NULL, "KSJ_StreamStart - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	nRet = KSJ_CaptureGetSizeEx(m_nCamareIndex, &nWidth, &nHeight, &nBitCount);
	//	QMessageBox::about(NULL, "KSJ_CaptureGetSizeEx - Result", QString("=================== nRet=%1 ===================").arg(nRet));
	//	pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];
	//	nRet = KSJ_StreamReadRawDataEx(0, pImageBuffer, &nDataSize);
	//	QMessageBox::about(NULL, "KSJ_StreamReadRawDataEx - Result", QString("nRet=%1, nWidth=%2, nHeight=%3, nBitCount=%4, (%5) nDataSize=%6").arg(nRet).arg(nWidth).arg(nHeight).arg(nBitCount).arg(nWidth*nHeight*nBitCount / 8).arg(nDataSize));
	//	delete[]pImageBuffer;
	//}


	//	if (nRet == RET_SUCCESS)
	//	{
	//		pImageBuffer = new unsigned char[nWidth*nHeight*nBitCount / 8];
	//
	//		unsigned int nDataSize;
	//#ifdef OLD_KSJAPI
	//		nRet = KSJ_StreamReadRawDataEx(m_nCamareIndex, pImageBuffer, &nDataSize);
	//		if (nDataSize > 0)
	//#else
	//		nRet = KSJ_CaptureRawData(m_nCamareIndex, pImageBuffer);
	//		if (nRet==RET_SUCCESS)
	//#endif
	//		{
	//			// 采集图像以后，将内存数据转换成QImage数据,这样pImageData的数据就被转移到QImage里面，以后可以自己进行算法操作
	//			TransferImageData(pImageBuffer, nWidth, nHeight, nBitCount);
	//		}
	//		else
	//		{
	//			int kk = 0;
	//		}
	//
	//		delete[]pImageBuffer;
	//		pImageBuffer = NULL;
	//	}



#endif

	//pImageBuffer = new unsigned char[4608 * 3288 * 3]; 

	//nRet = KSJ_CaptureRgbData(m_nCamareIndex, pImageBuffer);

	//delete []pImageBuffer;

}

void CKSJSCZDemoMainWindow::on_SendEndMsgPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;
#ifdef OLD_KSJAPI
	KSJ_SendPktEnd(m_nCamareIndex);
#endif
}

void CKSJSCZDemoMainWindow::on_ResetHostPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;
#ifdef OLD_KSJAPI
	KSJ_ResetDevice(m_nCamareIndex);
	KSJ_ResetHost(m_nCamareIndex);
#endif
}

void CKSJSCZDemoMainWindow::on_BayerModeComboBox_currentIndexChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_BayerSetMode(m_nCamareIndex, (KSJ_BAYERMODE)value);

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_BayerFilterComboBox_currentIndexChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	bool bIsCapturing = this->StopPreview();

	KSJ_FilterSetMode(m_nCamareIndex, (KSJ_FILTERMODE)value);

	if (bIsCapturing) this->StartPreview();
}

void CKSJSCZDemoMainWindow::on_DefaultBayerPushButton_clicked()
{
	if (m_nCamareIndex == -1) return;

	KSJ_BAYERMODE BayerMode;
	KSJ_BayerGetDefaultMode(m_nCamareIndex, &BayerMode);

	if (ui->BayerModeComboBox->currentIndex() != BayerMode)
	{
		bool bIsCapturing = this->StopPreview();

		KSJ_BayerSetMode(m_nCamareIndex, BayerMode);

		ui->BayerModeComboBox->blockSignals(true);
		ui->BayerModeComboBox->setCurrentIndex(BayerMode);
		ui->BayerModeComboBox->blockSignals(false);

		if (bIsCapturing) this->StartPreview();
	}
}

void CKSJSCZDemoMainWindow::on_OnlyCaptureCheckBox_stateChanged(int value)
{
	m_bShowImage = (value == Qt::Checked) ? 0 : 1;
}

#include <QDebug>

void CKSJSCZDemoMainWindow::OnClcFpsTimer()
{
	if (m_nClcFpsTickCount < 0) return;

	if (m_nClcFpsTickCount == 0)
	{
#ifdef _WIN32
		QueryPerformanceFrequency(&m_lifrqc);  // 取得高精度运行计数器的频率f,单位是每秒多少次（n/s）,  
		QueryPerformanceCounter(&m_litmp1);    // 取得高精度运行计数器的数值
#else
		gettimeofday(&m_start, NULL);
#endif
	}
	else
	{
#ifdef _WIN32
		QueryPerformanceCounter(&m_litmp2); // 取得高精度运行计数器的数值
		float fRunTimeS = (m_litmp2.QuadPart - m_litmp1.QuadPart) * 1000.f / m_lifrqc.QuadPart / 1000.0f;//获得对应时间,单位为微秒

		m_litmp1 = m_litmp2;
#else
		gettimeofday(&m_end, NULL);
		float fRunTimeS = ((m_end.tv_sec - m_start.tv_sec) * 1000.0f + (m_end.tv_usec - m_start.tv_usec) / 1000.0f) / 1000.0f;

		m_start = m_end;
#endif

		float fFps = (m_nFramesCount - m_nLastFramesCount) / fRunTimeS;
		
		printf("=============%d  %d  %.2f S ==============\n", m_nFramesCount, m_nFramesCount - m_nLastFramesCount, fRunTimeS);

		ui->FPSLabel->setText(QString("%1 fps").arg(QString::number(fFps, 'f', 2)));
	}

	m_nLastFramesCount = m_nFramesCount;

	++m_nClcFpsTickCount;
}

void CKSJSCZDemoMainWindow::on_PeakAveSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	KSJ_AESetPeakAveRatio(m_nCamareIndex, value);

	KSJ_AEGetPeakAveRatio(m_nCamareIndex, &m_fAePeakAveRatio);

	ui->PeakAveSpinBox->blockSignals(true);
	ui->PeakAveSpinBox->setValue(m_fAePeakAveRatio);
	ui->PeakAveSpinBox->blockSignals(false);
}

void CKSJSCZDemoMainWindow::on_MaxAEDoubleSpinBox_valueChanged(double value)
{
	if (m_nCamareIndex == -1) return;

	KSJ_AESetExposureTimeRange(m_nCamareIndex, 0, value);

	m_fAEMaxExposureTime = value;
}

void CKSJSCZDemoMainWindow::on_TargetBrightnessSpinBox_valueChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	KSJ_AESetTarget(m_nCamareIndex, value);

	m_nAETarget = value;
}

#define  AE_MAX_COUNT_DEF 20

void CKSJSCZDemoMainWindow::on_ContinuousAECheckBox_stateChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	m_nAEMaxCount = (value == Qt::Checked) ? -1 : AE_MAX_COUNT_DEF;

	KSJ_AESetMaxCount(m_nCamareIndex, m_nAEMaxCount);
}

void CKSJSCZDemoMainWindow::on_ShowAERegionCheckBox_stateChanged(int value)
{
	if (m_nCamareIndex == -1) return;

	m_bAEShowRegion = (value == Qt::Checked);

	KSJ_AEShowRegion(m_nCamareIndex, m_bAEShowRegion);
}

void CKSJSCZDemoMainWindow::on_AutoExposureCheckBox_stateChanged(int value)
{
	m_bIsDoAutoExposure = (value == Qt::Checked);

	AEStart(m_bIsDoAutoExposure);
}

#ifdef OLD_KSJAPI
void __stdcall AECALLBACKEX(KSJ_AE_STATUS AEStatus, int fExpsoureTimeMs, void *lpContext)
#else
void __stdcall AECALLBACKEX(KSJ_AE_STATUS AEStatus, float fExpsoureTimeMs, void *lpContext)
#endif
{
	((CKSJSCZDemoMainWindow *)lpContext)->AeCallbackEx(AEStatus, fExpsoureTimeMs);
}

void CKSJSCZDemoMainWindow::AeCallbackEx(KSJ_AE_STATUS AEStatus, float fExpsoureTimeMs)
{
	emit sigAEFinishMsg(int(AEStatus), fExpsoureTimeMs);
}


void CKSJSCZDemoMainWindow::AEStart(bool bStart)
{
	if (m_nCamareIndex == -1)    return;

	KSJ_AESetCallbackEx(m_nCamareIndex, AECALLBACKEX, this);
	KSJ_AESetMaxCount(m_nCamareIndex, m_nAEMaxCount);
	KSJ_AEStartEx(m_nCamareIndex, bStart);

	emit sigAEStartMsg(bStart);
}

void CKSJSCZDemoMainWindow::OnAEStartMsg(bool bStart)
{
	ui->AutoExposureCheckBox->setChecked(bStart);
}

const char *g_szAEStatus[] =
{
	"Once Success",
	"Once Fail Max Count",
	"Once Fail Wave",
	"Once Fail Over Range",
	"Doing",
	"Continue Success",
	"Continue Fail Wave",
	"Continue Fail Over Range",
};

void CKSJSCZDemoMainWindow::OnAEFinishMsg(int nAEStatus, float fExpsoureTimeMs)
{
	int nExposureLines = 0;

	if (KSJ_GetParam(m_nCamareIndex, KSJ_EXPOSURE_LINES, &nExposureLines) == RET_SUCCESS)
	{
		ui->ExpoureLineSpinBox->blockSignals(true);
		ui->ExpoureLineSpinBox->setValue(nExposureLines);
		ui->ExpoureLineSpinBox->blockSignals(false);
	}

	ui->ExposureTimeSpinBox->blockSignals(true);
	ui->ExposureTimeSpinBox->setValue(fExpsoureTimeMs);
	ui->ExposureTimeSpinBox->blockSignals(false);

	ui->AutoExposureStatusLabel->setText(g_szAEStatus[nAEStatus]);

	if (nAEStatus == KSJ_AE_ONCE_SUCCESS ||
		nAEStatus == KSJ_AE_ONCE_FAIL_MAX_COUNT ||
		nAEStatus == KSJ_AE_ONCE_FAIL_WAVE ||
		nAEStatus == KSJ_AE_ONCE_FAIL_OVER_RANGE)
	{
		ui->AutoExposureCheckBox->setChecked(false);
	}
	else
	{
		ui->AutoExposureCheckBox->setChecked(true);
	}
}

void CKSJSCZDemoMainWindow::on_StreamModeCheckBox_stateChanged(int value)
{
	if (m_nCamareIndex == -1)    return;

	bool bStart = (value == Qt::Checked);
#ifdef OLD_KSJAPI
	if (bStart)
	{
		KSJ_StreamStart(m_nCamareIndex);
	}
	else
	{
		KSJ_StreamStop(m_nCamareIndex);
	}
#endif
}

void CKSJSCZDemoMainWindow::on_UsbStatusPushButton_clicked()
{
	if (m_nCamareIndex == -1)    return;
#ifdef OLD_KSJAPI
	KSJ_USBSPEED speed = USB_NOT_CONNECTED;

	KSJ_GetUsbState(m_nCamareIndex, &speed);

	if (speed == USB_NOT_CONNECTED)
	{
		QMessageBox::about(NULL, "USB Status", "Not Connected!");
	}
	else if (speed == USB_FULL_SPEED)
	{
		QMessageBox::about(NULL, "USB Status", "USB 2.0 (Full)");
	}
	else if (speed == USB_HIGH_SPEED)
	{
		QMessageBox::about(NULL, "USB Status", "USB 2.0 (High)");
	}
	else if (speed == USB_SUPER_SPEED)
	{
		QMessageBox::about(NULL, "USB Status", "USB 3.0");
	}
#endif
}

void CKSJSCZDemoMainWindow::on_RebootDevicePushButton_clicked()
{
	if (m_nCamareIndex == -1)    return;
#ifdef OLD_KSJAPI
	KSJ_RebootDevice(m_nCamareIndex);
#endif
}
