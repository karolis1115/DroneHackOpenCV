# DroneHackOpenCV
A project where I take a Wi-Fi controlled drone bought from AliExpress, reverse engineer the protocol and control it with python. The end goal is to Use OpenCV and Aruco markers to create a sort of drone positioning system

## Inspiration
This project was inspired by a HackaDay article called:  
Controlling a JJRC H37 Elfie quad from a PC
Link: https://hackaday.io/project/19680-controlling-a-jjrc-h37-elfie-quad-from-a-pc

The drone I used for this project was the "**JJRC H49 SOL**". cheap Chinese toy drone with a 720P camera remote control and Wi-Fi control and video transmission.
All for just 20 euros more or less. Unfortunately seems like it's hard to come by and is more expensive these days.


This was my first introduction to hardware hacking. And sparked an interest in the subject.
I found that the drone exposes a telnet shell that gives access to the RTOS used by the Wi-Fi module in the drone. But I couldn't get too far with that other than finding what ports the drone exposed.

So Initially I explored reverse engineering the protocols the drone was using to stream video and control the drone. However, sometime later I discovered that the drone has a separate PCB inside the drone that handled the video and control data transmission. My mind was blown when I found an exposed UART interface, connected it to a serial monitor and got into a bootloader shell (U-boot).
A whole new obsession with dumping firmware and trying to unlock its secrets emerged. I was not able to get very far with it as soon as the RTOS booted it disabled the UART communication and the telnet shell did not expose enough useful commands to take full control over the firmware. I tried to compile my own version of the RTOS called "rt-thread" but ran into problems with the module not loading the drivers for the Wi-Fi module.
Regardless of that, I think from that moment on I started dumping contents of a bunch of electronic devices that have an easily accessible Flash IC or EPROM.
