import numpy as np

import sys
import preprocess
import cv2

def BGR2I444_test(bgr_file):
    src = np.fromfile(bgr_file,np.uint8)
    dst = np.ndarray((width*height*3,),dtype=np.uint8)
    preprocess.BGR2I44(src,dst,width,height)


width=640
height = 480


nv12_file ='*.NV12'
nv21_file = '*.NV21'
I420_file = '*.I420'
I444_file = "*.I444"

