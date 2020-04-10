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

usDeviceType = c_int()
nSerials = c_int()
usFirmwareVersion = c_int()

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
nBitCount = c_int()

# 取得图像的大小
libKsj.KSJ_CaptureGetSizeEx(0, byref(nWidth), byref(nHeight), byref(nBitCount))
print("width    = %d" % (nWidth.value))
print("height   = %d" % (nHeight.value))
print("bitcount = %d" % (nBitCount.value))

# 查看一下触发模式
trigermode = c_int();
libKsj.KSJ_TriggerModeGet(0, byref(trigermode))
print("trigermode =  {0}".format(trigermode.value))

nbufferSize = 5472*3648*1
pRawData = create_string_buffer(5472*3648*1)


t = tm.time()
t0 = tm.time()

nCount=0
nCount0=0
retValue1=1

imagecolor = np.zeros((684, 456, 3), dtype=np.uint8)

while 1:
    # 采集图像
    retValue = libKsj.KSJ_CaptureRgbData(0, pRawData)

    if retValue != 0:
        print("capture1 error code %d" % (retValue1))

    # 将图像转换成oencv图像，image可以做各种处理
    image = np.fromstring(pRawData, np.uint8).reshape(nWidth.value, nHeight.value, 1);

    # 缩小图像
    image = cv2.resize(image, (684, 456))
	cv2.cvtColor(image, cv2.COLOR_BayerGR2RGB, imagecolor, 3)
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
        


