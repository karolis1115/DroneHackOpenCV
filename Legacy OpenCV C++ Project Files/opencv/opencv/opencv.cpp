#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/aruco.hpp"
#include "opencv2/aruco/dictionary.hpp"
#include "opencv2/aruco/charuco.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/cudacodec.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudalegacy/NCV.hpp"
#include "opencv2/cudalegacy/cuda_runtime.h"
#include "opencv2/videoio.hpp"
#include "opencv2/tracking.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>



#pragma comment(lib, "Ws2_32.lib")
WSADATA wsaData;
using namespace std;
using namespace cv;
using namespace aruco;
using namespace cudacodec;
const int fps = 60;

	static bool readCameraParameters(string filename, Mat & camMatrix, Mat & distCoeffs) {
		FileStorage fs(filename, FileStorage::READ);
		if (!fs.isOpened())
			return false;
		fs["camera_matrix"] >> camMatrix;
		fs["distortion_coefficients"] >> distCoeffs;
		return true;
	}
	unsigned char* hexstr_to_char(const char* hexstr) {
		size_t len = strlen(hexstr);
		if (len % 2 != 0)
			return NULL;
		size_t final_len = len / 2;
		unsigned char* chrs = (unsigned char*)malloc((final_len + 1) * sizeof(*chrs));
		for (size_t i = 0, j = 0; j < final_len; i += 2, j++)
			chrs[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i + 1] % 32 + 9) % 25;
		chrs[final_len] = '\0';
		return chrs;
	}
	
	void recvDat() {
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		struct addrinfo* result2 = NULL, * ptr2 = NULL, hints2;
		ZeroMemory(&hints2, sizeof(hints2));
		hints2.ai_family = AF_INET;
		hints2.ai_socktype = SOCK_STREAM;
		hints2.ai_protocol = IPPROTO_TCP;
		getaddrinfo("172.16.10.1", "8888", &hints2, &result2);
		SOCKET ConnectSocket2 = INVALID_SOCKET;
		ptr2 = result2;
		ConnectSocket2 = socket(ptr2->ai_family, ptr2->ai_socktype, ptr2->ai_protocol);
		connect(ConnectSocket2, ptr2->ai_addr, (int)ptr2->ai_addrlen);
		char recvbuf[1280];
		ofstream fg("dat.bin", std::ios::binary | std::ios::out | std::ios::trunc);
		const char* sendbuf = "000102030405060708092828";
		while (1) {
			send(ConnectSocket2, (char*)hexstr_to_char(sendbuf), (int)strlen(sendbuf), 0);
			recv(ConnectSocket2, (char*)recvbuf, 1280, 0);
			fg.write(recvbuf, sizeof(recvbuf));
			//Sleep(10);
		}
		fg.close();
	}
	void datatrans(){
	    WSAStartup(MAKEWORD(2, 2), &wsaData);
		struct addrinfo* result = NULL, *ptr = NULL, hints;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;
		getaddrinfo("172.16.10.1", "8080", &hints, &result);
		SOCKET ConnectSocket = INVALID_SOCKET;
		ptr = result;
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		char IDLE[23] = "ff08003f403f1010100009";
		char ALT_HOLD[23] = "ff087e3f403f901010000b";
		char ARM[23] = "ff087e3f403f90101040cb";
		char LAND[23] = "ff087e3f403f901010808b";
		char LEFT[23] = "ff087e3f4000901010004a";
		char RIGHT[23] = "ff087e3f407e90101000cc";
		char FD[23] = "ff087e3f01409010100049";
		char BCK[23] = "ff087e3f7f4090101000cb";
		char UP[23] = "ff08fc3f403f901010008d";
		char DOWN[23] = "ff080040403f9010104048";
		char E_STOP[23] = "ff087e3f403f901010a06b";
		char Yaw_R[23] = "ff087e7e403f90101000cc";
		char Yaw_L[23] = "ff087e00403f901010004a";
		//VideoCapture vid("172.16.10.1:8888", CAP_FFMPEG);
		//vid.set(CAP_PROP_FOURCC, cv::VideoWriter::fourcc('H', '2', '6', '4'));
		//vid.set(CAP_PROP_FRAME_WIDTH, 1280);
		//vid.set(CAP_PROP_FRAME_HEIGHT, 720);
		//cv::Mat TempMat= Mat(720,1280,CV_8UC1,);
		cout << "loop begin";
		while (1) {
			if (GetAsyncKeyState(VK_OEM_COMMA))  send(ConnectSocket, (char*)hexstr_to_char(ARM), (int)strlen(ARM), 0);
			if (GetAsyncKeyState(VK_RETURN)) send(ConnectSocket, (char*)hexstr_to_char(LAND), (int)strlen(LAND), 0);
			if (GetAsyncKeyState(VK_LEFT)) send(ConnectSocket, (char*)hexstr_to_char(LEFT), (int)strlen(LEFT), 0);
			if (GetAsyncKeyState(VK_RIGHT)) send(ConnectSocket, (char*)hexstr_to_char(RIGHT), (int)strlen(RIGHT), 0);
			if (GetAsyncKeyState(VK_DOWN)) send(ConnectSocket, (char*)hexstr_to_char(BCK), (int)strlen(BCK), 0);
			if (GetAsyncKeyState(VK_UP)) send(ConnectSocket, (char*)hexstr_to_char(FD), (int)strlen(FD), 0);
			if (GetAsyncKeyState(0x57)) send(ConnectSocket, (char*)hexstr_to_char(UP), (int)strlen(UP), 0);
			if (GetAsyncKeyState(0x53)) send(ConnectSocket, (char*)hexstr_to_char(DOWN), (int)strlen(DOWN), 0);
			if (GetAsyncKeyState(VK_SPACE)) send(ConnectSocket, (char*)hexstr_to_char(E_STOP), (int)strlen(E_STOP), 0);
			if (GetAsyncKeyState(0x41)) send(ConnectSocket, (char*)hexstr_to_char(Yaw_L), (int)strlen(Yaw_L), 0);
			if (GetAsyncKeyState(0x44)) send(ConnectSocket, (char*)hexstr_to_char(Yaw_R), (int)strlen(Yaw_R), 0);
			else send(ConnectSocket, (char*)hexstr_to_char(ALT_HOLD), (int)strlen(ALT_HOLD), 0);
			//Sleep(20);
		}
		closesocket(ConnectSocket);
	    WSACleanup;
	}

void detectMarkers() {
	Scalar color1(180, 255, 50);
	Scalar color2(0,0,255);
	ofstream fr("dat.txt");
	//VideoCapture vid("vid.mp4"); // video file
	//VideoCapture vid("C:/Users/karol/.spyder-py3/myfile.bin"); // Video feed stream 
	VideoCapture vid(0); // internal or usb camera
	Mat inputImage;
	vector<int> markerIds;
	vector<vector<Point2f>> markerCorners, rejectedCandidates;
	Ptr<DetectorParameters> parameters = DetectorParameters::create();
	Ptr<Dictionary> dictionary = getPredefinedDictionary(DICT_ARUCO_ORIGINAL);
	while (vid.read(inputImage)){
		if (markerIds.size() > 0) {
			drawDetectedMarkers(inputImage, markerCorners, markerIds, color1);
			for (int i = 0; i < markerIds.size(); i++) {
				if(fr.is_open() != true)
					fr.open("dat.txt");
				fr << "Marker position: " << i << "  " << "Marker ID: " << markerIds[i] << endl;
			}
		}
		 if (markerIds.size() == 0) {
			 fr.open("dat.txt", std::ofstream::out | std::ofstream::trunc);
			 fr.close();
		}
		//drawDetectedMarkers(inputImage, rejectedCandidates,noArray(),color2);
		namedWindow("frame", WINDOW_AUTOSIZE);
		imshow("frame", inputImage);

		if (waitKey(1000 / fps) == 44) {
			break;
		}
	}
	fr.open("dat.txt", std::ofstream::out | std::ofstream::trunc);
	fr.close();
}

void poseEstim() {
	VideoCapture inputVideo;
	inputVideo.open(0);
	Mat cameraMatrix, distCoeffs;
	readCameraParameters("laptop.yml" ,cameraMatrix, distCoeffs);
	Ptr<Dictionary> dictionary = getPredefinedDictionary(DICT_ARUCO_ORIGINAL);
	while (inputVideo.grab()) {
		Mat image, imageCopy;
		inputVideo.retrieve(image);
		image.copyTo(imageCopy);
		vector<int> ids;
		vector<std::vector<Point2f>> corners;
		detectMarkers(image,dictionary, corners, ids);

		//if the detected number of markers is more than 0 ...
		if (ids.size() > 0) {
			drawDetectedMarkers(imageCopy, corners, ids);
			vector<Vec3d> rvecs, tvecs;
			estimatePoseSingleMarkers(corners, 0.02, cameraMatrix, distCoeffs, rvecs, tvecs);

			// draw axis for each marker
			for (int i = 0; i < ids.size(); i++) {
				drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.02);
			}
		}
		imshow("out", imageCopy);
		char key = (char)waitKey(1000/60);
		if (key == 27)
			break;
	}

}

int main() {
	//thread t2(recvDat);
	//thread t1(datatrans);
	recvDat();
	//datatrans();
	//quadDetect();
	//detectMarkers();
	//cout<<getBuildInformation();
	return 0;
	//poseEstim();
}