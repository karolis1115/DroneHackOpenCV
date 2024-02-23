gst-launch-1.0 tcpclientsrc host=172.16.10.1 port=8888 ! h264parse ! decodebin ! identity sync=false ! autovideosink
pause