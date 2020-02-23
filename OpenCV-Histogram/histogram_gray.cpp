/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 * original : https://github.com/opencv/opencv/blob/master/samples/cpp/demhist.cpp
 */


#include "histogram_util.hpp"

using namespace cv;
using namespace std;


int _brightness = 100;
int _contrast = 100;

Mat image;

string inputImage;

/**
 * createOutputFileName
 */
void createOutputFileName(string input, string &textFile, string &imageFile)
{

    string dir;
    string title;
    string ext;
    parseFileName(input, dir, title, ext);

    string name =  title +  "_gray_hist";

    textFile = name + ".txt";
    imageFile = name + ".png";

}


/* brightness/contrast callback function */
static void updateBrightnessContrast( int /*arg*/, void* )
{

    const int WIDTH = 320;
    const int HEIGHT = 200;

    int histSize = 64;
    int brightness = _brightness - 100;
    int contrast = _contrast - 100;

    /*
     * The algorithm is by Werner D. Streidt
     * (http://visca.com/ffactory/archives/5-99/msg00021.html)
     */
    double a, b;
    if( contrast > 0 )
    {
        double delta = 127.*contrast/100;
        a = 255./(255. - delta*2);
        b = a*(brightness - delta);
    }
    else
    {
        double delta = -128.*contrast/100;
        a = (256.-delta*2)/255.;
        b = a*brightness + delta;
    }

    Mat dst, hist;
    image.convertTo(dst, CV_8U, a, b);
    imshow("image", dst);

    calcHist(&dst, 1, 0, Mat(), hist, 1, &histSize, 0);
    Mat histImage = Mat::ones(HEIGHT, WIDTH, CV_8U)*255;

    //normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);

    //histImage = Scalar::all(255);
    //int binW = cvRound((double)histImage.cols/histSize);

    //for( int i = 0; i < histSize; i++ )
        //rectangle( histImage, Point(i*binW, histImage.rows),
                   //Point((i+1)*binW, histImage.rows - cvRound(hist.at<float>(i))),
                   //Scalar::all(0), -1, 8, 0 );

    histImage = createHistImage(hist, WIDTH, HEIGHT, BLACK);

    string ouputTextFile;
    string outputImageFile;
    createOutputFileName(inputImage, ouputTextFile, outputImageFile);

    string data = matnd2Str(hist);
    saveHistogram(ouputTextFile, data);

    imwrite(outputImageFile, histImage);
    cout << "save to: " << outputImageFile << endl;

    imshow("histogram", histImage);

}

const char* keys =
{
    "{help h||}{@image|baboon.jpg|input image file}"
};


/**
 * main
 */
int main( int argc, const char** argv )
{

    cout << "OpenCV Version: " << CV_VERSION << endl;

    CommandLineParser parser(argc, argv, keys);
    parser.about("\nThis program demonstrates the use of calcHist() -- histogram creation.\n");
    if (parser.has("help"))
    {
        parser.printMessage();
    return EXIT_SUCCESS;
    }

    // string inputImage = parser.get<string>(0);

    inputImage = "./images/baboon.jpg";
    if(argc == 2) {
        inputImage = argv[1];
    }


    // Load the source image. HighGUI use.
    //image = imread(samples::findFile(inputImage), IMREAD_GRAYSCALE);
    image = imread(inputImage, IMREAD_GRAYSCALE);

    if(image.empty())
    {
        std::cerr << "Cannot read image file: " << inputImage << std::endl;
        return EXIT_FAILURE;
    }

    namedWindow("image", 0);
    namedWindow("histogram", 0);

    createTrackbar("brightness", "image", &_brightness, 200, updateBrightnessContrast);
    createTrackbar("contrast", "image", &_contrast, 200, updateBrightnessContrast);


    updateBrightnessContrast(0, 0);
    waitKey();

    cout << "histogram_gray Successfull" << endl;
    return EXIT_SUCCESS;
}

