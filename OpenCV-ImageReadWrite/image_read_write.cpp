/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */

#include <string> 
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

/**
 * parseFileName
 */
bool parseFileName(string name, string &title, string &ext)
{
    size_t pos = name.find('.');
    if(pos == string::npos){
        return false;
    }

    title = name.substr(0, pos);
    ext = name.substr(pos+1, name.size()-pos);
    return true;
}


/**
 * main
 */
int main(int argc, char** argv)
{

    cv::CommandLineParser parser(argc, argv,
        "{input|vegetables.jpg|input file}"
    );

    // get input filename
    std::string input;
    if (parser.has("input"))
    {
        input = parser.get<string>("input");
    }

    // create output file name
    string title;
    string ext;
    parseFileName(input, title, ext);

    string output = title + "_gray." + ext;

    //load as color image
    Mat color = imread(input, 1);


    if(color.empty())
    {
        // finish the program, if not load the image
        return 1;
    }

    // convert to black and white
    Mat gray;
    cvtColor(color, gray, COLOR_BGR2GRAY); 

    // save to output file
    imwrite(output, gray);

    // show input image
    cv::namedWindow(input, WINDOW_AUTOSIZE|WINDOW_FREERATIO);
    imshow(input, color);
    waitKey(0);

    return 0;
}
