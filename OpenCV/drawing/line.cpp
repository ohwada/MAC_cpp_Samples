/**
 *  line.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://cvwww.ee.ous.ac.jp/opencv_practice4/#1.1

#include <opencv2/opencv.hpp>


/**
 *  main
 */
int main(void)
{

// declare an object to store the image
// # CV_8UC3 : 8bit 3channel  full color image
	cv::Mat	image(400, 400, CV_8UC3);

	for (int n = 0; n < 4; n++) {
		int lineType, lineWidth;

		switch (n) {
		case 0:
// draw with line width 1, 8 concatenated
			lineType = cv::LINE_8; lineWidth = 1; break;
		case 1:
// draw with line width 1, 4 concatenated
			lineType = cv::LINE_4; lineWidth = 1; break;
		case 2:
// draw with line width 1, anti-aliasing
			lineType = cv::LINE_AA; lineWidth = 1; break;
		case 3:
// draw with line width 4, anti-aliasing
			lineType = cv::LINE_AA; lineWidth = 4; break;
		}

// fill the image with white
// specify the color with Scalar(Blue, Green, Red). 
// Note that it is in BGR order
		image = cv::Scalar(255, 255, 255);

		for (int i = 0; i < 360; i += 10) {
// start and end coordinates
// # Specify integer coordinates (x,y) with cv::Point. Note that it is an arrangement of (x, y) unlike the matrix Mat

// start coordinates (200,200)
			cv::Point p1(200, 200);

// coordinates of the end point 
			cv::Point p2;

// in the formula below, place every 10 degrees on the circumference
			p2.x = cos(i * CV_PI / 180) * 200 + p1.x + 0.5;
			p2.y = sin(i * CV_PI / 180) * 200 + p1.y + 0.5;

// // raw a line
// // line(image, start point coordinates, end point coordinates, color, line width, connection)
			cv::line(image, p1, p2, cv::Scalar(255, 0, 0), lineWidth, lineType);
		}

		cv::imshow("Image", image);
		cv::waitKey();
	}

	return 0;
}

