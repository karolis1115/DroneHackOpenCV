import sys

state=0
message=""
yaw=0
roll=0
pitch=0
throttle=0
commands=0
err=0
n=0

for line in sys.stdin:
	if state==0:
		pos=line.find("0x0010:")
		if pos!=-1:
			message=line[(pos+39):(pos+43)]+line[(pos+44):(pos+48)]
			roll=int(line[(pos+41):(pos+43)],16)
			pitch=int(line[(pos+44):(pos+46)],16)
			throttle=int(line[(pos+46):(pos+48)],16)
			state=1
	else:
		state=0
		pos=line.find("0x0020:")
		if pos!=-1:
			message=message+line[(pos+9):(pos+13)]+line[(pos+14):(pos+18)]
			yaw=int(line[(pos+9):(pos+11)],16)
			commands=int(line[(pos+11):(pos+13)],16)
			err=int(line[(pos+13):(pos+15)],16)
			n=n+1
			if n==10: #this is a little trick that only displays 1 out of 10 messages
				sys.stdout.write(message+" roll:"+str(roll)+" pitch:"+str(pitch)+" throttle:"+str(throttle)+" yaw:"+str(yaw)+" commands:"+format(commands,"08b")+" err:"+format(roll^pitch^throttle^yaw^commands,'x')+'\n')
