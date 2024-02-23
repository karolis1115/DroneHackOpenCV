import os
os.add_dll_directory(r"C:/opencv/gst/1.0/msvc_x86_64/bin") #windows
#sys.path.append('/usr/local/lib/python3.9/site-packages') #linux/rpi
import numpy
import cv2
print(cv2.__version__)