#!/bin/sh
python ./pull_video.py |gst-launch-1.0 fdsrc fd=0 ! h264parse ! avdec_h264 ! autovideosink


