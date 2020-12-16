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
import ksj.cam


if __name__ == '__main__':

    avi_path = './'

    cam =  ksj.cam.Ksjcam()
    cam.SetExptime(0,3)

    ts = time.time()


    st = datetime.datetime.fromtimestamp(ts).strftime('%Y%m%d%H%M%S')

    # fourcc = cv2.VideoWriter_fourcc('M', 'J', 'P', 'G')
    fourcc = cv2.VideoWriter_fourcc(*'XVID')

    # 1280,720是摄像头的分辨率，必须设置摄像头支持的格式，否则视频录制不成功

    out = cv2.VideoWriter(avi_path + st+'.avi',fourcc, 10.0, (1280,960))


    while 1:
        image = cam.read(0)

        # frame = cv2.imread("time.jpeg")
        # dir(image)
        frame = image
        # cv2.imshow('frame', frame)
        # cv2.waitKey(1)
        # # dir(frame)
        # frame = cv.fromarray(image)



        if True:
            # frame = cv2.flip(frame,0)
            # 写入帧
            out.write(frame)
            cv2.imshow('frame',frame)
            cv2.waitKey(1)
            # if cv2.waitKey(1) & 0xFF == ord('q'):
            #     break
        else:
            break

    out.release()
    out1.release()
    cv2.destroyAllWindows()


