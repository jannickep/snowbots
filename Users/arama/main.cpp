#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

struct Trackbar{
	std::string Name;
	std::string WindowName;
	int StartPos;
	int MaxPos;
};

void DoNothing(int a, void *b){

}

//Trackbars
Trackbar
RedHMin, RedHMax, RedSMin,
RedSMax, RedVMin, RedVMax,
BluHMin, BluHMax, BluSMin,
BluSMax, BluVMin, BluVMax;

void SetTrackbars(){
	//Set RedHMin:
	RedHMin.Name = "Red Hue Min";
	RedHMin.WindowName = "Red";
	RedHMin.StartPos = 0;
	RedHMin.MaxPos = 180;

	//Set RedHMax:
	RedHMax.Name = "Red Hue Max";
	RedHMax.WindowName = "Red";
	RedHMax.StartPos = 180;
	RedHMax.MaxPos = 180;

	//Set RedSMin:
	RedSMin.Name = "Red Sat Min";
	RedSMin.WindowName = "Red";
	RedSMin.StartPos = 0;
	RedSMin.MaxPos = 255;

	//Set RedSMax:
	RedSMax.Name = "Red Sat Max";
	RedSMax.WindowName = "Red";
	RedSMax.StartPos = 255;
	RedSMax.MaxPos = 255;

	//Set RedVMin:
	RedVMin.Name = "Red Val Min";
	RedVMin.WindowName = "Red";
	RedVMin.StartPos = 0;
	RedVMin.MaxPos = 255;

	//Set RedVMax:
	RedVMax.Name = "Red Val Max";
	RedVMax.WindowName = "Red";
	RedVMax.StartPos = 255;
	RedVMax.MaxPos = 255;

	//Set BluHMin:
	BluHMin.Name = "Blu Hue Min";
	BluHMin.WindowName = "Blu";
	BluHMin.StartPos = 0;
	BluHMin.MaxPos = 180;

	//Set BluHMax:
	BluHMax.Name = "Blu Hue Max";
	BluHMax.WindowName = "Blu";
	BluHMax.StartPos = 180;
	BluHMax.MaxPos = 180;

	//Set BluSMin:
	BluSMin.Name = "Blu Sat Min";
	BluSMin.WindowName = "Blu";
	BluSMin.StartPos = 0;
	BluSMin.MaxPos = 255;

	//Set BluSMax:
	BluSMax.Name = "Blu Sat Max";
	BluSMax.WindowName = "Blu";
	BluSMax.StartPos = 255;
	BluSMax.MaxPos = 255;

	//Set BluSMin:
	BluVMin.Name = "Blu Val Min";
	BluVMin.WindowName = "Blu";
	BluVMin.StartPos = 0;
	BluVMin.MaxPos = 255;

	//Set BluSMax:
	BluVMax.Name = "Blu Val Max";
	BluVMax.WindowName = "Blu";
	BluVMax.StartPos = 255;
	BluVMax.MaxPos = 255;
}

void Calibrate(Mat source, std::vector<Trackbar> trackbars){
	//Because there should only be 6 trackbars right now:
	assert(trackbars.size() == 6);

	Scalar hsvmean;
	Scalar hsvstddev;
	meanStdDev(source, hsvmean, hsvstddev);
	std::cout << "Mean: " << hsvmean << std::endl;
	std::cout << "StdDev: " << hsvstddev << std::endl;

	for(size_t i = 0; i < 6; i++){
		//Since the order trackbars are defined in is min, max, min, max

		int newposition;
		int j = i/2;
		if(i%2 == 0){
			//Even case (min)
			//ensure we don't have a value below 0
			if(hsvmean.val[j] > hsvstddev.val[j]){
				newposition = hsvmean.val[j] - hsvstddev.val[j];
			}else{
				newposition = 0;
			}
			setTrackbarPos(
					trackbars[i].Name,
					trackbars[i].WindowName,
					newposition);
		}else{
			//Odd case (max)
			//Ensure we don't have a value larger than the max value for the trackbar
			if((hsvmean.val[j] + hsvstddev.val[j]) < trackbars[i].MaxPos){
				newposition = hsvmean.val[j] + hsvstddev.val[j];
			}else{
				newposition = trackbars[i].MaxPos;
			}
			setTrackbarPos(
					trackbars[i].Name,
					trackbars[i].WindowName,
					newposition);
		}
		std::cout << "------------------------------------" << std::endl;
		std::cout << "count: " << j << std::endl;
		std::cout << "nepos: " << newposition << std::endl;
		std::cout << "name: " << trackbars[i].Name << std::endl
				<< "window: " << trackbars[i].WindowName << std::endl;
	}
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
		std::cout << "IM BLIND!" << std::endl;
		return -1;
	}

	//UNLEASH
	//THE TRACKBARS!
	SetTrackbars();
	std::vector<Trackbar> AllTrackbars;
	AllTrackbars.push_back(RedHMin);
	AllTrackbars.push_back(RedHMax);
	AllTrackbars.push_back(RedSMin);
	AllTrackbars.push_back(RedSMax);
	AllTrackbars.push_back(RedVMin);
	AllTrackbars.push_back(RedVMax);
	AllTrackbars.push_back(BluHMin);
	AllTrackbars.push_back(BluHMax);
	AllTrackbars.push_back(BluSMin);
	AllTrackbars.push_back(BluSMax);
	AllTrackbars.push_back(BluVMin);
	AllTrackbars.push_back(BluVMax);
	std::cout << "AllTrackbars.size(): " << AllTrackbars.size() << std::endl;
	std::cout << "sizeof(AllTrackbars): " << sizeof(AllTrackbars) << std::endl;

	for(size_t i = 0; i < AllTrackbars.size(); ++i){
		createTrackbar(
				AllTrackbars[i].Name,
				AllTrackbars[i].WindowName,
				&AllTrackbars[i].StartPos,
				AllTrackbars[i].MaxPos,
				DoNothing);
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

		//Set the values of these scalars
		//These do not filter yet because IDK what I should have as default

		//Check that we are getting images from camera
		int cameracount = 0;
		do{
			cameracount++;
			camera.read(original);

			//If we've tried to get an image over 100 times and
			//have had no success then something, somewhere, fucked up big time.
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

		//Deal with key events
		int key = waitKey(30);
		switch(char(key)){
		case 27:
			std::cout << "Escape key press detected. " << std::endl;
			return (0);
		case 'r':
			std::cout << "Calibrating red" << std::endl;
			break;
		case 'b':
			std::cout << "Calibrating blu" << std::endl;
			std::vector<Trackbar> bluvector(&AllTrackbars[6], &AllTrackbars[12]);
			Calibrate(hsv, bluvector);
			break;
		}
	}
	return 0;
}
