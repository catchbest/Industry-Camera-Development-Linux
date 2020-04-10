#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QMatrix>
#include <QMutex>

#ifdef OLD_KSJAPI
#ifdef  UNICODE                     // r_winnt
typedef wchar_t TCHAR;
#else   /* UNICODE */               // r_winnt
typedef char TCHAR;
#endif

#define CALLBACK    __stdcall
#endif

#include "KSJApi.h"
#include "KSJApiInternal.h"

#ifdef _WIN32
#include <windows.h>
#endif


namespace Ui { class KSJSCZDemoMainWindow; }

class CKSJSCZDemoMainWindow : public QDialog
{
	Q_OBJECT

public:
	explicit CKSJSCZDemoMainWindow(QWidget *parent = 0);
	~CKSJSCZDemoMainWindow();

private:
	Ui::KSJSCZDemoMainWindow *ui;

signals:                                     //自定义信号
	void explains();            //假如要自定义槽和信号, explains信号是必须的
	void sigWBADone(float, float, float);
	void sigAEStartMsg(bool);
	void sigAEFinishMsg(int, float);

protected slots:

	void on_PreViewPushButton_clicked();
	void on_RefreshPushButton_clicked();
	void on_SnapImagePushButton_clicked();

	void on_DevicesComboBox_currentIndexChanged(int);

	void on_TrigetModeComboBox_currentIndexChanged(int);
	void on_TrigetMethodComboBox_currentIndexChanged(int);

	void on_FixFrameRateDoubleSpinBox_valueChanged(double);
	void on_CaptureTimeoutSpinBox_valueChanged(int);

	void on_SkipComboBox_currentIndexChanged(int);

	void on_ApplyFovPushButton_clicked();

	void on_ExpoureLineSpinBox_valueChanged(int);
	void on_ExposureTimeSpinBox_valueChanged(double);

	void on_MirrorCheckBox_stateChanged(int);
	void on_FlipCheckBox_stateChanged(int);

	void on_SensitivityComboBox_currentIndexChanged(int);

	void on_GainRedSpinBox_valueChanged(int);
	void on_GainGreenSpinBox_valueChanged(int);
	void on_GainBlueSpinBox_valueChanged(int);

	void on_ProgramLutPushButton_clicked();

	void on_WBModeComboBox_currentIndexChanged(int);
	void on_WBPresettingComboBox_currentIndexChanged(int);
	void on_WBPHiSpinBox_valueChanged(int);
	void on_WBRedSpinBox_valueChanged(double);
	void on_WBGreenSpinBox_valueChanged(double);
	void on_WBBlueSpinBox_valueChanged(double);

	void on_ProgramWBMatrixPushButton_clicked();

	void OnWBADone(float, float, float);

	void on_CCMModeComboBox_currentIndexChanged(int);
	void on_CCMPresettingComboBox_currentIndexChanged(int);

	void on_CCM00SpinBox_valueChanged(double);
	void on_CCM01SpinBox_valueChanged(double);
	void on_CCM02SpinBox_valueChanged(double);
	void on_CCM10SpinBox_valueChanged(double);
	void on_CCM11SpinBox_valueChanged(double);
	void on_CCM12SpinBox_valueChanged(double);
	void on_CCM20SpinBox_valueChanged(double);
	void on_CCM21SpinBox_valueChanged(double);
	void on_CCM22SpinBox_valueChanged(double);

	void on_ProgramCCMMatrixPushButton_clicked();

	void on_PragramSettingsPushButton_clicked();
	void on_ClearSettingsPushButton_clicked();

	void on_EmptyBufferPushButton_clicked();
	void on_CaptureRGBPushButton_clicked();
	void on_CaptureRawPushButton_clicked();

	void on_SendEndMsgPushButton_clicked();

	void on_ResetHostPushButton_clicked();

	void on_TestingPushButton_clicked();

	void on_BayerModeComboBox_currentIndexChanged(int);
	void on_BayerFilterComboBox_currentIndexChanged(int);

	void on_DefaultBayerPushButton_clicked();

	void on_OnlyCaptureCheckBox_stateChanged(int);

	void OnClcFpsTimer();

	void on_PeakAveSpinBox_valueChanged(double);
	void on_MaxAEDoubleSpinBox_valueChanged(double);
	void on_TargetBrightnessSpinBox_valueChanged(int);

	void on_ContinuousAECheckBox_stateChanged(int);
	void on_ShowAERegionCheckBox_stateChanged(int);

	void on_AutoExposureCheckBox_stateChanged(int);

	void OnAEStartMsg(bool);
	void OnAEFinishMsg(int, float);

	void on_StreamModeCheckBox_stateChanged(int);


	void on_UsbStatusPushButton_clicked();
	void on_RebootDevicePushButton_clicked();


protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent * e);
	virtual void mouseReleaseEvent(QMouseEvent * e);
	virtual void mouseMoveEvent(QMouseEvent * e);
	virtual void mouseDoubleClickEvent(QMouseEvent * e);
	virtual void wheelEvent(QWheelEvent * event);

protected:
	bool StartCaptureThread();
	bool KillCaptureThread();

	void RefreshDevice();
	void SelectDevice(int nIndex);

	void InitCnotrol();
	void UpdateDeviceInfo();

	void UpdateWhiteBalanceMatrix();
	void EnableWhiteBalanceMatrixControls(bool bEnable);

	void UpdateColorCorrectionMatrix();
	void EnableColorCorrectionMatrixControls(bool bEnable);

	bool StopPreview();
	bool StartPreview();

	void AEStart(bool bStart);


public:
	void WBACallback(float fMatrix[3]);

	void AeCallbackEx(KSJ_AE_STATUS AEStatus, float fExpsoureTimeMs);

protected:
	int  m_nCamareIndex;
	bool m_bStopCaptureThread;
	bool m_bCapturingThreadIsWorking;

	bool m_bSaveImage;
	int  m_nSnapCount;
	QString m_strImagePath;
	QString m_strImagePreFix;

protected:
#ifdef _WIN32
	HANDLE        m_hCapturingThread;
	unsigned int  m_nCapturingThreadId;
	static unsigned int __stdcall ThreadForCaptureData(LPVOID arg);
#else
	unsigned long m_nCapturingThreadId;
	static void* ThreadForCaptureData(void *arg);
#endif

protected:
	void TransferImageData(unsigned char* pImageData, int w, int h, int bc, unsigned int nTimeOutMS);
	void ProcessCaptureData();

protected:
	// 采集到的图像
	QImage*  m_pImage;
	QMutex   m_ImageLocker;

	bool           m_bHasNewData;
	int            m_nImgWidth;
	int            m_nImgHeight;
	int            m_nImgBitCount;
	unsigned char* m_pTempImageData;
	QMutex         m_DataLocker;

	float          m_fCaptureUseMS;

	int            m_nClcFpsTickCount;

#ifdef _WIN32
	LARGE_INTEGER   m_lifrqc, m_litmp1, m_litmp2;
#else
	struct timeval  m_start;
	struct timeval  m_end;
#endif

	// 保留图像显示位置的信息
    QRect    m_rcClient;

	int     m_nFramesCount;
	int     m_nLastFramesCount;
	bool    m_bShowImage;

	QTimer* m_pClcFpsTimer;

	bool    m_bIsDoAutoExposure;

	float   m_fAePeakAveRatio;
	float   m_fAEMaxExposureTime;
	int     m_nAETarget;
	bool    m_bAEShowRegion;
	int     m_nAEMaxCount;

};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
