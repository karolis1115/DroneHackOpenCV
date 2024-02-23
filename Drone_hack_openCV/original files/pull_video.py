import socket
import sys
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('172.16.10.1', 8888))

magicword='495464000000580000009bf89049c926884d4f922b3b33ba7eceacef63f77157ab2f53e3f768ecd9e18547b8c22e21d01bfb6b3de325a27b8fb3acef63f77157ab2f53e3f768ecd9e185eb20be383aab05a8c2a71f2c906d93f72a85e7356effe1b8f5af097f9147f87e'.decode('hex')

s.send(magicword)
data = s.recv(106) 
n=0
while n<150000: #write replace by while 1 if you want this to not stop
    data = s.recv(1024)
    sys.stdout.write(data)
    n=n+1
s.close()
