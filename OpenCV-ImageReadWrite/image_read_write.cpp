/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */

#include <string> 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "parse_filename.hpp"

using namespace cv;
using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "OpenCV Version: " << CV_VERSION << endl;

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return 1;
    }

    // specify filename from commandline 
    string input = argv[1];

    // create output file name
    string dir;
    string title;
    string ext;
    parseFileName(input, dir, title, ext);

    string output = title + "_gray." + ext;

    //load as color image
    Mat color = imread(input, 1);

    if(color.empty())
    {
        // finish the program, if not load the image
        cerr << "read faild: " << input << endl;
        return 1;
    }

    // convert to black and white
    Mat gray;
    cvtColor(color, gray, COLOR_BGR2GRAY); 

    // save to output file
    imwrite(output, gray);
    cerr << "write to: " << output << endl;

    // show input image
    cv::namedWindow(input, WINDOW_AUTOSIZE|WINDOW_FREERATIO);
    imshow(input, color);
    waitKey(0);

    return 0;
}
