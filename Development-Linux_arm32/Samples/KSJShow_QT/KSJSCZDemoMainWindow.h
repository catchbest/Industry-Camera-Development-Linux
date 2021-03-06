﻿#ifndef __KSJSCZDEMO_MAINWINDOW_H_
#define __KSJSCZDEMO_MAINWINDOW_H_

#include <QTimer>
#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QMatrix>
#include <QMutex>

#ifdef _WIN32
#include <tchar.h>
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

#define MAX_CAMERA_COUNT    16

extern const QString g_szDeviceType[];

namespace Ui { class KSJSCZDemoMainWindow; }

struct CallbackParam
{
	int nCameraIndex;
	void* pThreadParam;
};


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
	void sigNewImage();

protected slots:

	void OnNewImage();

	void on_PreViewPushButton_clicked();
	void on_RefreshPushButton_clicked();
	void on_SnapImagePushButton_clicked();

	void on_TrigetModeComboBox_currentIndexChanged(int);
	void on_TrigetMethodComboBox_currentIndexChanged(int);

	void on_FixFrameRateDoubleSpinBox_valueChanged(double);
	void on_CaptureTimeoutSpinBox_valueChanged(int);

	void on_SkipComboBox_currentIndexChanged(int);

	void on_ExitAppPushButton_clicked();

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
	void OnUpdateShowTimer();

	void on_PeakAveSpinBox_valueChanged(double);
	void on_MaxAEDoubleSpinBox_valueChanged(double);
	void on_TargetBrightnessSpinBox_valueChanged(int);

	void on_ContinuousAECheckBox_stateChanged(int);

	void on_AutoExposureCheckBox_stateChanged(int);

	void OnAEStartMsg(bool);
	void OnAEFinishMsg(int, float);

	void on_StreamModeCheckBox_stateChanged(int);


	void on_UsbStatusPushButton_clicked();
	void on_RebootDevicePushButton_clicked();

    void on_LutEnableCheckBox_stateChanged(int value);

	void on_PreViewAllPushButton_clicked();
	void on_StopViewAllPushButton_clicked();

protected:
	virtual void changeEvent(QEvent* event);
	virtual void resizeEvent(QResizeEvent * event);
	virtual void paintEvent(QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent * e);
	virtual void mouseReleaseEvent(QMouseEvent * e);
	virtual void mouseMoveEvent(QMouseEvent * e);
	virtual void mouseDoubleClickEvent(QMouseEvent * e);
	virtual void wheelEvent(QWheelEvent * event);

protected:
	bool StartCaptureThread(int nIndex);
	bool KillCaptureThread(int nIndex);

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
	void WBACallback(int nCamareIndex, float fMatrix[3]);

	void AeCallbackEx(int nCamareIndex, KSJ_AE_STATUS AEStatus, float fExpsoureTimeMs);

protected:
	int  m_nCameraNumber;
	int  m_nCamareIndex;

	bool m_pbStopCaptureThread[MAX_CAMERA_COUNT];
	bool m_pbCapturingThreadIsWorking[MAX_CAMERA_COUNT];

	bool m_pbSaveImage[MAX_CAMERA_COUNT];
	int  m_pnSnapCount[MAX_CAMERA_COUNT];

	QString m_strImagePath;
	QString m_strImagePreFix;

protected:
#ifdef _WIN32
	HANDLE m_hCapturingThread[MAX_CAMERA_COUNT];
	unsigned int m_nCapturingThreadId[MAX_CAMERA_COUNT];
	static unsigned int __stdcall ThreadForCaptureData(LPVOID arg);
#else
	unsigned long m_nCapturingThreadId[MAX_CAMERA_COUNT];
	static void* ThreadForCaptureData(void *arg);
#endif

protected:
	void TransferImageData(int nIndex, unsigned char* pImageData, int w, int h, int bc, unsigned int nTimeOutMS);
	void ProcessCaptureData();

protected:

	// 采集到的图像
	QImage*        m_pShowImage[MAX_CAMERA_COUNT];
	QMutex*        m_pImageLocker[MAX_CAMERA_COUNT];

	bool           m_bHasNewData[MAX_CAMERA_COUNT];
	int            m_nImgWidth[MAX_CAMERA_COUNT];
	int            m_nImgHeight[MAX_CAMERA_COUNT];
	int            m_nImgBitCount[MAX_CAMERA_COUNT];
	unsigned char* m_pTempImageData[MAX_CAMERA_COUNT];
	QMutex*        m_pDataLocker[MAX_CAMERA_COUNT];

	CallbackParam  m_DeviceCallbackParam[MAX_CAMERA_COUNT];

#ifdef _WIN32
	LARGE_INTEGER   m_lifrqc, m_litmp1, m_litmp2;
#else
	struct timeval  m_start;
	struct timeval  m_end;
#endif

	// 保留图像显示位置的信息
    QRect    m_rcClient;

	bool    m_bShowImage;

	bool    m_bHasNewImage;

	int     m_nFramesCount[MAX_CAMERA_COUNT];
	int     m_nLastFramesCount[MAX_CAMERA_COUNT];
	float   m_fCaptureUseMS[MAX_CAMERA_COUNT];
	int     m_nClcFpsTickCount[MAX_CAMERA_COUNT];

	QTimer* m_pClcFpsTimer;

	QTimer* m_pUpdateShowTimer;

	bool    m_bIsDoAutoExposure[MAX_CAMERA_COUNT];
	float   m_fAePeakAveRatio[MAX_CAMERA_COUNT];
	float   m_fAEMinExposureTime[MAX_CAMERA_COUNT];
	float   m_fAEMaxExposureTime[MAX_CAMERA_COUNT];
	int     m_nAETarget[MAX_CAMERA_COUNT];
	int     m_nAEMaxCount[MAX_CAMERA_COUNT];


};

#endif // __KSJSCZDEMO_MAINWINDOWS_H_
