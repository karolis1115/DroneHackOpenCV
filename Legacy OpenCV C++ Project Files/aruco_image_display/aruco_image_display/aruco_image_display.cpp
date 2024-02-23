// aruco_image_display.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <thread>
#include "aruco.h"
using namespace std;
using namespace cv;
using namespace aruco;
using namespace std;
int main() {

	Mat markerImage;
	// Generate the marker
	drawMarker(33, 200, markerImage, 1);
}