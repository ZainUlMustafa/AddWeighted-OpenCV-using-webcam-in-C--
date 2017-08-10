// Zain Ul Mustafa 2017
// OpenCV addWeighted project to add a weight to a live camera feed/webcam feed.

//Connect with me:
/*	Twitter: http://www.twitter.com/ZainsOfficial/
	Facebook: http://www.facebook.com/ZainsOfficial/
	Github: http://github.com/ZainUlMustafa/
*/

/* This OpenCV software is allowed for any user to copy, modify, merge, and distribute in any of his/her project.
Complete repository for this project is available on github. If you find this project anywhere except github, it
is to be noted that it is not made by me and not distributed by me. 

Please follow this link to get to the original repository of github for this project
Github shortened link (no spam and no ads): http://bit.ly/2vSEAfT
*/


#include <opencv\cv.h>
#include <opencv\highgui.h>
using namespace cv;
#include<iostream>
using namespace std;

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;
double gamma = 0;

Mat cameraFeed;
Mat grayScale;
Mat weight;
Mat destination;

//default video capture dimensions 640x480
const int frameWidth = 640;
const int frameHeight = 480;

void trackbarCallback(int, void*){
	alpha = (double) alpha_slider/alpha_slider_max;
	beta = (1 - alpha);
	addWeighted(cameraFeed, alpha, weight, beta, gamma, destination);
	cvtColor(destination, grayScale, COLOR_BGR2GRAY);

	imshow("CAMERA_FEED", cameraFeed);
	imshow("GRAYSCALE", grayScale);
	imshow("WEIGHT_PICTURE", weight);
	imshow("DESTINATION_WINDOW", destination);
}

int main(){
	cout<<"Enter the weight picture source: \n (e.g C:/User/Desktop/abc.jpg)"<<endl<<">> ";
	String source;
	cin>>source;

	Size size(frameWidth, frameHeight);
	alpha_slider = 0;

	//weight picture dimension must equal the dimension of cameraFeed
	weight = imread(source);
	resize(weight, weight, size);

	VideoCapture capture;
	capture.open(0);
	//setting the dimensions of webcam frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, frameWidth);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, frameHeight);
	if(!capture.isOpened()){
		cout<<"Capture not open successfully"<<endl;
		getchar();
		return -1;
	}


	while(1){
		capture.read(cameraFeed);

		char TrackbarName[50];
		sprintf(TrackbarName, "Alpha value: %d", alpha_slider_max);
		createTrackbar(TrackbarName, "TRACKBAR", &alpha_slider, alpha_slider_max, trackbarCallback);
		trackbarCallback(0, 0);

		namedWindow("CAMERA_FEED");
		namedWindow("GRAYSCALE");
		namedWindow("WEIGHT_PICTURE");
		namedWindow("DESTINATION_WINDOW", 1);
		namedWindow("TRACKBAR", 0);
		resizeWindow("TRACKBAR", 600, 40);

		//you don't need to destroy the windows as they are in the continuous loop
		waitKey(30);
	}

	return 0;
}
