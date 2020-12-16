#!/usr/bin/python3

from ctypes import *
import os.path
import sys
import os
import time as tm


libKsj = cdll.LoadLibrary('libksjapi.so')

libKsj.KSJ_Init()
camCount = libKsj.KSJ_DeviceGetCount()
print("cam count: %d" % (camCount))

usDeviceType = c_int()
nSerials = c_int()
usFirmwareVersion = c_int()
libKsj.KSJ_DeviceGetInformation(0, byref(usDeviceType), byref(nSerials), byref(usFirmwareVersion))
print("Device Type     = %d" % (usDeviceType.value))
print("Serials         = %d" % (nSerials.value))
print("FirmwareVersion = %d" % (usFirmwareVersion.value))

resultV = libKsj.KSJ_TriggerModeSet(0, 0)
print("KSJ_TriggerModeSet0 error code = %d" % (resultV))

#resultV = libKsj.KSJ_SetFixedFrameRateEx(0, c_float(70))
#print("KSJ_SetFixedFrameRateEx0 error code = %d" % (resultV))
        
nWidth = c_int()
nHeight = c_int()
nBitCount = c_int()
libKsj.KSJ_CaptureGetSizeEx(0, byref(nWidth), byref(nHeight), byref(nBitCount))
print("width    = %d" % (nWidth.value))
print("height   = %d" % (nHeight.value))
print("bitcount = %d" % (nBitCount.value))

trigermode = c_int();
libKsj.KSJ_TriggerModeGet(0, byref(trigermode))
print("trigermode0 =  {0}".format(trigermode.value))

nbufferSize = nWidth.value * nHeight.value * nBitCount.value / 8
pRawData1 = create_string_buffer(int(nbufferSize))
pRawData2 = create_string_buffer(int(nbufferSize))


t = tm.time()
t0 = tm.time()

nCount=0
nCount0=0
retValue1=1
retValue2=1

while 1:
    retValue1 = libKsj.KSJ_CaptureRawData(0, pRawData1)

    if retValue1 != 0:
        print("capture1 error code %d" % (retValue1))

    t = tm.time()
    nCount += 1
    tt = t - t0

    if tt > 1:
        print("fps = %f" % (float(nCount-nCount0)/tt))
        print("count = %d" % (nCount))
        t0=t
        nCount0=nCount
        


