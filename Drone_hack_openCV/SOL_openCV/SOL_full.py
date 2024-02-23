#import keyboard
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
file = open("file.bin", "wb")
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s2= socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('172.16.10.1', 8888))
s2.connect(('172.16.10.1',8080))
while(True):
    '''
    if keyboard.is_pressed('.'):
        s2.send(decode_hex('ff087e3f403f90101040cb')[0]) #arm
    elif keyboard.is_pressed(','):
        s2.send(decode_hex('ff087e3f403f901010808b')[0]) #land
    elif keyboard.is_pressed('space'):
        s2.send(decode_hex('ff087e3f403f901010a06b')[0])# E stop
    else:
        s2.send(decode_hex('ff087e3f403f901010000b')[0])
        '''
    s.send(magicword)
    data = s.recv(1024) #buffer
    file.write(data)
    #sys.stdout.buffer.write(data)
    cap = cv2.VideoCapture('filesrc location=file.bin ! h264parse ! avdec_h264 max-threads=1 ! videoconvert ! appsink sync=false',cv2.CAP_GSTREAMER)
    #cap = cv2.VideoCapture('videotestsrc pattern=snow !  videoconvert ! appsink sync=false',cv2.CAP_GSTREAMER)
    print(cap.isOpened())
    Ret,frame = cap.read()
    if not Ret:
        print ("empty frame!")
        continue
    markerCorners, markerIds, rejectedCandidates = aruco.detectMarkers(frame, dictionary, parameters=parameters)
    aruco.drawDetectedMarkers(frame, markerCorners, markerIds)
    aruco.drawDetectedMarkers(frame, rejectedCandidates, borderColor=(255, 0, 0))
    cv2.imshow("yeets", frame)
    if cv2.waitKey(1)&0xFF == ord('q'):
        break
cap.release()
s.close()
s2.close()
