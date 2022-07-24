/**
 * video_shoe.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ video_show.cpp -o video -std=c++11 `pkg-config --cflags --libs opencv4`

// reference : https://code-database.com/knowledges/96

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;


/**
 * main
 */
int main(int argc, char **argv) 
{
    char* file = (char *)"videos/Mountain.mp4";
    char* outfile = (char *)"CloneMountain.mp4";

    if (argc == 2) {
        file = argv[1];
    } else {
       cout << "Usage: " << argv[0] << " <videoFile> " << endl;
    }

	cv::VideoCapture video;

	// open video fie
	video.open(file);

// exit if the video file cannot be opened
	if (video.isOpened() == false) {
         cerr << "can not open: " << file << endl;
		return 1;
	}

	cv::VideoWriter writer;

// specify the video format
// ISO MPEG-4 / .mp4
   int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');


// get frame width
	int width  = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);


// get the frame height
	int height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);	

// get frame rate
	double  fps = video.get(cv::CAP_PROP_FPS);


	writer.open(outfile, fourcc, fps, cv::Size(width, height));

    cv::Mat image ;

const char* WINNAME = (char *)"OpenCV: Video";

	while (1) 
{

	// capture one frame from video to image
		video >> image;


// exit the endless loop when the image cannot be loaded
	if (image.empty() == true) {
			break; 	
	}


// display the video in the window
	cv::imshow(WINNAME, image);


// // export image image to video file
		writer << image;

		// press q to finish
		if (cv::waitKey(1) == 'q') {
			break;
		}
} // while

	return 0;
}

