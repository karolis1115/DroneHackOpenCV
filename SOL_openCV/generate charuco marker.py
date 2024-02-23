import os
import sys
#sys.path.append('/usr/local/lib/python3.8/site-packages')
os.add_dll_directory(r"C:/opencv/gst/1.0/msvc_x86_64/bin")

import cv2
from cv2 import aruco

aruco_dict = aruco.Dictionary_get(aruco.DICT_5X5_250)
aruco_dict.bytesList=aruco_dict.bytesList[30:,:,:]
board = aruco.CharucoBoard_create(7, 5, 1, 0.5, aruco_dict)

imboard = board.draw((2000, 2000))
cv2.imwrite("chessboard1.png", imboard)