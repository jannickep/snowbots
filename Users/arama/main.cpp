#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

struct HSVrange{
	double huemin;
	double huemax;
	double satmin;
	double satmax;
	double valmin;
	double valmax;
};
void DoNothing(int a, void *b){

}

int main() {

	//Acess the first camera
	VideoCapture camera(0);

	//Declare our windows
	namedWindow("Original", 1);
	namedWindow("HSV", 1);
	namedWindow("Red", 1);
	namedWindow("Blu", 1);

	//Check camera opened
	if (!camera.isOpened()){
		std::cout << "FUCK SHIT IM BLIND!" << std::endl;
	}

	//UNLEASH
	//THE TRACKBARS!
	std::string TrackbarNames[] =  {
			//Red
			"Red Hue Min", "Red Hue Max",
			"Red Sat Min", "Red Sat Max",
			"Red Val Min", "Red Val Max",

			//vs Blu
			"Blu Hue Min", "Blu Hue Max",
			"Blu Sat Min", "Blu Sat Max",
			"Blu Val Min", "Blu Val Max"
	};
	uint TrackbarMax[] = {
			180, 180,
			255, 255,
			255, 255,
			180, 180,
			255, 255,
			255, 255,
	};
	for(size_t i = 0; i < 12; ++i){
		std::string window;
		if(i<6){
			window = "Red";
		}else{
			window = "Blu";
		}
		createTrackbar(TrackbarNames[i], window, 0, TrackbarMax[i], DoNothing, 0);
	}

	//Our epic (in the traditional sense) main loop
	while (true) {
		//Make our matrices
		Mat original;
		Mat hsv;
		Mat red;
		Mat blu;

		//And our scalars
		//Note HSV ranges H: 0 - 180, S: 0 - 255, V: 0 - 255
		Scalar red_min = Scalar(
				getTrackbarPos("Red Hue Min", "Red"),
				getTrackbarPos("Red Sat Min", "Red"),
				getTrackbarPos("Red Val Min", "Red"));
		Scalar red_max = Scalar(
				getTrackbarPos("Red Hue Max", "Red"),
				getTrackbarPos("Red Sat Max", "Red"),
				getTrackbarPos("Red Val Max", "Red"));
		Scalar blu_min = Scalar(
				getTrackbarPos("Blu Hue Min", "Blu"),
				getTrackbarPos("Blu Sat Min", "Blu"),
				getTrackbarPos("Blu Val Min", "Blu"));
		Scalar blu_max = Scalar(
				getTrackbarPos("Blu Hue Max", "Blu"),
				getTrackbarPos("Blu Sat Max", "Blu"),
				getTrackbarPos("Blu Val Max", "Blu"));

		//Contains range (there HAS to be a better way of doing this)
		HSVrange redrange, blurange;

		//Set the values of these scalars
		//These do not filter yet because IDK what I should have as default

		//Check that we are getting images from camera
		int cameracount = 0;
		do{
			cameracount++;
			camera.read(original);

			//If we've tried to get an image over 100 times and have had no success
			//then something, somewhere, fucked up big time.
			if(cameracount > 100){
				std::cout << "camera.read() is returning an empty matrix" << std::endl;
				return -1;
			}
		}while(original.empty());


		//Get a HSV image (which BTW looks trippy as fuck)
		cvtColor(original, hsv, CV_BGR2HSV);

		//Filter for red
		inRange(hsv, red_min, red_max, red);

		//Filter for blu
		inRange(hsv, blu_min, blu_max, blu);

		imshow("Original", original);
		imshow("HSV", hsv);
		imshow("Red", red);
		imshow("Blu", blu);
		if (waitKey(30) >= 0)break;
	}
	return 0;
}
