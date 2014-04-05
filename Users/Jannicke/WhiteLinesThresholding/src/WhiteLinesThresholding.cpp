#include <stdio.h>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

//Include Libraries 
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;



Mat image, image_gray,filter, thresholded, canny, detected_lines, birds;
int threshold_value = 140;
int const max_threshold = 255;
int blur_value=21;
int const max_blur = 200;
int const max_BINARY_value = 255;
int llowThreshold = 760;
int max_llowThreshold = 120;
string window_name = "Threshold Demo";
string trackbar_blur = "Blur";
string trackbar_threshold = "Value";
  
//Mat ones(3, 3, CV_32F);
Mat ones( 2, 4, CV_32FC1 );

// Function Declarations
void Threshold_Demo( int, void* );
void Blur_Demo(int, void*);
void drawlines(int, void*);

int main( int argc, char** argv )
{

	// Input Quadilateral or Image plane coordinates
	    Point2f inputQuad[4];
	    // Output Quadilateral or World plane coordinates
	    Point2f outputQuad[4];
  //Read Image
  image = imread( argv[1], 1 );
  thresholded = image;
  birds = image;

  //Create image_gray a grayscaled version of image
   cvtColor( image, image_gray, CV_RGB2GRAY );
   
  //Warning if no data
  if( argc != 2 || !image.data )
    {
      printf( "No image data \n" );
      return -1;
    }
  ones = Mat::zeros( image.rows, image.cols, image.type() );
  //Display image                  
  namedWindow( "Display Image", CV_WINDOW_NORMAL );
  imshow( "Display Image", image );

  //Display gray image  
  namedWindow(window_name, CV_WINDOW_NORMAL );
  imshow( window_name, image_gray );
  
  //Display canny image
  namedWindow("Canny", CV_WINDOW_NORMAL );
  imshow("Canny",image_gray );

  //Display line image  
  namedWindow("Lines", CV_WINDOW_NORMAL );
  imshow( "Lines", image );

// Display Bird's Eye Image
  namedWindow("Bird's eye", CV_WINDOW_NORMAL );
  imshow( "Bird's eye", birds );

  // Two track bars one for threshold and one for blur
  createTrackbar( trackbar_blur, window_name, &blur_value, max_blur, Blur_Demo );
  createTrackbar( trackbar_threshold, window_name, &threshold_value, max_threshold, Threshold_Demo );
  createTrackbar( "Line Threshold:", "Lines", &llowThreshold, max_llowThreshold, drawlines );

  // The 4 points that select quadilateral on the input , from top-left in clockwise order
      // These four pts are the sides of the rect box used as input
      inputQuad[0] = Point2f( -30,-60 );
      inputQuad[1] = Point2f( image.cols+50,-50);
      inputQuad[2] = Point2f( image.cols+100,image.rows+50);
      inputQuad[3] = Point2f( -50,image.rows+50  );
      // The 4 points where the mapping is to be done , from top-left in clockwise order
      outputQuad[0] = Point2f( 0,0 );
      outputQuad[1] = Point2f( image.cols-1,0);
      outputQuad[2] = Point2f( image.cols-1,image.rows-1);
      outputQuad[3] = Point2f( 0,image.rows-1  );

      ones = getPerspectiveTransform( inputQuad, outputQuad );
      std::cout << "Start" ;
      warpPerspective(image, birds, ones, ones.size());

      //warpPerspective(image,birds,ones,birds.size());
  //perspectiveTransform(&image,birds,&ones);
		  //CV_INTER_LINEAR);
  // Wait until user presses a key
  waitKey(0);
  return 0;
}

// Update thresholds for image
void Threshold_Demo( int, void* )
{
  if(blur_value%2 == 0)
  {
  	blur_value= blur_value+1;
  }
  medianBlur( image_gray, filter, blur_value);
  threshold( filter, thresholded, threshold_value, max_BINARY_value, THRESH_BINARY);
  // adaptiveThreshold(filter, thresholded, threshold_value, ADAPTIVE_THRESH_GAUSSIAN_C,  THRESH_BINARY, 13,0);
  imshow( window_name, thresholded );
}


void Blur_Demo( int, void* )
{
    if(blur_value%2==0)
  {
  	blur_value = blur_value+1;
  }
// getGaussianKernel(image_gray);
  medianBlur( image_gray, filter, blur_value);
  threshold( filter, thresholded, threshold_value, max_BINARY_value, THRESH_BINARY);
 //adaptiveThreshold(filter, thresholded, threshold_value, ADAPTIVE_THRESH_GAUSSIAN_C,  THRESH_BINARY, 13,0);
  imshow( window_name, thresholded );
}

//Draw detected lines
void drawlines(int,void*)
{
	    vector<Vec2f> lines;
	    Canny(thresholded, canny, 50, 200, 3);
	    HoughLines(canny, lines, 1, CV_PI/180, llowThreshold, 0, 0 ); // not sure what last two variables really do
	    detected_lines = image;
	    for( size_t i = 0; i < lines.size(); i++ )
	    {
	       float rho = lines[i][0], theta = lines[i][1];
	       Point pt1, pt2;
	       double a = cos(theta), b = sin(theta);
	       double x0 = a*rho, y0 = b*rho;
	       pt1.x = cvRound(x0 + 1000*(-b));
	       pt1.y = cvRound(y0 + 1000*(a));
	       pt2.x = cvRound(x0 - 1000*(-b));
	       pt2.y = cvRound(y0 - 1000*(a));
	       line(detected_lines, pt1, pt2, Scalar(0,250,255), 3, CV_AA);
	    }
	   warpPerspective(image, birds, ones, image.size());
	   imshow( "Bird's eye", birds );
	   imshow("Lines", detected_lines);
	   imshow( "Canny", canny);
}
