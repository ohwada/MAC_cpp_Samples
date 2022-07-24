/**
 * video_capture.cpp
 * 2022-06-01 K.OHWADA
 */

// capture video from the built-in camera

// g++ video_capture.cpp -o capture -std=c++11 `pkg-config --cflags --libs opencv4`

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// prototype
void drawText(Mat & image);


/**
 * main
 */
int main()
{

const char* WINNAME = (char *)"OpenCV: VideoCapture";

    Mat image;
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        while(1)
        {
            capture >> image;
            if(image.empty()){
                break;
            }
            drawText(image);
            imshow(WINNAME, image);
            if(waitKey(10) >= 0){
                break;
            }
        }
    }
    else
    {
        cout << "No capture" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        drawText(image);
        imshow("Sample", image);
        waitKey(0);
    }

    return 0;
}


/**
 * drawText
 */
void drawText(Mat & image)
{
    putText(image, "Hello OpenCV",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // font face and scale
            Scalar(255, 255, 255), // white
            1, LINE_AA); // line thickness and type
}
