# -- coding: utf-8 --

#!/usr/bin/python3

from ctypes import *
import os.path
import sys
import os
import numpy as np
import cv2
import time as tm


libKsj = cdll.LoadLibrary('libksjapi.so')

# 初始化库函数
libKsj.KSJ_Init()
# 得到相机的个数，如果为0可以直接退出
camCount = libKsj.KSJ_DeviceGetCount()
print("cam count: %d" % (camCount))

if camCount == 0:
    print("!!! Do not found any camera !!!")
    sys.exit(-1)

usDeviceType = c_int()
nSerials = c_int()
usFirmwareVersion = c_int()

nIsMono = c_int();
libKsj.KSJ_QueryFunction(0, byref(nIsMono));
print("Is Mono  = %d" % (nIsMono.value))

# 查看设备信息
libKsj.KSJ_DeviceGetInformation(0, byref(usDeviceType), byref(nSerials), byref(usFirmwareVersion))
print("Device Type     = %d" % (usDeviceType.value))
print("Serials         = %d" % (nSerials.value))
print("FirmwareVersion = %d" % (usFirmwareVersion.value))

# 设置触发模式
# 0 表示内触发模式，速度是最快的
# 1 表示软件触发模式，采集一次触发一次
# 2 表示硬件触发模式，由外部信号触发
# 3 表示固定帧率模式
resultV = libKsj.KSJ_TriggerModeSet(0, 0)
print("KSJ_TriggerModeSet error code = %d" % (resultV))
# 设置帧率，只有固定帧率模式的时候才能够设置
# resultV = libKsj.KSJ_SetFixedFrameRateEx(0, c_float(80))
# print("KSJ_SetFixedFrameRateEx error code = %d" % (resultV))

# 设置曝光
resultV = libKsj.KSJ_ExposureTimeSet(0, c_float(20))
print("KSJ_ExposureTimeSet error code = %d" % (resultV))
        
nWidth = c_int()
nHeight = c_int()

# 取得图像的大小
libKsj.KSJ_CaptureGetSize(0, byref(nWidth), byref(nHeight))
print("width    = %d" % (nWidth.value))
print("height   = %d" % (nHeight.value))

# 查看一下触发模式
trigermode = c_int();
libKsj.KSJ_TriggerModeGet(0, byref(trigermode))
print("trigermode =  {0}".format(trigermode.value))

nBayerMode = c_int()
nWBMode = c_int()

if nIsMono.value == 0:
    #Bayer 模式
    # 0 -- KSJ_BGGR_BGR24
    # 1 -- KSJ_GRBG_BGR24 
    # 2 -- KSJ_RGGB_BGR24
    # 3 -- KSJ_GBRG_BGR24
    libKsj.KSJ_BayerGetDefaultMode(0, byref(nBayerMode));
    print("Bayer mode is = %d" % (nBayerMode.value))
    # 设置bayer模式
    #libKsj.KSJ_BayerSetMode(0, 0);
    
    #白平衡 模式
    # 0 -- KSJ_WB_DISABLE
    # 1 -- KSJ_SWB_PRESETTINGS
    # 2 -- KSJ_SWB_AUTO_ONCE
    # 3 -- KSJ_SWB_AUTO_CONITNUOUS
    # 4 -- KSJ_SWB_MANUAL
    # 5 -- KSJ_HWB_PRESETTINGS
    # 6 -- KSJ_HWB_AUTO_ONCE
    # 7 -- KSJ_HWB_AUTO_CONITNUOUS
    # 8 -- KSJ_HWB_MANUAL
    libKsj.KSJ_WhiteBalanceGet(0, byref(nWBMode));
    print("White Balance mode is = %d" % (nWBMode.value))
    # 设置bayer模式
    libKsj.KSJ_WhiteBalanceSet(0, 5);

t = tm.time()
t0 = tm.time()

nCount=0
nCount0=0

#黑白相机
if nIsMono.value != 0:
    pRawData = create_string_buffer(nWidth.value*nHeight.value*1)
    while 1:
    # 采集图像
        retValue = libKsj.KSJ_CaptureRawData(0, pRawData)

        if retValue != 0:
            print("capture1 error code %d" % (retValue))
        else:
            # 将图像转换成oencv图像，image可以做各种处理
            image = np.fromstring(pRawData, np.uint8).reshape(nHeight.value, nWidth.value, 1);

            # 缩小图像
            #image = cv2.resize(image, (684, 456))
            # 显示图像
            cv2.imshow("video", image)
            cv2.waitKey(1)
    
    t = tm.time()
    nCount += 1
    tt = t - t0

    if tt > 1:
        print("fps = %f" % (float(nCount-nCount0)/tt))
        print("count = %d" % (nCount))
        t0=t
        nCount0=nCount
else:
    pRawData = create_string_buffer(nWidth.value*nHeight.value*3)
    while 1:
    # 采集图像
        retValue = libKsj.KSJ_CaptureRgbData(0, pRawData)

        if retValue != 0:
            print("capture1 error code %d" % (retValue))
        else:
            # 将图像转换成oencv图像，image可以做各种处理
            image = np.fromstring(pRawData, np.uint8).reshape(nHeight.value, nWidth.value, 3);

            # 缩小图像
            #image = cv2.resize(image, (684, 456))
            # 显示图像
            cv2.imshow("video", image)
            cv2.waitKey(1)
    
    t = tm.time()
    nCount += 1
    tt = t - t0

    if tt > 1:
        print("fps = %f" % (float(nCount-nCount0)/tt))
        print("count = %d" % (nCount))
        t0=t
        nCount0=nCount
        

