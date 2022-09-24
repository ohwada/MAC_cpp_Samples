/**
 * face_detect_smile.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/opencv/opencv/blob/4.x/samples/cpp/smiledetect.cpp

#include <iostream>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "parse_filename.hpp"

using namespace std;
using namespace cv;

// prototype
void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip, string output_file );



/**
 * main
 */
int main( int argc, const char** argv )
{

  string input_file("images/dlib_bald_guys.jpg");
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
    output_file = fname + string("_smile.") + ext; 
}

  cout << input_file  << endl;
  cout << output_file << endl;


  const string CASCADE_NAME =
    "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml";

  const string NESTED_NAME =
    "/usr/local/share/opencv4/haarcascades/haarcascade_smile.xml";

    CascadeClassifier cascade, nestedCascade;

    if( !cascade.load( CASCADE_NAME ) )
    {
        cerr << "ERROR: Could not load face cascade: " << CASCADE_NAME << endl;
        return EXIT_FAILURE;
    }

    if( !nestedCascade.load( NESTED_NAME ) )
    {
        cerr << "ERROR: Could not load smile cascade: " << NESTED_NAME << endl;
        return EXIT_FAILURE;
    }

    cv::Mat input_image = cv::imread(input_file, cv::IMREAD_UNCHANGED);
        if (input_image.empty())
        {
            std::cerr << "Cannot read image: " << input_file << std:: endl;
            return EXIT_FAILURE;
        }

    double scale = 1;
    bool tryflip = false;

    detectAndDraw(  input_image, cascade,
                    nestedCascade,
                    scale, tryflip, output_file);

    cout << "saved: " << output_file << endl;

    return EXIT_SUCCESS;
}


/**
 * detectAndDraw
 */
void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip, string output_file)
{
    vector<Rect> faces, faces2;
    const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    };

    const Scalar BLUE(255,0,0);
    const Scalar RED(0,0,255);
    const Scalar GREEN(0,255, 0);
    const Scalar AQUA(255,255, 0);
    const Scalar PINK(198,198, 255);

    Mat gray, smallImg;

    cvtColor( img, gray, COLOR_BGR2GRAY );

    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(30, 30) );
    if( tryflip )
    {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale( smallImg, faces2,
                                 1.1, 2, 0
                                 //|CASCADE_FIND_BIGGEST_OBJECT
                                 //|CASCADE_DO_ROUGH_SEARCH
                                 |CASCADE_SCALE_IMAGE,
                                 Size(30, 30) );
        for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r )
        {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;


            rectangle( img, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                       Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                       GREEN, 3, 8, 0);

        const int half_height=cvRound((float)r.height/2);
        r.y=r.y + half_height;
        r.height = half_height-1;
        smallImgROI = smallImg( r );
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
            1.1, 0, 0
            //|CASCADE_FIND_BIGGEST_OBJECT
            //|CASCADE_DO_ROUGH_SEARCH
            //|CASCADE_DO_CANNY_PRUNING
            |CASCADE_SCALE_IMAGE,
            Size(30, 30) );

        // The number of detected neighbors depends on image size (and also illumination, etc.). The
        // following steps use a floating minimum and maximum of neighbors. Intensity thus estimated will be
        //accurate only after a first smile has been displayed by the user.
        const int smile_neighbors = (int)nestedObjects.size();
        static int max_neighbors=-1;
        static int min_neighbors=-1;
        if (min_neighbors == -1) min_neighbors = smile_neighbors;
        max_neighbors = MAX(max_neighbors, smile_neighbors);

        // Draw rectangle on the left side of the image reflecting smile intensity
        float intensityZeroOne = ((float)smile_neighbors - min_neighbors) / (max_neighbors - min_neighbors + 1);

std::cout << intensityZeroOne << std::endl;

        // int rect_height = cvRound((float)img.rows * intensityZeroOne);

Scalar col;


// change color with intensity
// Red strong, Blue weak
 if( intensityZeroOne < 0.1){
        col = BLUE;
 } else if( intensityZeroOne < 0.2){
        col = AQUA;
 } else if( intensityZeroOne < 0.3){
        col = PINK;
} else {
        float red = (float)255 * intensityZeroOne;
        col = Scalar(0, 0, red);
}

        center.x = cvRound((r.x + r.width*0.5)*scale);
        center.y = cvRound((r.y + r.height*0.5)*scale);
        radius = cvRound((r.width + r.height)*0.25*scale);
        circle( img, center, radius, col, 3, 8, 0 );

    } // for

// output image
  cv::imwrite(output_file, img);

    imshow( "result", img );

  cv::waitKey(0);
}
