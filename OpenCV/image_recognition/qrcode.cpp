/**
 * qrcode.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/opencv/opencv/blob/4.x/samples/cpp/qrcode.cpp
// https://rest-term.com/archives/3491/

#include <iostream>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "parse_filename.hpp"


/**
 * calc_qr_version
 */
int calc_qr_version(  cv::Mat straight_qrcode )
{ 
// calculate the QR code version
    return ((straight_qrcode.rows - 21) / 4) + 1 ;
}

    using namespace std;


/**
 * main
 */
int main(int argc, char **argv) 
{

   string input_file("images/qr_example.png");
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

    const cv::Mat input_image = cv::imread(input_file, cv::IMREAD_COLOR);

    cv::Mat output_image = input_image.clone();
    vector<cv::Point> points;
    cv::Mat straight_qrcode;

// QR code detector
    cv::QRCodeDetector detector;

// QR code detection and decoding (decoding)
    const string data = detector.detectAndDecode(input_image, points, straight_qrcode);

    if(data.length() > 0) {
    
// output decording information 
        cout << "decoded data: " << data << endl;

const cv::Scalar RED(0, 0, 255);
auto size = points.size();
// draw rectangle of detection result
        for(size_t i = 0; i < size; ++i) {
            int j = (i + 1) % size;
            cv::line(output_image, points[i], points[j], RED, 4);
        } // for

        cv::imwrite(output_file, output_image);

    // // QR code version
        cout << "QR code version: " <<  calc_qr_version(straight_qrcode) << endl;
    } else {
        cout << "QR code not detected" << endl;
    }

        cout << "created " << output_file << endl;

      return EXIT_SUCCESS;
}
