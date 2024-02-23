import socket
import pygame
import time
from math import floor

def get():
    #pygame gives the analogue joystick position as a float that goes from -1 to 1, the code below takes the readings and
    #scales them so that they fit in the 0-255 range the quadcopter expects
    a=int(floor((j.get_axis(2)*0.3+1)*127.5)) 
    b=int(floor((-j.get_axis(3)*0.3+1)*127.5))
    c=int(floor((-j.get_axis(1)+1)*127.5))
    d=int(floor((j.get_axis(0)+1)*127.5)) 
    commands=(j.get_button(6)<<2)|(j.get_button(8)) #only two buttons are used so far: "arm" and emergency stop
    out=(102<<56)|a<<48|b<<40|c<<32|d<<24|commands<<16|(a^b^c^d^commands)<<8|153
    pygame.event.pump()
    return out

# The IP of the quadcopter plus the UDP port it listens to for control commands
IPADDR = '172.16.10.1'
PORTNUM = 8895

pygame.init()
j = pygame.joystick.Joystick(1)
j.init()
 
# initialize a socket
# SOCK_DGRAM specifies that this is UDP
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
 
# connect the socket
s.connect((IPADDR, PORTNUM))

while True:
    s.send(format(get(),'x').decode('hex')) #ugly hack, I guess there's a better way of doing this
    time.sleep(0.05)

# close the socket
s.close()
