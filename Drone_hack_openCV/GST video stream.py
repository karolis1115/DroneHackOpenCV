import socket
import sys
import codecs
import gi
from gi.repository import Gst
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('172.16.10.1', 8620))
Gst.init(sys.argv)


magicword= '000102030405060708092828'
decode_hex = codecs.getdecoder("hex_codec")
magicword = decode_hex(magicword)[0]
pipeline = Gst.parse_launch("gst-launch-1.0 fdsrc fd=0 ! h264parse ! avdec_h264 ! xvimagesink sync=false")
while 1: #write replace by while 1 if you want this to not stop
    s.send(magicword)
    data = s.recv(1024)
    sys.stdout.write(data)
