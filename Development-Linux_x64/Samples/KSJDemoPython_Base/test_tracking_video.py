# coding:utf-8
import cv2
import os
import time
import datetime
import datetime
import signal
import threading
import time
import numpy as np
import cv2
import math
from PIL import Image
from PIL import ImageEnhance
#from pylibdmtx.pylibdmtx import decode
#import pyzbar.pyzbar as pyzbar

import ksj.cam as kcam


if __name__ == '__main__':

    nFrameCount = 0
    decodeflag = 0

    cam =  kcam.Ksjcam()
    cam.SetExptime(0, 5)  # 设置曝光时间 

    cv2.namedWindow('input_image', cv2.WINDOW_AUTOSIZE)

    while True:
       # cam.SetExptime(0, 3)  # 设置曝光时间 
        frame = cam.read(0)
        nHeight = frame.shape[0]
        nWidth = frame.shape[1]
        
        cv2.imshow('image', frame)
       # cv2.imwrite('bigimage01.jpg',frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        if decodeflag == 1:
            break

        print(nFrameCount)
        if nFrameCount == 0:
            nTimeStart = datetime.datetime.now()

        if nFrameCount == 99:
            nTimeStop = datetime.datetime.now()
            deltt= (nTimeStop - nTimeStart)
	    #print("image_shape:" + str(image.shape))
            print("cam fps: %f" % (100/(deltt.total_seconds())))
            nFrameCount = -1
        nFrameCount = nFrameCount + 1

    cv2.destroyAllWindows()


