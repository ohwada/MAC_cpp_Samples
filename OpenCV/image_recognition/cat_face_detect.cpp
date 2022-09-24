/**
 * cat_face_detect.cpp
 * 2022-06-01 K.OHWADA
 */

// CascadeClassifier
// https://docs.opencv.org/3.4/d1/de5/classcv_1_1CascadeClassifier.html
// reference : https://github.com/opencv/opencv/blob/4.x/samples/cpp/facedetect.cpp
// https://qiita.com/niwasawa/items/87feb5f7923bbe2a7e26


#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "parse_filename.hpp"


/**
 * visualize
 */
void visualize(cv::Mat& image, cv::Rect face)
{

// Blue, Green, Red, Alpha
    const cv::Scalar GREEN(0, 255, 0, 255); 

// output the coordinates of the detected face
    std::cout << "Face: " << face << std::endl;

    auto x = face.x;
    auto y = face.y;
    auto width = face.width;
    auto height = face.height;
    auto x2 = x+ width;
    auto y2 = y +height;
    cv::Point p1(x, y);
    cv::Point p2(x2, y2);
    int thickness = 2;

    cv::rectangle(image, p1, p2,  GREEN, thickness);
}


using namespace std;


/**
 * main
 */
int main(int argc, char* argv[]) 
{

const char* WINNAME = (char *)"OpenCV";

  string input_file("images/cat-kowalievska-1170986.jpg");
  string output_file;

  if (argc == 3) {
    input_file  = argv[1];
    output_file = argv[2];
  } else if (argc == 2) {
    input_file  = argv[1];
 } else { 
        cout << "Usage: " << argv[0] << " <imgFile> " << endl;
  }



if( output_file.empty() ) {
    string fname = getFileNameWithoutExt(input_file);
    string ext = getFileNameExt(input_file);
    output_file = fname + string("_out.") + ext; 
}

  cout << input_file  << endl;
  cout << output_file << endl;

  // use IMREAD_UNCHANGED to support with alpha channel
  cv::Mat input_image = cv::imread(input_file, cv::IMREAD_UNCHANGED);


// Preparation for object detection with Haar feature-based cascade classifier
  // use cascade classifier for face detection

  const string FACE_CASCADE_NAME =
    "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";

  cv::CascadeClassifier face_cascade;
  if ( !face_cascade.load(FACE_CASCADE_NAME) ) {
    cerr << "face_cascade.load failed" <<  endl;
            return EXIT_FAILURE;
  };


  // detect face
  std::vector<cv::Rect> faces;
  face_cascade.detectMultiScale(input_image, faces);


  // Object to put the output image data
  // use CV_8UC4 to support with alpha channel
  // CV_<bit-depth>{U|S|F}C(<number_of_channels>)
// CV_8U: bit depth = unsigned 8-bit integer (0-255)
  // C4: number of channels=4
  cv::Mat output_image(input_image.size(), CV_8UC4);

// copy input image data to output image data
  input_image.copyTo(output_image);

  for (size_t i=0; i<faces.size(); i++) 
{
    visualize(output_image, faces[i]);
  } // for

  // create window
  cv::namedWindow(WINNAME, cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);

  // show image
  cv::imshow(WINNAME, output_image);

  cv::waitKey(0);

// output image
  cv::imwrite(output_file, output_image);

cout << "saved: " << output_file << endl;

      return EXIT_SUCCESS;
}

// Face: [175 x 175 from (215, 202)]
// created: lena_out.png
