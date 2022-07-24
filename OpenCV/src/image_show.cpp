/**
 * image_show.cpp
 * 2022-06-01 K.OHWADA
 */

// g++  image_show.cpp -o image -std=c++11 `pkg-config --cflags --libs opencv4`

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;


/**
 * main
 */
int main(int argc, char **argv) 
{
    char* file = (char *)"images/sample.png";
    char * outfile = (char*)"sample_gray.png";

    if (argc == 2) {
        file = argv[1];
    } else {
       cout << "Usage: " << argv[0] << " <imageFile> " << endl;
    }

    cout << "file: " << file << endl;

  cv::Mat color;

// load as a 3-channel color image
  color = cv::imread(file, 1);

  // // exit the program if the image is not loaded
  if(color.empty()) {
        cerr << "can not read: " << file << endl;
        return 1;
    }

  // create window
const char* WINNAME = (char *)"OpenCV: Image";
  cv::namedWindow(WINNAME, cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);

  // show image
  cv::imshow(WINNAME, color);

  cv::waitKey(0);

// write gray.png
    cv::Mat gray;
    cv::cvtColor(color, gray, cv::COLOR_BGR2GRAY); 
    bool result = cv::imwrite(outfile, gray);


    if (result){
        cout << "saved to: " << outfile << endl;
    } else {
        cerr << "can not save : " << outfile << endl;
    }

    return 0;
}
