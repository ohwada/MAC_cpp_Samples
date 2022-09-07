/**
 *  ellipse.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://cvwww.ee.ous.ac.jp/opencv_practice4/#1.1

#include <opencv2/opencv.hpp>
 

/**
 *  image
 */
int main(void)
{

// declare an object to store the image
// # CV_8UC3 : 8bit 3channel full color image
	cv::Mat	image(400, 400, CV_8UC3);
 

// fill the image with white
	image = cv::Scalar(255, 255, 255);
	
// rotation rectangle
// RotatedRect(center coordinates, size (x, y), rotation angle degree)
	cv::RotatedRect rect1(cv::Point2f( 80, 80), cv::Size(120, 60), 0);
	cv::RotatedRect rect2(cv::Point2f(200, 80), cv::Size(120, 60), 45);
	cv::RotatedRect rect3(cv::Point2f(320, 80), cv::Size(120, 60), -30);
 

// draw an ellipse
// # ellipse(image, RotatedRect, color, line width, join)
	cv::ellipse(image, rect1, cv::Scalar(255, 0, 255), 1, cv::LINE_AA);
	cv::ellipse(image, rect2, cv::Scalar(255, 0, 255), 2, cv::LINE_AA);
	cv::ellipse(image, rect3, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);
 

// draw an arc or sector
// ellipse(image, center coordinates, Size(x diameter, y diameter), ellipse rotation angle, start angle, end angle, color, line width, connection)
	cv::ellipse(image, cv::Point( 80, 200), cv::Size(50, 50), 0, 0, 225, cv::Scalar(255, 200, 0), 1, cv::LINE_AA);
	cv::ellipse(image, cv::Point(200, 200), cv::Size(50, 50), 0, 0, 225, cv::Scalar(255, 200, 0), -1, cv::LINE_AA);
	cv::ellipse(image, cv::Point(320, 200), cv::Size(50, 50), 0, -225, 45, cv::Scalar(255, 200, 0), -1, cv::LINE_AA);
 
	cv::ellipse(image, cv::Point( 80, 320), cv::Size(60, 30),   0,    0, 225, cv::Scalar(0, 180, 255), 1, cv::LINE_AA);
	cv::ellipse(image, cv::Point(200, 320), cv::Size(60, 30),  45,    0, 225, cv::Scalar(0, 180, 255), 2, cv::LINE_AA);
	cv::ellipse(image, cv::Point(320, 320), cv::Size(60, 30), -30, -225,  45, cv::Scalar(0, 180, 255), -1, cv::LINE_AA);
 
 
	cv::imshow("Image", image);
	cv::waitKey();
 
	return 0;
}
