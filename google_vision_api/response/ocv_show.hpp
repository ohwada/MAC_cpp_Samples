/**
 *  polylines.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://cvwww.ee.ous.ac.jp/opencv_practice4/#1.4

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

// prototype 
bool ocv_show(std::vector<struct faceAnnotation> vec, std::string file_input,  std::string file_output); 
void ocv_show(std::vector<struct faceAnnotation> vec, int width, int height);
void visualize(cv::Mat& image, struct faceAnnotation a);
std::vector<cv::Point> conv_ertices( std::vector<struct vertice> vertices);
std::vector<cv::Point>  get_all_andmark_pos( std::vector<struct landmark> vec);
void wait_key();



/**
 * conv_vertices
 */
std::vector<cv::Point> conv_vertices( std::vector<struct vertice> vec)
{
    std::vector<cv::Point> p;
    for(auto v: vec) {
    int x = v.x;
    int y = v.y;
    // std::cout << "x: " << x << ", y:" << y << std::endl;
	p.push_back(cv::Point(x, y) );
} // for

    return p;
}


/**
 * get_landmark_pos
 */
cv::Point get_landmark_pos( std::vector<struct landmark> vec, std::string name)
{
    cv::Point p;
    for(auto v: vec)
    {
        if( v.type == name ) {
            auto pos = v.pos;
            p.x = (int)pos.x;
            p.y = (int)pos.y;
            return p;
        }
    } // for

    return p;
}

/**
 * get_all_landmark_pos
 */
std::vector<cv::Point>  get_all_andmark_pos( std::vector<struct landmark> vec1)
{
    std::vector<cv::Point> vec2;
    for(auto v: vec1)
    {
        auto pos = v.pos;
        //int x = (int)pos.x;
        //int y = (int)pos.y;
        vec2.push_back( cv::Point(pos.x ,pos.y) );
    } // for

    return vec2;
}


/**
 * visualize
 */
void visualize(cv::Mat& image, struct faceAnnotation a)
{
    const cv::Scalar BLUE(255, 0, 0);
    const cv::Scalar GREEN(0, 255, 0);
    const cv::Scalar RED(0, 0, 255);

// bounding
    auto  p1 = conv_vertices(a.bounding_poly.vertices);
    auto  p2 = conv_vertices(a.fd_bounding_poly.vertices);

// draw a polygon
    bool is_closed = true;
    int thickness = 2;
	cv::polylines(image, p1, is_closed, GREEN, thickness, cv::LINE_AA);
	cv::polylines(image, p2, is_closed, GREEN, thickness, cv::LINE_AA);

// landmark
    auto vec = get_all_andmark_pos(a.landmarks);

// draw circle
    int radius = 3;
    for(auto v: vec){
        cv::circle(image, v, radius, GREEN,  thickness, cv::LINE_AA);
    } // for

}


/**
 * ocv_show
 */
void ocv_show(std::vector<struct faceAnnotation> vec, int width, int height) 
{

// declare an object to store the image
	// # CV_8UC3 : 8bit 3channel full color image
	cv::Mat	 image(width, height, CV_8UC3);
 
// fill the image with white
	image = cv::Scalar(255, 255, 255);
 
for(auto v: vec)
{
    visualize(image, v);
}

	cv::imshow("Image", image);

}


/**
 * ocv_show
 */
bool ocv_show(std::vector<struct faceAnnotation> vec, std::string file_input,  std::string file_output) 
{

const char* WINNAME = (char *)"Google Vision API";

  cv::Mat image = cv::imread(file_input, cv::IMREAD_UNCHANGED);
 
  if(image.empty()) {
        std::cerr << "can not load image: " << file_input << std::endl;
        return false;
    }

    for(auto v: vec)
    {
        visualize(image, v);
    }

	cv::imshow(WINNAME, image);

    cv::imwrite(file_output, image);

    std::cout << "saved: " << file_output << std::endl;

    return true;
}


/**
 * wait_key
 */
void wait_key()
{
	cv::waitKey();
}
