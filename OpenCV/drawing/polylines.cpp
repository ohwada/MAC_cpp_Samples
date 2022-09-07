/**
 *  polylines.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://cvwww.ee.ous.ac.jp/opencv_practice4/#1.4
#include <opencv2/opencv.hpp>
 
using namespace std;
 

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
 
// set the vertices of the polygon
	vector<cv::Point> p;
	int n = 5;
	for (int i = 0; i < n; i++) {
		p.push_back(cv::Point(cos(CV_PI * (2.0*i/n - 0.5)) * 180 + 200, sin(CV_PI * (2.0*i/n - 0.5)) * 180 + 200));
	}
 
// draw a polygon
// polylines(image, vertex set, close polygon, color, line width, connect)
	cv::polylines(image, p, true, cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
 
	p.clear();
	for (int i = 0; i < n; i++) {
		p.push_back(cv::Point(cos(CV_PI * (2.0*i/n - 0.5)) * 140 + 200, sin(CV_PI * (2.0*i/n - 0.5)) * 140 + 200));
	}
 
// draw a filled polygon
// fillConvexPoly(image, vertex set, color, concatenation)
	cv::fillConvexPoly(image, p, cv::Scalar(0, 0, 255), cv::LINE_AA);
 
	// // when using fillPoly:
	//  vector<vector<cv::Point>> pp;
	//  pp.push_back(p);
	//  cv::fillPoly(image, pp, cv::Scalar(0, 0, 255), cv::LINE_AA);
 
	cv::imshow("Image", image);
	cv::waitKey();
 
// draw multiple polygons at once
 
	// set the vertices of the polygon
	vector<vector<cv::Point>> ps(16);
	for (int n = 0; n < 16; n++) {
		cv::Point p0((n % 4) * 100 + 50, (n / 4) * 100 + 50);
		for (int i = 0; i < n + 3; i++) {
			cv::Point pa(cos(CV_PI * (2.0*i/(n+3) - 0.5)) * 40, sin(CV_PI * (2.0*i/(n+3) - 0.5)) * 40);
			ps[n].push_back(p0 + pa);
		}
	}
 
	image = cv::Scalar(255, 255, 255);
 
// draw a polygon
	cv::fillPoly(image, ps, cv::Scalar(0, 255, 255), cv::LINE_AA);


// polygon filled with yellow
// black line polygon
	cv::polylines(image, ps, true, cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
 
	cv::imshow("Image", image);
	cv::waitKey();
	
	return 0;
}

