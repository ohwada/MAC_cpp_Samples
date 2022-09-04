/**
 * face_detect_dnn.cpp
 * 2022-06-01 K.OHWADA
 */

// DNN-based Face Detection And Recognition
// https://docs.opencv.org/4.x/d0/dd4/tutorial_dnn_face.html

// reference : https://github.com/opencv/opencv/blob/4.x/samples/dnn/face_detect.cpp

#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "file_util.hpp"
#include "parse_filename.hpp"

using namespace cv;
using namespace std;


/**
 * visualize
 */
static
void visualize(Mat& input, Mat& faces, int thickness = 2)
{
    for (int i = 0; i < faces.rows; i++)
    {
        // Print results
        cout << "Face " << i
             << ", top-left coordinates: (" << faces.at<float>(i, 0) << ", " << faces.at<float>(i, 1) << "), "
             << "box width: " << faces.at<float>(i, 2)  << ", box height: " << faces.at<float>(i, 3) << ", "
             << "score: " << cv::format("%.2f", faces.at<float>(i, 14))
             << endl;

        // Draw bounding box
        rectangle(input, Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), Scalar(0, 255, 0), thickness);
        // Draw landmarks
        circle(input, Point2i(int(faces.at<float>(i, 4)), int(faces.at<float>(i, 5))), 2, Scalar(255, 0, 0), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 6)), int(faces.at<float>(i, 7))), 2, Scalar(0, 0, 255), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 8)), int(faces.at<float>(i, 9))), 2, Scalar(0, 255, 0), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 2, Scalar(255, 0, 255), thickness);
        circle(input, Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 2, Scalar(0, 255, 255), thickness);
    } // for

    // putText(input, fpsString, Point(0, 15), 
   // FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
}


/**
 * main
 */
int main(int argc, char** argv)
{
    const char* WINNAME = (char *)"OpenCV dnn";

string input_file("images/faces1.jpg");
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

    const string PATH("/usr/local/share/opencv4/dnn/models/");

    const string FD_MODEL_PATH = make_path(PATH, "face_detection_yunet.onnx");

  const float SCORE_THRESHOLD = 0.9;

    const float NMS_THRESHOLD = 0.3;

    const float SCALE = 1.0 ;

      const int TOPK = 5000;

    //! [initialize_FaceDetectorYN]
    // Initialize FaceDetectorYN
    Ptr<FaceDetectorYN> detector = FaceDetectorYN::create(FD_MODEL_PATH, "", Size(320, 320), SCORE_THRESHOLD, NMS_THRESHOLD, TOPK);
    //! [initialize_FaceDetectorYN]


        Mat image = imread(samples::findFile(input_file));
        if (image.empty())
        {
            cerr << "Cannot read image: " << input_file << endl;
            return EXIT_FAILURE;

        }

        int imageWidth = int(image.cols * SCALE);
        int imageHeight = int(image.rows * SCALE);
        resize(image, image, Size(imageWidth, imageHeight));


        // Set input size before inference
        detector->setInputSize(image.size());

        Mat faces;
        detector->detect(image, faces);
        if (faces.rows < 1)
        {
            cerr << "Cannot find a face in " << input_file << endl;
            return EXIT_FAILURE;
        }

        // Draw results on the input image
        visualize(image, faces);

  // create window
  cv::namedWindow(WINNAME, cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);

       // Visualize results
        imshow(WINNAME, image);

        cv::waitKey(0);

        imwrite( output_file, image);
    
    cout << "saved: " << output_file << endl;

          return EXIT_SUCCESS;
}
