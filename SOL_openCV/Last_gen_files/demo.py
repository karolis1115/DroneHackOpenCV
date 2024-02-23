import socket
from time import sleep

# The IP of the quadcopter plus the UDP port it listens to for control commands
IPADDR = '172.16.10.1'
PORTNUM = 55934
 
# "idle" message, this is the first message the app sends to the quadcopter when you enable the controls
PIDLE = '6680800180008199'.decode('hex') 
# "altitude hold" this is what the app starts sending to the quadcopter once you enable the altitude hold
PHOLD = '6680808080000099'.decode('hex')
# "arm" this is what the app sends to the quadcopter when you press the "up" arrow that make the motors start to spin before taking off
PSPIN = '6680808080010199'.decode('hex')
# this is the message the app sends to the quadcopter when you press the "emergency stop" button
PSTOP = '6680808080040499'.decode('hex')
 
# initialize a socket
# SOCK_DGRAM specifies that this is UDP
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
 
# connect the socket
s.connect((IPADDR, PORTNUM))
 
# send a series of commands
for n in range(0,100): # send the idle command for some 5 seconds
    s.send(PIDLE)
    sleep(0.05) # the app sends a packet of 8 bytes every 50 miliseconds

for n in range(0,100): # send the idle + altitude hold command for some 5 seconds
    s.send(PHOLD)
    sleep(0.05)

for n in range(0,21): # send the "arm" command for 1 second (this is what the app seems to do when you press the up arrow to arm the quadcopter
    s.send(PSPIN)
    sleep(0.05)

for n in range(0,100): # send the idle + altitude hold command for some 5 seconds
    s.send(PHOLD)
    sleep(0.05)

for n in range(0,21): # send the "emergency stop" command for 1 second
    s.send(PSTOP)
    sleep(0.05)

for n in range(0,200): # send the idle + altitude hold for some 5 seconds
    s.send(PHOLD)
    sleep(0.05)


# close the socket
s.close()
