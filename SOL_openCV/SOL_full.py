#import keyboard
import os
os.add_dll_directory(r"C:/opencv/gst/1.0/msvc_x86_64/bin")
import codecs
import threading
import socket
import sys
import cv2
import numpy as np
import cv2.aruco as aruco 
from time import sleep

dictionary = aruco.Dictionary_get(aruco.DICT_6X6_250)
parameters =  aruco.DetectorParameters_create()

magicword= '000102030405060708092828'
decode_hex= codecs.getdecoder("hex_codec")
magicword= decode_hex(magicword)[0]


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#s2= socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('172.16.10.1', 8888))
#s2.connect(('172.16.10.1',8080))
file = open("dat.bin", "wb")

for i in range(5000):
    s.send(magicword)
    data = s.recv(128) #buffer
    file.write(data)

cap = cv2.VideoCapture('fdsrc fd=0 ! h264parse ! avdec_h264 max-threads=1 output-corrupt=true ! autovideoconvert ! appsink sync=false',cv2.CAP_GSTREAMER)
#cap = cv2.VideoCapture('filesrc location=dat.bin ! h264parse ! avdec_h264 ! videoconvert !queue !appsink sync=false', cv2.CAP_GSTREAMER)
#cap = cv2.VideoCapture("filesrc location=dat.bin ! video/x-raw format=BGRx width= 1280 height=960 framerate=20/1! appsink sync=false", cv2.CAP_GSTREAMER)
#cap = cv2.VideoCapture('fdsink fd=0 ! avdec_h264 max-threads=1 ! videoconvert ! appsink sync=false',cv2.CAP_GSTREAMER)
#cap = cv2.VideoCapture('videotestsrc pattern=snow !  videoconvert ! appsink sync=false',cv2.CAP_GSTREAMER)

while(True):
    '''
    if keyboard.is_pressed('.'):
        s2.send(decode_hex('ff087e3f403f90101040cb')[0]) #arm
    elif keyboard.is_pressed(','):
        s2.send(decode_hex('ff087e3f403f901010808b')[0]) #land
    elif keyboard.is_pressed('space'):
        s2.send(decode_hex('ff087e3f403f901010a06b')[0])# E stop
    else:
        s2.send(decode_hex('ff 08 7e 3f 40 3f 90 10 10 00 0b')[0])
        '''
    s.send(magicword)
    data = s.recv(128) #buffer
    file.write(data)
    Ret,frame = cap.read()
    if not Ret:
        #print ("empty frame!")
        continue
    markerCorners, markerIds, rejectedCandidates = aruco.detectMarkers(frame, dictionary, parameters=parameters)
    aruco.drawDetectedMarkers(frame, markerCorners, markerIds)
    aruco.drawDetectedMarkers(frame, rejectedCandidates, borderColor=(255, 0, 0))
    cv2.imshow("yeets", frame)
    cv2.waitKey(1)
cap.release()
s.close()
file.close()
#s2.close()
