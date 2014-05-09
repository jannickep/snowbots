#include <iostream>
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

//Include Libraries
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

void detectLines(void);
void findcentre(int);
void drawLine(int);
int countLines(int);

Mat image, image_grey, image_filter, image_thresholded, image_canny;
int const threshold_value = 160;
int blur_value = 7;
int const max_BINARY_value = 255;
int direction[3]; // x,y,z using right handed co-ordinate system, + z rotate counter clockwise


int main(int argc, char** argv) {

	//Read image
	image = imread(argv[1], 1);

	//Stop if no image data
	if (argc != 2 || !image.data) {
		printf("No image data \n");
		return -1;
	}
	//Create image_gray, gray_scaled version of image (needed for canny filter)
	cvtColor(image, image_grey, CV_RGB2GRAY);

	//Blur and threshold the image
	if (blur_value % 2 == 0) {
		blur_value = blur_value + 1;
	}
	medianBlur(image_grey, image_filter, blur_value);
	threshold(image_filter, image_thresholded, threshold_value,
			max_BINARY_value, THRESH_BINARY);

	//Canny Edge detection
	Canny(image_thresholded, image_canny, 50, 200, 3);

	// Detect lines
	detectLines();

	//Display image
	namedWindow("Display Image", CV_WINDOW_NORMAL);
	imshow("Display Image", image);

	//Display gray image
	namedWindow("Grey Image", CV_WINDOW_NORMAL);
	imshow("Grey Image", image_grey);

	//Display line image
	namedWindow("Lines", CV_WINDOW_NORMAL);
	imshow("Lines", image_thresholded);

	//Display Canny image
	namedWindow("Canny", CV_WINDOW_NORMAL);
	imshow("Canny", image_canny);

	// Wait until user presses a key, will close all windows
	waitKey(0);

	return 0;
}

void detectLines(void) {
	int const ROW = image.rows / 2-52;// starting row for checking direction
	//TODO: for... different horizontal lines I guess to minimize noise, starting with just the centreline
	//Draw lines on thresholded image, where it is being checked
	int numLines = 0;
	drawLine(ROW);
	findcentre(ROW);
	numLines = countLines(ROW);
}

//Draws a horizontal line at row
void drawLine(int row)
{
	Point pt1, pt2;
	pt1.x = 0;
	pt1.y = row;
	pt2.x = image.cols;
	pt2.y = row;
	line(image_canny, pt1, pt2, CV_RGB(250, 100, 255), 1, CV_AA);
}

void findcentre(int row) {
	//TODO: for pixels in line find high low changeovers calculate centre of white lines then centre of path
	int Mit;
	int sum = 0;
	int count = 0;
	int average;
	cout<<"findcenter";
	for (int i=0; i<image_thresholded.cols; i++){
		Mit = (image_thresholded.at<uchar>(row, i)) % 2; // had problems with data type of binary image. Modulo works to get either 1 or 0
		cout << Mit << endl;
		if (Mit > 0) {
			//Highlight area where circle is detected
			Point centre;
			centre.x = i;
			centre.y = row;
			circle(image_canny, centre, 5, CV_RGB(250, 100, 255), 1, 8, 0);
			sum = sum + i;
			count++;
		}
	}
	average = sum / count;
	//Put large dot in average of white lines
	Point centre;
	centre.x = average;
	centre.y = row;
	circle(image_canny, centre, 10, CV_RGB(250, 100, 255), 1, 8, 0);
}

int countLines(int row){
	int Mit;
	int lineCount = 0;
	int transitionCount = 0;
	int lastValue = (image_thresholded.at<uchar>(row, 0)) % 2;
	for (int i=0; i<image_thresholded.cols; i++){
			Mit = (image_thresholded.at<uchar>(row, i)) % 2;
			if (Mit != lastValue) {
				transitionCount++;
			}
			lastValue = Mit;
		}
	lineCount = ceil(transitionCount/2.0);
	cout<<"Number of Transitions: "<<transitionCount<<endl;
	cout<<"Number of Lines: "<<lineCount<<endl;
	return lineCount;
}
