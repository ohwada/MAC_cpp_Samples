/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */



#include <string> 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "parse_filename.hpp"


using namespace std;
using namespace cv;


/**
 * main
 */
int main(int argc, char** argv)
{

    cout << "OpenCV: read write "  << endl;

    cout << "OpenCV Version: " << CV_VERSION << endl;


    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }


    string input = argv[1];


    string fname = getFileNameWithoutExt(input);
    string ext = getFileNameExt(input);
    string output_copy = fname +"_copy." + ext;
    string output_gray = fname +"_gray." + ext;

    string win_name = "imshow: " + fname;


    // load as BGR color
    Mat color = imread(input, IMREAD_COLOR);

    if(color.empty())
    {
        cerr << "read Faild: " << input << endl;
        return 1;
    }

    // convert to black and white
    Mat gray;
    cvtColor(color, gray, COLOR_BGR2GRAY); 

    // save to output file
    bool ret1 = imwrite(output_copy, color);
    if(ret1) {
                cout << "saved: " << output_copy << endl;
    } else {
                cerr << "write Failed: " << output_copy << endl;
    }

    bool ret2 = imwrite(output_gray, gray);
    if(ret2) {
                cout << "saved: " << output_gray << endl;
    } else {
                cerr << "write Failed: " << output_gray << endl;
    }


    // show input image
    cv::namedWindow(win_name, WINDOW_AUTOSIZE|WINDOW_FREERATIO);
    imshow(win_name, color);
    waitKey(0);

	return EXIT_SUCCESS;
}
