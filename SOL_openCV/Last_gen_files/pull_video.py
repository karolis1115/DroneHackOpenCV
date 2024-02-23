
import codecs
import threading
import socket
import sys
from time import sleep
#file = open("file.bin", "wb")
magicword= '000102030405060708092828'
decode_hex= codecs.getdecoder("hex_codec")
magicword= decode_hex(magicword)[0]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s2= socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('172.16.10.1', 8888))
#s2.connect(('172.16.10.1',8080))
while(True):
    sleep(4)
    s.send(magicword)
    data = s.recv(128)
    sys.stdout.buffer.write(data)
    #file.write(data)
s.close()
s2.close()
