/********************************************************************************
** Form generated from reading UI file 'KSJSCZDemoMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KSJSCZDEMOMAINWINDOW_H
#define UI_KSJSCZDEMOMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KSJSCZDemoMainWindow
{
public:
    QGroupBox *SettingGroupBox;
    QPushButton *RefreshPushButton;
    QLabel *CamerasInfoLabel;
    QPushButton *PragramSettingsPushButton;
    QPushButton *ClearSettingsPushButton;
    QTabWidget *SettingTabWidget;
    QWidget *NormalTab;
    QGroupBox *groupBox_4;
    QSpinBox *ExpoureLineSpinBox;
    QLabel *label_14;
    QLabel *label_15;
    QDoubleSpinBox *ExposureTimeSpinBox;
    QGroupBox *groupBox_2;
    QSpinBox *GainGreenSpinBox;
    QSpinBox *GainRedSpinBox;
    QSpinBox *GainBlueSpinBox;
    QLabel *label_13;
    QLabel *label_16;
    QLabel *label_19;
    QCheckBox *MirrorCheckBox;
    QCheckBox *FlipCheckBox;
    QComboBox *SensitivityComboBox;
    QLabel *label_18;
    QGroupBox *groupBox;
    QSpinBox *ColStartSpinBox;
    QSpinBox *RowStartSpinBox;
    QSpinBox *ColSizeSpinBox;
    QSpinBox *RowSizeSpinBox;
    QPushButton *ApplyFovPushButton;
    QSpinBox *MultiFrameNumberSpinBox;
    QLabel *label_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QComboBox *SkipComboBox;
    QLabel *label_17;
    QDoubleSpinBox *FixFrameRateDoubleSpinBox;
    QComboBox *TrigetMethodComboBox;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *TrigetModeComboBox;
    QLabel *label;
    QPushButton *ProgramLutPushButton;
    QSpinBox *CaptureTimeoutSpinBox;
    QLabel *label_4;
    QCheckBox *LutEnableCheckBox;
    QWidget *ColorMatrixTab;
    QGroupBox *groupBox_3;
    QPushButton *ProgramWBMatrixPushButton;
    QLabel *label_12;
    QComboBox *WBModeComboBox;
    QLabel *label_20;
    QComboBox *WBPresettingComboBox;
    QLabel *label_25;
    QLabel *label_23;
    QLabel *label_24;
    QDoubleSpinBox *WBRedSpinBox;
    QSpinBox *WBPHiSpinBox;
    QLabel *label_21;
    QDoubleSpinBox *WBGreenSpinBox;
    QDoubleSpinBox *WBBlueSpinBox;
    QGroupBox *groupBox_5;
    QPushButton *ProgramCCMMatrixPushButton;
    QLabel *label_22;
    QComboBox *CCMModeComboBox;
    QLabel *label_26;
    QComboBox *CCMPresettingComboBox;
    QDoubleSpinBox *CCM00SpinBox;
    QDoubleSpinBox *CCM01SpinBox;
    QDoubleSpinBox *CCM02SpinBox;
    QDoubleSpinBox *CCM11SpinBox;
    QDoubleSpinBox *CCM10SpinBox;
    QDoubleSpinBox *CCM12SpinBox;
    QDoubleSpinBox *CCM21SpinBox;
    QDoubleSpinBox *CCM22SpinBox;
    QDoubleSpinBox *CCM20SpinBox;
    QGroupBox *groupBox_6;
    QLabel *label_27;
    QComboBox *BayerModeComboBox;
    QComboBox *BayerFilterComboBox;
    QLabel *label_28;
    QPushButton *DefaultBayerPushButton;
    QWidget *tab;
    QDoubleSpinBox *PeakAveSpinBox;
    QLabel *label_29;
    QLabel *label_30;
    QDoubleSpinBox *MaxAEDoubleSpinBox;
    QSpinBox *TargetBrightnessSpinBox;
    QLabel *label_31;
    QCheckBox *ContinuousAECheckBox;
    QCheckBox *AutoExposureCheckBox;
    QLabel *AutoExposureStatusLabel;
    QWidget *TestingTab;
    QPushButton *EmptyBufferPushButton;
    QPushButton *CaptureRGBPushButton;
    QPushButton *CaptureRawPushButton;
    QPushButton *TestingPushButton;
    QPushButton *SendEndMsgPushButton;
    QPushButton *ResetHostPushButton;
    QPushButton *UsbStatusPushButton;
    QPushButton *RebootDevicePushButton;
    QPushButton *PreViewPushButton;
    QPushButton *SnapImagePushButton;
    QLabel *FPSLabel;
    QCheckBox *OnlyCaptureCheckBox;
    QCheckBox *StreamModeCheckBox;
    QLabel *DeviceNameLabel;
    QLabel *SnapCountLabel;
    QPushButton *ExitAppPushButton;
    QPushButton *PreViewAllPushButton;
    QPushButton *StopViewAllPushButton;

    void setupUi(QDialog *KSJSCZDemoMainWindow)
    {
        if (KSJSCZDemoMainWindow->objectName().isEmpty())
            KSJSCZDemoMainWindow->setObjectName(QStringLiteral("KSJSCZDemoMainWindow"));
        KSJSCZDemoMainWindow->resize(1024, 702);
        SettingGroupBox = new QGroupBox(KSJSCZDemoMainWindow);
        SettingGroupBox->setObjectName(QStringLiteral("SettingGroupBox"));
        SettingGroupBox->setGeometry(QRect(708, -10, 312, 710));
        RefreshPushButton = new QPushButton(SettingGroupBox);
        RefreshPushButton->setObjectName(QStringLiteral("RefreshPushButton"));
        RefreshPushButton->setGeometry(QRect(190, 25, 65, 27));
        CamerasInfoLabel = new QLabel(SettingGroupBox);
        CamerasInfoLabel->setObjectName(QStringLiteral("CamerasInfoLabel"));
        CamerasInfoLabel->setGeometry(QRect(12, 30, 101, 16));
        PragramSettingsPushButton = new QPushButton(SettingGroupBox);
        PragramSettingsPushButton->setObjectName(QStringLiteral("PragramSettingsPushButton"));
        PragramSettingsPushButton->setGeometry(QRect(10, 673, 132, 30));
        ClearSettingsPushButton = new QPushButton(SettingGroupBox);
        ClearSettingsPushButton->setObjectName(QStringLiteral("ClearSettingsPushButton"));
        ClearSettingsPushButton->setGeometry(QRect(170, 673, 132, 30));
        SettingTabWidget = new QTabWidget(SettingGroupBox);
        SettingTabWidget->setObjectName(QStringLiteral("SettingTabWidget"));
        SettingTabWidget->setGeometry(QRect(4, 174, 304, 495));
        NormalTab = new QWidget();
        NormalTab->setObjectName(QStringLiteral("NormalTab"));
        groupBox_4 = new QGroupBox(NormalTab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(4, 10, 290, 51));
        ExpoureLineSpinBox = new QSpinBox(groupBox_4);
        ExpoureLineSpinBox->setObjectName(QStringLiteral("ExpoureLineSpinBox"));
        ExpoureLineSpinBox->setGeometry(QRect(72, 20, 69, 22));
        ExpoureLineSpinBox->setMaximum(999999);
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 22, 40, 16));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(152, 22, 59, 16));
        label_15->setLayoutDirection(Qt::LeftToRight);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ExposureTimeSpinBox = new QDoubleSpinBox(groupBox_4);
        ExposureTimeSpinBox->setObjectName(QStringLiteral("ExposureTimeSpinBox"));
        ExposureTimeSpinBox->setEnabled(false);
        ExposureTimeSpinBox->setGeometry(QRect(216, 20, 62, 22));
        groupBox_2 = new QGroupBox(NormalTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(4, 72, 288, 53));
        GainGreenSpinBox = new QSpinBox(groupBox_2);
        GainGreenSpinBox->setObjectName(QStringLiteral("GainGreenSpinBox"));
        GainGreenSpinBox->setGeometry(QRect(140, 21, 48, 22));
        GainGreenSpinBox->setMaximum(8192);
        GainRedSpinBox = new QSpinBox(groupBox_2);
        GainRedSpinBox->setObjectName(QStringLiteral("GainRedSpinBox"));
        GainRedSpinBox->setGeometry(QRect(42, 21, 48, 22));
        GainRedSpinBox->setMaximum(8192);
        GainBlueSpinBox = new QSpinBox(groupBox_2);
        GainBlueSpinBox->setObjectName(QStringLiteral("GainBlueSpinBox"));
        GainBlueSpinBox->setGeometry(QRect(230, 21, 48, 22));
        GainBlueSpinBox->setMaximum(8192);
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(96, 24, 40, 16));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(192, 24, 35, 16));
        label_16->setLayoutDirection(Qt::LeftToRight);
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(7, 24, 31, 16));
        label_19->setLayoutDirection(Qt::LeftToRight);
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MirrorCheckBox = new QCheckBox(NormalTab);
        MirrorCheckBox->setObjectName(QStringLiteral("MirrorCheckBox"));
        MirrorCheckBox->setGeometry(QRect(72, 136, 67, 20));
        FlipCheckBox = new QCheckBox(NormalTab);
        FlipCheckBox->setObjectName(QStringLiteral("FlipCheckBox"));
        FlipCheckBox->setGeometry(QRect(14, 136, 53, 20));
        SensitivityComboBox = new QComboBox(NormalTab);
        SensitivityComboBox->setObjectName(QStringLiteral("SensitivityComboBox"));
        SensitivityComboBox->setGeometry(QRect(228, 134, 67, 25));
        label_18 = new QLabel(NormalTab);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(144, 138, 79, 16));
        groupBox = new QGroupBox(NormalTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(2, 164, 290, 131));
        ColStartSpinBox = new QSpinBox(groupBox);
        ColStartSpinBox->setObjectName(QStringLiteral("ColStartSpinBox"));
        ColStartSpinBox->setGeometry(QRect(96, 14, 59, 22));
        ColStartSpinBox->setMaximum(8192);
        RowStartSpinBox = new QSpinBox(groupBox);
        RowStartSpinBox->setObjectName(QStringLiteral("RowStartSpinBox"));
        RowStartSpinBox->setGeometry(QRect(96, 40, 59, 22));
        RowStartSpinBox->setMaximum(8192);
        ColSizeSpinBox = new QSpinBox(groupBox);
        ColSizeSpinBox->setObjectName(QStringLiteral("ColSizeSpinBox"));
        ColSizeSpinBox->setGeometry(QRect(204, 14, 59, 22));
        ColSizeSpinBox->setMaximum(8192);
        RowSizeSpinBox = new QSpinBox(groupBox);
        RowSizeSpinBox->setObjectName(QStringLiteral("RowSizeSpinBox"));
        RowSizeSpinBox->setGeometry(QRect(204, 40, 59, 22));
        RowSizeSpinBox->setMaximum(8192);
        ApplyFovPushButton = new QPushButton(groupBox);
        ApplyFovPushButton->setObjectName(QStringLiteral("ApplyFovPushButton"));
        ApplyFovPushButton->setGeometry(QRect(208, 68, 69, 32));
        MultiFrameNumberSpinBox = new QSpinBox(groupBox);
        MultiFrameNumberSpinBox->setObjectName(QStringLiteral("MultiFrameNumberSpinBox"));
        MultiFrameNumberSpinBox->setGeometry(QRect(130, 74, 59, 22));
        MultiFrameNumberSpinBox->setMaximum(8192);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(8, 76, 119, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 16, 80, 16));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 42, 80, 16));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(160, 42, 36, 16));
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(160, 16, 36, 16));
        label_10->setLayoutDirection(Qt::LeftToRight);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SkipComboBox = new QComboBox(groupBox);
        SkipComboBox->setObjectName(QStringLiteral("SkipComboBox"));
        SkipComboBox->setGeometry(QRect(52, 102, 69, 25));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(12, 108, 35, 16));
        FixFrameRateDoubleSpinBox = new QDoubleSpinBox(NormalTab);
        FixFrameRateDoubleSpinBox->setObjectName(QStringLiteral("FixFrameRateDoubleSpinBox"));
        FixFrameRateDoubleSpinBox->setGeometry(QRect(136, 406, 62, 22));
        TrigetMethodComboBox = new QComboBox(NormalTab);
        TrigetMethodComboBox->setObjectName(QStringLiteral("TrigetMethodComboBox"));
        TrigetMethodComboBox->setGeometry(QRect(28, 374, 264, 28));
        label_6 = new QLabel(NormalTab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(8, 304, 109, 16));
        label_7 = new QLabel(NormalTab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(8, 356, 120, 16));
        TrigetModeComboBox = new QComboBox(NormalTab);
        TrigetModeComboBox->setObjectName(QStringLiteral("TrigetModeComboBox"));
        TrigetModeComboBox->setGeometry(QRect(28, 326, 264, 28));
        label = new QLabel(NormalTab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(6, 409, 120, 16));
        ProgramLutPushButton = new QPushButton(NormalTab);
        ProgramLutPushButton->setObjectName(QStringLiteral("ProgramLutPushButton"));
        ProgramLutPushButton->setGeometry(QRect(160, 433, 131, 30));
        CaptureTimeoutSpinBox = new QSpinBox(NormalTab);
        CaptureTimeoutSpinBox->setObjectName(QStringLiteral("CaptureTimeoutSpinBox"));
        CaptureTimeoutSpinBox->setGeometry(QRect(214, 300, 79, 22));
        CaptureTimeoutSpinBox->setMaximum(999999999);
        label_4 = new QLabel(NormalTab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(124, 304, 85, 16));
        LutEnableCheckBox = new QCheckBox(NormalTab);
        LutEnableCheckBox->setObjectName(QStringLiteral("LutEnableCheckBox"));
        LutEnableCheckBox->setGeometry(QRect(20, 437, 101, 20));
        SettingTabWidget->addTab(NormalTab, QString());
        ColorMatrixTab = new QWidget();
        ColorMatrixTab->setObjectName(QStringLiteral("ColorMatrixTab"));
        groupBox_3 = new QGroupBox(ColorMatrixTab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(4, 6, 290, 173));
        ProgramWBMatrixPushButton = new QPushButton(groupBox_3);
        ProgramWBMatrixPushButton->setObjectName(QStringLiteral("ProgramWBMatrixPushButton"));
        ProgramWBMatrixPushButton->setGeometry(QRect(142, 134, 141, 32));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(8, 22, 80, 16));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WBModeComboBox = new QComboBox(groupBox_3);
        WBModeComboBox->setObjectName(QStringLiteral("WBModeComboBox"));
        WBModeComboBox->setGeometry(QRect(102, 18, 168, 28));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(8, 54, 80, 16));
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WBPresettingComboBox = new QComboBox(groupBox_3);
        WBPresettingComboBox->setObjectName(QStringLiteral("WBPresettingComboBox"));
        WBPresettingComboBox->setGeometry(QRect(102, 50, 168, 28));
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(8, 110, 29, 16));
        label_25->setLayoutDirection(Qt::LeftToRight);
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(196, 110, 36, 16));
        label_23->setLayoutDirection(Qt::LeftToRight);
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(96, 110, 43, 16));
        label_24->setLayoutDirection(Qt::LeftToRight);
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WBRedSpinBox = new QDoubleSpinBox(groupBox_3);
        WBRedSpinBox->setObjectName(QStringLiteral("WBRedSpinBox"));
        WBRedSpinBox->setGeometry(QRect(44, 108, 50, 22));
        WBRedSpinBox->setDecimals(3);
        WBRedSpinBox->setMinimum(0);
        WBRedSpinBox->setMaximum(5);
        WBPHiSpinBox = new QSpinBox(groupBox_3);
        WBPHiSpinBox->setObjectName(QStringLiteral("WBPHiSpinBox"));
        WBPHiSpinBox->setGeometry(QRect(104, 82, 59, 22));
        WBPHiSpinBox->setMaximum(8192);
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(8, 84, 80, 16));
        label_21->setLayoutDirection(Qt::LeftToRight);
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WBGreenSpinBox = new QDoubleSpinBox(groupBox_3);
        WBGreenSpinBox->setObjectName(QStringLiteral("WBGreenSpinBox"));
        WBGreenSpinBox->setGeometry(QRect(144, 108, 50, 22));
        WBGreenSpinBox->setDecimals(3);
        WBGreenSpinBox->setMaximum(5);
        WBBlueSpinBox = new QDoubleSpinBox(groupBox_3);
        WBBlueSpinBox->setObjectName(QStringLiteral("WBBlueSpinBox"));
        WBBlueSpinBox->setGeometry(QRect(234, 108, 50, 22));
        WBBlueSpinBox->setDecimals(3);
        WBBlueSpinBox->setMaximum(5);
        groupBox_5 = new QGroupBox(ColorMatrixTab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(4, 184, 290, 173));
        ProgramCCMMatrixPushButton = new QPushButton(groupBox_5);
        ProgramCCMMatrixPushButton->setObjectName(QStringLiteral("ProgramCCMMatrixPushButton"));
        ProgramCCMMatrixPushButton->setGeometry(QRect(206, 122, 79, 39));
        label_22 = new QLabel(groupBox_5);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(8, 22, 80, 16));
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CCMModeComboBox = new QComboBox(groupBox_5);
        CCMModeComboBox->setObjectName(QStringLiteral("CCMModeComboBox"));
        CCMModeComboBox->setGeometry(QRect(102, 18, 168, 28));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(8, 54, 80, 16));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        CCMPresettingComboBox = new QComboBox(groupBox_5);
        CCMPresettingComboBox->setObjectName(QStringLiteral("CCMPresettingComboBox"));
        CCMPresettingComboBox->setGeometry(QRect(102, 50, 168, 28));
        CCM00SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM00SpinBox->setObjectName(QStringLiteral("CCM00SpinBox"));
        CCM00SpinBox->setGeometry(QRect(14, 84, 52, 22));
        CCM00SpinBox->setDecimals(3);
        CCM00SpinBox->setMinimum(-999);
        CCM00SpinBox->setMaximum(999);
        CCM00SpinBox->setSingleStep(0.001);
        CCM01SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM01SpinBox->setObjectName(QStringLiteral("CCM01SpinBox"));
        CCM01SpinBox->setGeometry(QRect(76, 84, 52, 22));
        CCM01SpinBox->setDecimals(3);
        CCM01SpinBox->setMinimum(-999);
        CCM01SpinBox->setMaximum(999);
        CCM01SpinBox->setSingleStep(0.001);
        CCM02SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM02SpinBox->setObjectName(QStringLiteral("CCM02SpinBox"));
        CCM02SpinBox->setGeometry(QRect(136, 84, 52, 22));
        CCM02SpinBox->setDecimals(3);
        CCM02SpinBox->setMinimum(-999);
        CCM02SpinBox->setMaximum(999);
        CCM02SpinBox->setSingleStep(0.001);
        CCM11SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM11SpinBox->setObjectName(QStringLiteral("CCM11SpinBox"));
        CCM11SpinBox->setGeometry(QRect(76, 112, 52, 22));
        CCM11SpinBox->setDecimals(3);
        CCM11SpinBox->setMinimum(-999);
        CCM11SpinBox->setMaximum(999);
        CCM11SpinBox->setSingleStep(0.001);
        CCM10SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM10SpinBox->setObjectName(QStringLiteral("CCM10SpinBox"));
        CCM10SpinBox->setGeometry(QRect(14, 112, 52, 22));
        CCM10SpinBox->setDecimals(3);
        CCM10SpinBox->setMinimum(-999);
        CCM10SpinBox->setMaximum(999);
        CCM10SpinBox->setSingleStep(0.001);
        CCM12SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM12SpinBox->setObjectName(QStringLiteral("CCM12SpinBox"));
        CCM12SpinBox->setGeometry(QRect(136, 112, 52, 22));
        CCM12SpinBox->setDecimals(3);
        CCM12SpinBox->setMinimum(-999);
        CCM12SpinBox->setMaximum(999);
        CCM12SpinBox->setSingleStep(0.001);
        CCM21SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM21SpinBox->setObjectName(QStringLiteral("CCM21SpinBox"));
        CCM21SpinBox->setGeometry(QRect(76, 140, 52, 22));
        CCM21SpinBox->setDecimals(3);
        CCM21SpinBox->setMinimum(-999);
        CCM21SpinBox->setMaximum(999);
        CCM21SpinBox->setSingleStep(0.001);
        CCM22SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM22SpinBox->setObjectName(QStringLiteral("CCM22SpinBox"));
        CCM22SpinBox->setGeometry(QRect(136, 140, 52, 22));
        CCM22SpinBox->setDecimals(3);
        CCM22SpinBox->setMinimum(-999);
        CCM22SpinBox->setMaximum(999);
        CCM22SpinBox->setSingleStep(0.001);
        CCM20SpinBox = new QDoubleSpinBox(groupBox_5);
        CCM20SpinBox->setObjectName(QStringLiteral("CCM20SpinBox"));
        CCM20SpinBox->setGeometry(QRect(14, 140, 52, 22));
        CCM20SpinBox->setDecimals(3);
        CCM20SpinBox->setMinimum(-999);
        CCM20SpinBox->setMaximum(999);
        CCM20SpinBox->setSingleStep(0.001);
        groupBox_6 = new QGroupBox(ColorMatrixTab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(4, 358, 290, 83));
        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(10, 22, 47, 16));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BayerModeComboBox = new QComboBox(groupBox_6);
        BayerModeComboBox->setObjectName(QStringLiteral("BayerModeComboBox"));
        BayerModeComboBox->setGeometry(QRect(64, 18, 148, 28));
        BayerFilterComboBox = new QComboBox(groupBox_6);
        BayerFilterComboBox->setObjectName(QStringLiteral("BayerFilterComboBox"));
        BayerFilterComboBox->setGeometry(QRect(64, 50, 148, 28));
        label_28 = new QLabel(groupBox_6);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(10, 54, 47, 16));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DefaultBayerPushButton = new QPushButton(groupBox_6);
        DefaultBayerPushButton->setObjectName(QStringLiteral("DefaultBayerPushButton"));
        DefaultBayerPushButton->setGeometry(QRect(220, 16, 61, 32));
        SettingTabWidget->addTab(ColorMatrixTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        PeakAveSpinBox = new QDoubleSpinBox(tab);
        PeakAveSpinBox->setObjectName(QStringLiteral("PeakAveSpinBox"));
        PeakAveSpinBox->setGeometry(QRect(84, 14, 52, 22));
        PeakAveSpinBox->setDecimals(3);
        PeakAveSpinBox->setMaximum(5);
        label_29 = new QLabel(tab);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(8, 16, 69, 16));
        label_29->setLayoutDirection(Qt::LeftToRight);
        label_29->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_30 = new QLabel(tab);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(8, 44, 185, 16));
        label_30->setLayoutDirection(Qt::LeftToRight);
        label_30->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        MaxAEDoubleSpinBox = new QDoubleSpinBox(tab);
        MaxAEDoubleSpinBox->setObjectName(QStringLiteral("MaxAEDoubleSpinBox"));
        MaxAEDoubleSpinBox->setGeometry(QRect(200, 40, 56, 22));
        MaxAEDoubleSpinBox->setMinimum(1);
        MaxAEDoubleSpinBox->setMaximum(10000);
        MaxAEDoubleSpinBox->setValue(1000);
        TargetBrightnessSpinBox = new QSpinBox(tab);
        TargetBrightnessSpinBox->setObjectName(QStringLiteral("TargetBrightnessSpinBox"));
        TargetBrightnessSpinBox->setGeometry(QRect(236, 68, 56, 22));
        TargetBrightnessSpinBox->setMinimum(128);
        TargetBrightnessSpinBox->setMaximum(255);
        label_31 = new QLabel(tab);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(8, 72, 221, 16));
        label_31->setLayoutDirection(Qt::LeftToRight);
        label_31->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ContinuousAECheckBox = new QCheckBox(tab);
        ContinuousAECheckBox->setObjectName(QStringLiteral("ContinuousAECheckBox"));
        ContinuousAECheckBox->setGeometry(QRect(10, 102, 97, 20));
        AutoExposureCheckBox = new QCheckBox(tab);
        AutoExposureCheckBox->setObjectName(QStringLiteral("AutoExposureCheckBox"));
        AutoExposureCheckBox->setGeometry(QRect(10, 136, 109, 20));
        AutoExposureStatusLabel = new QLabel(tab);
        AutoExposureStatusLabel->setObjectName(QStringLiteral("AutoExposureStatusLabel"));
        AutoExposureStatusLabel->setGeometry(QRect(16, 164, 221, 16));
        AutoExposureStatusLabel->setLayoutDirection(Qt::LeftToRight);
        AutoExposureStatusLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        SettingTabWidget->addTab(tab, QString());
        TestingTab = new QWidget();
        TestingTab->setObjectName(QStringLiteral("TestingTab"));
        EmptyBufferPushButton = new QPushButton(TestingTab);
        EmptyBufferPushButton->setObjectName(QStringLiteral("EmptyBufferPushButton"));
        EmptyBufferPushButton->setGeometry(QRect(18, 22, 111, 32));
        CaptureRGBPushButton = new QPushButton(TestingTab);
        CaptureRGBPushButton->setObjectName(QStringLiteral("CaptureRGBPushButton"));
        CaptureRGBPushButton->setGeometry(QRect(18, 62, 111, 32));
        CaptureRawPushButton = new QPushButton(TestingTab);
        CaptureRawPushButton->setObjectName(QStringLiteral("CaptureRawPushButton"));
        CaptureRawPushButton->setGeometry(QRect(18, 102, 111, 32));
        TestingPushButton = new QPushButton(TestingTab);
        TestingPushButton->setObjectName(QStringLiteral("TestingPushButton"));
        TestingPushButton->setGeometry(QRect(18, 146, 111, 32));
        SendEndMsgPushButton = new QPushButton(TestingTab);
        SendEndMsgPushButton->setObjectName(QStringLiteral("SendEndMsgPushButton"));
        SendEndMsgPushButton->setGeometry(QRect(148, 22, 111, 32));
        ResetHostPushButton = new QPushButton(TestingTab);
        ResetHostPushButton->setObjectName(QStringLiteral("ResetHostPushButton"));
        ResetHostPushButton->setGeometry(QRect(148, 62, 111, 32));
        UsbStatusPushButton = new QPushButton(TestingTab);
        UsbStatusPushButton->setObjectName(QStringLiteral("UsbStatusPushButton"));
        UsbStatusPushButton->setGeometry(QRect(18, 188, 111, 32));
        RebootDevicePushButton = new QPushButton(TestingTab);
        RebootDevicePushButton->setObjectName(QStringLiteral("RebootDevicePushButton"));
        RebootDevicePushButton->setGeometry(QRect(152, 188, 111, 32));
        SettingTabWidget->addTab(TestingTab, QString());
        PreViewPushButton = new QPushButton(SettingGroupBox);
        PreViewPushButton->setObjectName(QStringLiteral("PreViewPushButton"));
        PreViewPushButton->setGeometry(QRect(6, 114, 97, 32));
        SnapImagePushButton = new QPushButton(SettingGroupBox);
        SnapImagePushButton->setObjectName(QStringLiteral("SnapImagePushButton"));
        SnapImagePushButton->setGeometry(QRect(104, 114, 69, 32));
        FPSLabel = new QLabel(SettingGroupBox);
        FPSLabel->setObjectName(QStringLiteral("FPSLabel"));
        FPSLabel->setGeometry(QRect(220, 92, 67, 16));
        OnlyCaptureCheckBox = new QCheckBox(SettingGroupBox);
        OnlyCaptureCheckBox->setObjectName(QStringLiteral("OnlyCaptureCheckBox"));
        OnlyCaptureCheckBox->setGeometry(QRect(6, 150, 141, 20));
        StreamModeCheckBox = new QCheckBox(SettingGroupBox);
        StreamModeCheckBox->setObjectName(QStringLiteral("StreamModeCheckBox"));
        StreamModeCheckBox->setGeometry(QRect(162, 150, 141, 20));
        DeviceNameLabel = new QLabel(SettingGroupBox);
        DeviceNameLabel->setObjectName(QStringLiteral("DeviceNameLabel"));
        DeviceNameLabel->setGeometry(QRect(16, 66, 279, 16));
        SnapCountLabel = new QLabel(SettingGroupBox);
        SnapCountLabel->setObjectName(QStringLiteral("SnapCountLabel"));
        SnapCountLabel->setGeometry(QRect(12, 92, 197, 16));
        ExitAppPushButton = new QPushButton(SettingGroupBox);
        ExitAppPushButton->setObjectName(QStringLiteral("ExitAppPushButton"));
        ExitAppPushButton->setGeometry(QRect(270, 25, 27, 27));
        PreViewAllPushButton = new QPushButton(SettingGroupBox);
        PreViewAllPushButton->setObjectName(QStringLiteral("PreViewAllPushButton"));
        PreViewAllPushButton->setGeometry(QRect(178, 114, 65, 32));
        StopViewAllPushButton = new QPushButton(SettingGroupBox);
        StopViewAllPushButton->setObjectName(QStringLiteral("StopViewAllPushButton"));
        StopViewAllPushButton->setGeometry(QRect(242, 114, 65, 32));
        SettingTabWidget->raise();
        RefreshPushButton->raise();
        CamerasInfoLabel->raise();
        PragramSettingsPushButton->raise();
        ClearSettingsPushButton->raise();
        PreViewPushButton->raise();
        SnapImagePushButton->raise();
        FPSLabel->raise();
        OnlyCaptureCheckBox->raise();
        StreamModeCheckBox->raise();
        DeviceNameLabel->raise();
        SnapCountLabel->raise();
        ExitAppPushButton->raise();
        PreViewAllPushButton->raise();
        StopViewAllPushButton->raise();

        retranslateUi(KSJSCZDemoMainWindow);

        SettingTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(KSJSCZDemoMainWindow);
    } // setupUi

    void retranslateUi(QDialog *KSJSCZDemoMainWindow)
    {
        KSJSCZDemoMainWindow->setWindowTitle(QApplication::translate("KSJSCZDemoMainWindow", "Dialog", Q_NULLPTR));
        SettingGroupBox->setTitle(QString());
        RefreshPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Refresh", Q_NULLPTR));
        CamerasInfoLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "NO CAMARE", Q_NULLPTR));
        PragramSettingsPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Pragram to camera", Q_NULLPTR));
        ClearSettingsPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Clear camera setting", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Exposure", Q_NULLPTR));
        label_14->setText(QApplication::translate("KSJSCZDemoMainWindow", "Line:", Q_NULLPTR));
        label_15->setText(QApplication::translate("KSJSCZDemoMainWindow", "Time(MS):", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "CMOS Gain", Q_NULLPTR));
        label_13->setText(QApplication::translate("KSJSCZDemoMainWindow", "Green:", Q_NULLPTR));
        label_16->setText(QApplication::translate("KSJSCZDemoMainWindow", "Blue:", Q_NULLPTR));
        label_19->setText(QApplication::translate("KSJSCZDemoMainWindow", "Red:", Q_NULLPTR));
        MirrorCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Mirror", Q_NULLPTR));
        FlipCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Flip", Q_NULLPTR));
        label_18->setText(QApplication::translate("KSJSCZDemoMainWindow", "Sensitivity:", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "FOV", Q_NULLPTR));
        ApplyFovPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Apply", Q_NULLPTR));
        label_2->setText(QApplication::translate("KSJSCZDemoMainWindow", "Multiframe number:", Q_NULLPTR));
        label_8->setText(QApplication::translate("KSJSCZDemoMainWindow", "Col Start:", Q_NULLPTR));
        label_9->setText(QApplication::translate("KSJSCZDemoMainWindow", "Row Start:", Q_NULLPTR));
        label_11->setText(QApplication::translate("KSJSCZDemoMainWindow", "Size:", Q_NULLPTR));
        label_10->setText(QApplication::translate("KSJSCZDemoMainWindow", "Size:", Q_NULLPTR));
        label_17->setText(QApplication::translate("KSJSCZDemoMainWindow", "Skip:", Q_NULLPTR));
        label_6->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Mode:", Q_NULLPTR));
        label_7->setText(QApplication::translate("KSJSCZDemoMainWindow", "Trigger Method:", Q_NULLPTR));
        label->setText(QApplication::translate("KSJSCZDemoMainWindow", "Fixed frame rate:", Q_NULLPTR));
        ProgramLutPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Program LUT", Q_NULLPTR));
        label_4->setText(QApplication::translate("KSJSCZDemoMainWindow", "Timeout(MS):", Q_NULLPTR));
        LutEnableCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Enable LUT", Q_NULLPTR));
        SettingTabWidget->setTabText(SettingTabWidget->indexOf(NormalTab), QApplication::translate("KSJSCZDemoMainWindow", "Normal", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "White Balance Matrix", Q_NULLPTR));
        ProgramWBMatrixPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Programm WB Matrix", Q_NULLPTR));
        label_12->setText(QApplication::translate("KSJSCZDemoMainWindow", "Mode:", Q_NULLPTR));
        label_20->setText(QApplication::translate("KSJSCZDemoMainWindow", "Presettings:", Q_NULLPTR));
        label_25->setText(QApplication::translate("KSJSCZDemoMainWindow", "Red:", Q_NULLPTR));
        label_23->setText(QApplication::translate("KSJSCZDemoMainWindow", "Blue:", Q_NULLPTR));
        label_24->setText(QApplication::translate("KSJSCZDemoMainWindow", "Green:", Q_NULLPTR));
        label_21->setText(QApplication::translate("KSJSCZDemoMainWindow", "PHi:", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Color Correction Matrix", Q_NULLPTR));
        ProgramCCMMatrixPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Programm", Q_NULLPTR));
        label_22->setText(QApplication::translate("KSJSCZDemoMainWindow", "Mode:", Q_NULLPTR));
        label_26->setText(QApplication::translate("KSJSCZDemoMainWindow", "Presettings:", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("KSJSCZDemoMainWindow", "Bayer", Q_NULLPTR));
        label_27->setText(QApplication::translate("KSJSCZDemoMainWindow", "Mode:", Q_NULLPTR));
        label_28->setText(QApplication::translate("KSJSCZDemoMainWindow", "Filter:", Q_NULLPTR));
        DefaultBayerPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Default", Q_NULLPTR));
        SettingTabWidget->setTabText(SettingTabWidget->indexOf(ColorMatrixTab), QApplication::translate("KSJSCZDemoMainWindow", "Color Matrix", Q_NULLPTR));
        label_29->setText(QApplication::translate("KSJSCZDemoMainWindow", "Peak/Ave:", Q_NULLPTR));
        label_30->setText(QApplication::translate("KSJSCZDemoMainWindow", "Max Target Exposure Time(ms):", Q_NULLPTR));
        label_31->setText(QApplication::translate("KSJSCZDemoMainWindow", "Target Brightness(128 recommended):", Q_NULLPTR));
        ContinuousAECheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Continuous", Q_NULLPTR));
        AutoExposureCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Auto Exposure", Q_NULLPTR));
        AutoExposureStatusLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "....", Q_NULLPTR));
        SettingTabWidget->setTabText(SettingTabWidget->indexOf(tab), QApplication::translate("KSJSCZDemoMainWindow", "Auto Exposure", Q_NULLPTR));
        EmptyBufferPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Empty Buffer", Q_NULLPTR));
        CaptureRGBPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Capture RGB", Q_NULLPTR));
        CaptureRawPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Capture Raw", Q_NULLPTR));
        TestingPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Testing", Q_NULLPTR));
        SendEndMsgPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Send End", Q_NULLPTR));
        ResetHostPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Reset Host", Q_NULLPTR));
        UsbStatusPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "USB Status", Q_NULLPTR));
        RebootDevicePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Reboot Device", Q_NULLPTR));
        SettingTabWidget->setTabText(SettingTabWidget->indexOf(TestingTab), QApplication::translate("KSJSCZDemoMainWindow", "Testing", Q_NULLPTR));
        PreViewPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start Preview", Q_NULLPTR));
        SnapImagePushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Snap", Q_NULLPTR));
        FPSLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "0 fps", Q_NULLPTR));
        OnlyCaptureCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Do not show image", Q_NULLPTR));
        StreamModeCheckBox->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start stream mode", Q_NULLPTR));
        DeviceNameLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "******", Q_NULLPTR));
        SnapCountLabel->setText(QApplication::translate("KSJSCZDemoMainWindow", "0", Q_NULLPTR));
        ExitAppPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "X", Q_NULLPTR));
        PreViewAllPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Start All", Q_NULLPTR));
        StopViewAllPushButton->setText(QApplication::translate("KSJSCZDemoMainWindow", "Stop All", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class KSJSCZDemoMainWindow: public Ui_KSJSCZDemoMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KSJSCZDEMOMAINWINDOW_H