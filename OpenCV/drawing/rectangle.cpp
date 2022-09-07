/**
 *  rectangle.cpp
 * 2022-06-01 K.OHWADA
 */

// draw rectangles and circles
// reference : http://cvwww.ee.ous.ac.jp/opencv_practice4/#1.1

#include <opencv2/opencv.hpp>
 

/**
 *  main
 */
int main(void)
{
// declare an object to store the image
	// # CV_8UC3 : 8bit 3channel full color image
	cv::Mat	image(400, 400, CV_8UC3);
 

// fill the image with white
	image = cv::Scalar(255, 255, 255);
 
// draw a rectangle 1
// rectangle(image, vertex 1, vertex 2, color, width, concatenation)
// draw a straight rectangle with vertices 1 and 2 as diagonals
	cv::Point p1(10, 10), p2(190, 90);
	cv::rectangle(image, p1, p2, cv::Scalar(255, 0, 0), 1, cv::LINE_4);
 
// draw a rectangle 2
// rectangle(image, rectangle, color, width, concatenation)
// draw a straight rectangle based on cv::Rect(start point x, start point y, width, height)
	cv::Rect rect(210, 10, 180, 80);
	cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 1, cv::LINE_4);
 
	for (int i = 0; i < 13; i++) {
		cv::Rect rect(i * 30 + 10, 100, 20, 80);

// # fill inside rectangle if line width < 0
		cv::rectangle(image, rect, cv::Scalar(255 - i * 20, 0, i * 20 + 15), -1, cv::LINE_4);
	}
	
	for (int i = 1; i < 7; i++) {
// draw a perfect circle
// circle(image, center coordinates, radius, color, line width, connection)
		cv::circle(image, cv::Point(i * i * 9 + 10, 250), i * 9 - 1, cv::Scalar(0, 200, 0), 1, cv::LINE_AA);

// fill inside the circle if line width < 0
		cv::circle(image, cv::Point(384 - i * i * 9, 340), i * 9 - 1, cv::Scalar(0, 200, 0), -1, cv::LINE_AA);
	}
	
	cv::imshow("Image", image);
	cv::waitKey();
 
	return 0;
}
