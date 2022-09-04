/**
 * face_detect_dnn.cpp
 * 2022-06-01 K.OHWADA
 */


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
void visualize(Mat& input, int frame, Mat& faces, double fps, int thickness = 2)
{
    std::string fpsString = cv::format("FPS : %.2f", (float)fps);
    if (frame >= 0)
        cout << "Frame " << frame << ", ";
    cout << "FPS: " << fpsString << endl;
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
    }
    putText(input, fpsString, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);
}


/**
 * main
 */
int main(int argc, char** argv)
{

    const char* WINNAME = (char *)"LIve";

    const int VIDEO = 0;

    const float SCORE_THRESHOLD = 0.9;

    const float NMS_THRESHOLD = 0.3;

    const float SCALE = 1.0 ;

    const int TOPK = 5000;

    const bool SAVE = false;

    const string PATH("/usr/local/share/opencv4/dnn/models/");

    const string FD_MODEL_PATH = make_path(PATH, "face_detection_yunet.onnx");

 //! [initialize_FaceDetectorYN]
    // Initialize FaceDetectorYN
    Ptr<FaceDetectorYN> detector = FaceDetectorYN::create(FD_MODEL_PATH, "", Size(320, 320), SCORE_THRESHOLD, NMS_THRESHOLD, TOPK);
    //! [initialize_FaceDetectorYN]


    TickMeter tm;

    int frameWidth, frameHeight;

    VideoCapture capture;
    capture.open(0);

    if (capture.isOpened())
        {
            frameWidth = int(capture.get(CAP_PROP_FRAME_WIDTH) * SCALE);
            frameHeight = int(capture.get(CAP_PROP_FRAME_HEIGHT) * SCALE);
            cout << "Video " << VIDEO
                << ": width=" << frameWidth
                << ", height=" << frameHeight
                << endl;
        }
        else
        {
            cout << "Could not initialize video capturing: " << VIDEO << endl;
            return EXIT_FAILURE;
        }

    detector->setInputSize(Size(frameWidth, frameHeight));

        cout << "Press 'SPACE' to save frame, any other key to exit..." << endl;
        int nFrame = 0;
        while(1)
        {
            // Get frame
            Mat frame;
            if (!capture.read(frame))
            {
                cerr << "Can't grab frame! Stop\n";
                break;
            }

            resize(frame, frame, Size(frameWidth, frameHeight));

            // Inference
            Mat faces;
            tm.start();
            detector->detect(frame, faces);
            tm.stop();

            Mat result = frame.clone();
            // Draw results on the input image
            visualize(result, nFrame, faces, tm.getFPS());

            // Visualize results
            imshow(WINNAME, result);

            int key = waitKey(1);
            bool saveFrame = SAVE;

            if (key == ' ')
            {
                saveFrame = true;
                key = 0;  // handled
            }

            if (saveFrame)
            {
                std::string frame_name = cv::format("frame_%05d.png", nFrame);
                std::string result_name = cv::format("result_%05d.jpg", nFrame);
                cout << "Saving '" << frame_name << "' and '" << result_name << "' ...\n";
                imwrite(frame_name, frame);
                imwrite(result_name, result);
            }

            ++nFrame;

            if (key > 0){
                break;
            }
        } // while

        cout << "Processed " << nFrame << " frames" << endl;


          return EXIT_SUCCESS;
}
