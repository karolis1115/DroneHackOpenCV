import os
import sys
#sys.path.append('/usr/local/lib/python3.8/site-packages')
os.add_dll_directory(r"C:/opencv/gst/1.0/msvc_x86_64/bin")
import cv2
import codecs
import threading
import socket
from time import sleep
magicword= '000102030405060708092828'
decode_hex= codecs.getdecoder("hex_codec")
magicword= decode_hex(magicword)[0]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#s2= socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('172.16.10.1', 8888))
#s2.connect(('172.16.10.1',8080))
#file =open('dat.bin','wb')
s.send(magicword)
try:
    while(True):
        s.send(magicword)
        data = s.recv(128)
        sys.stdout.buffer.write(data)
        #file.write(data)
except (BrokenPipeError, IOError):
    pass
sys.stderr.close()
s.shutdown(socket.SHUT_RDWR)
s.close()
#s2.close()
#file.close()
