#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace std;
using namespace cv;
CascadeClassifier casc;
int main() {
	casc.load("cascade.xml");
	VideoCapture quad(0);
	Mat frame;
	while (quad.read(frame)) {
		vector<Rect> faces;
		Mat monoFrame;
		cvtColor(frame, monoFrame, COLOR_BGR2GRAY);
		equalizeHist(monoFrame, monoFrame);
		casc.detectMultiScale(monoFrame, faces,1.1,3,0);
		for (int i = 0; i < faces.size(); i++){
			Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
			ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);
		}
		imshow("frame", frame);
		if (waitKey(1000 / 30) == 44) break;
	}
}