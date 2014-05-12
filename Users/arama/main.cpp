#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define RED Scalar(0,0,255)
#define GREEN Scalar(0,255,0)
#define BLUE Scalar(255,0,0)

void DoNothing(int a, void *b){

}

struct Trackbar{
	string Name;
	string WindowName;
	int StartPos;
	int MaxPos;
};

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

void Calibrate(Mat source, vector<Trackbar> trackbars){
	//Because there should only be 6 trackbars right now:
	assert(trackbars.size() == 6);

	Scalar hsvmean;
	Scalar hsvstddev;
	meanStdDev(source, hsvmean, hsvstddev);
	cout << "Mean: " << hsvmean << endl;
	cout << "StdDev: " << hsvstddev << endl;

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
	}
}


int DetectMaxColorColumn(Mat source){
	//Assert that were getting a single channel system
	//That being said I don't think doing this on HSV would break the program
	//It'd just be kindda pointless
	assert(source.channels() == 1);
	vector<int> columnTotals;

	//Calculate which col of pixels has the most of our color
	reduce(source, columnTotals, 0, CV_REDUCE_SUM, -1);

	//Is it a weird way of finding a distance? yes.
	//Does it work? yes.And it will do so efficiently.
	//BTW: this calculate the position of the column w/ the highest sum
	return distance(columnTotals.begin(), max_element(columnTotals.begin(), columnTotals.end()));
}

int main() {
	//Global vars
	//for calibrating
	bool calibrating =  false;
	double calibrationZoneMin = 0.4;
	double calibrationZoneMax = 0.6;
	double zoneReSize = 0.01;

	//Acess the first camera
	VideoCapture camera(0);

	//Declare our windows
	namedWindow("Original", 1);
	namedWindow("HSV", 1);
	namedWindow("Red", 1);
	namedWindow("Blu", 1);

	//Check camera opened
	if (!camera.isOpened()){
		cout << "IM BLIND!" << endl;
		return -1;
	}

	//UNLEASH
	//THE TRACKBARS!
	SetTrackbars();
	vector<Trackbar> AllTrackbars;
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

		//Check that we are getting images from camera
		int cameracount = 0;
		do{
			cameracount++;
			camera.read(original);

			//If we've tried to get an image over 100 times and
			//have had no success then something, somewhere, fucked up big time.
			if(cameracount > 100){
				cout << "camera.read() is returning an empty matrix" << endl;
				return -1;
			}
		}while(original.empty());


		//Get a HSV image (which BTW looks trippy as fuck)
		cvtColor(original, hsv, CV_BGR2HSV);

		//Filter for red
		inRange(hsv, red_min, red_max, red);

		//Filter for blu
		inRange(hsv, blu_min, blu_max, blu);


		if(calibrating){
			rectangle(
					original,
					Point(original.cols*calibrationZoneMin,original.rows*calibrationZoneMin),
					Point(original.cols*calibrationZoneMax,original.rows*calibrationZoneMax),
					GREEN,
					1,
					8,// can be 4, 8 or CV_AA (but I don't think we need anti aliasing do we?)
					0);
		}

		//Display a line to show perceived max on screen
		//Starting with Red
		int redPos = DetectMaxColorColumn(red);
		line(
				original,
				Point(redPos,0),
				Point(redPos,red.rows),
				RED,
				1,
				4,
				0
				);

		double bluPos = DetectMaxColorColumn(blu);
		line(
				original,
				Point(bluPos,0),
				Point(bluPos,blu.rows),
				BLUE,
				1,
				4,
				0
		);

		//Display images (note: HSV image is being displayed as RGB)
		imshow("Original", original);
		imshow("HSV", hsv);
		imshow("Red", red);
		imshow("Blu", blu);

		//Deal with key events
		int key = waitKey(10);
		switch(char(key)){

		//Escape key
		case 27:
			cout << "Escape key press detected. " << endl;
			return (0);

		//C key
		case 'c':
			//Toggles calibration so that an overlay can be displayed before calibrating
			//Added bonus: no more accidental calibrations
			if(!calibrating){
				cout << "Ready to calibrate." << endl;
				cout << "c: cancel calibration" << endl;
				cout << "b: calibrate blue" << endl;
				cout << "r: calibrate red " << endl;
				cout << "The calibration zone is represented by the green rectangle." << endl;
				cout << "To change the size of the rectangle press '[' and ']'" << endl;
				calibrating = true;
			}else{
				cout << "Calibrating cancelled" << endl;
				calibrating = false;
			}
			break;

		//R key
		case 'r':
			if(calibrating){
				cout << "Calibrating red" << endl;
				//Make a Region of Interest
				//	by first making a Rect
				Rect zone = Rect(
						red.cols*calibrationZoneMin,
						red.rows*calibrationZoneMin,
						red.cols*(calibrationZoneMax-calibrationZoneMin),
						red.rows*(calibrationZoneMax-calibrationZoneMin)
						);

				//And then using said Rect as a mask for our image
				Mat calibrationZone = hsv(zone);
				vector<Trackbar> redvector(&AllTrackbars[0], &AllTrackbars[6]);
				Calibrate(calibrationZone, redvector);
				calibrating = false;
			}
			break;

		//B key
		case 'b':
			if(calibrating){
				cout << "Calibrating blu" << endl;
				//Make a Region of Interest
				//	by first making a Rect
				Rect zone = Rect(
						blu.cols*calibrationZoneMin,
						blu.rows*calibrationZoneMin,
						blu.cols*(calibrationZoneMax-calibrationZoneMin),
						blu.rows*(calibrationZoneMax-calibrationZoneMin)
				);

				//And then using said Rect as a mask for our image
				Mat calibrationZone = hsv(zone);
				vector<Trackbar> bluvector(&AllTrackbars[6], &AllTrackbars[12]);
				Calibrate(hsv, bluvector);
				calibrating = false;
			}
			break;
		//] key
		case ']':
			//because a rectangle larger than the screen is just silly
			if(calibrating
					&& calibrationZoneMin - zoneReSize > 0
					&& calibrationZoneMax + zoneReSize < 1){
				calibrationZoneMin -= zoneReSize;
				calibrationZoneMax += zoneReSize;
			}
			break;
		//[ Key
		case '[':
			//Arguably not necessary
			if(calibrating
					&& (calibrationZoneMin + zoneReSize < calibrationZoneMax - zoneReSize)){
				calibrationZoneMin += zoneReSize;
				calibrationZoneMax -= zoneReSize;
			}
			break;
		}
	}
	return 0;
}
