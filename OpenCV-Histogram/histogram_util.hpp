/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */


#include <stdio.h>
#include <stdlib.h>
#include <string> 
#include <vector> 
#include <iostream>


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "parse_filename.hpp"





const char LF = '\n';
const char UNDERBAR = '_';

const    cv::Scalar RED(0, 0, 255, 255);
const    cv::Scalar GREEN(0, 255, 0, 255);
const    cv::Scalar BLUE(255, 0, 0, 255);
const    cv::Scalar BLACK(0, 0, 0, 0);


cv::Mat createHistImage(cv::MatND mat, int width, int height, cv::Scalar color);

std::string matnd2Str(cv::MatND mat);

cv::MatND calcHistogram(cv::Mat src, int ch, int num_bins);

int saveHistogram(std::string output, std::string data);

