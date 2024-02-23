import socket
import sys
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('172.16.10.1', 8888))

magicword='000102030405060708092828'.decode('hex')
while 1: #write replace by while 1 if you want this to not stop
	s.send(magicword)	
    data = s.recv(1024)
    sys.stdout.write(data)
    n=n+1
