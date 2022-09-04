/**
 * face_detect_cascade.cpp
 * 2022-06-01 K.OHWADA
 */

// CascadeClassifier
// https://docs.opencv.org/3.4/d1/de5/classcv_1_1CascadeClassifier.html
// reference : https://qiita.com/niwasawa/items/87feb5f7923bbe2a7e26


#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[]) 
{

const char* WINNAME = (char *)"OpenCV";

  string input_file("images/lena.png");
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
    "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml";

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
// output the coordinates of the detected face
    cout << "Face: " << faces[i] << endl;

// Draw an ellipse at the face position
    cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
    cv::Size size(faces[i].width / 2, faces[i].height / 2);

// Blue, Green, Red, Alpha
    const cv::Scalar COLOR(255, 0, 255, 255); 

    const double ANGLE = 0;
    const double START_ANGLE = 0;
    const double END_ANGLE = 360;
    const int THICKNESS = 4;

    cv::ellipse(output_image, center, size, ANGLE, START_ANGLE, END_ANGLE, COLOR, THICKNESS);
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
