/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */

#include "histogram_util.hpp"

using namespace cv;
using namespace std;


/**
 * createHistImageRGB
 */
    Mat createHistImageRGB(MatND histRed, MatND histGreen, MatND histBlue, int sub_width, int sub_height, string title)
{

    const int TITLE_HEIGHT = 34;
    const int SPACE_HEIGHT = 2;


    // create RGB hist image
    Mat imageRed = createHistImage(histRed, sub_width, sub_height, RED);
    Mat imageGreen = createHistImage(histGreen, sub_width, sub_height, GREEN);
    Mat imageBlue = createHistImage(histBlue, sub_width, sub_height, BLUE);


    // create Canvas image
    int height = 3*(sub_height + SPACE_HEIGHT) + TITLE_HEIGHT;
    Mat histImage = Mat::ones(height, sub_width, CV_8UC4)*255;
    histImage = Scalar::all(255);

    // get title RGB histgram position in Canvas
    Rect rectRed(0, TITLE_HEIGHT, sub_width, sub_height);
    Rect rectGreen(0, (sub_height + SPACE_HEIGHT + TITLE_HEIGHT), sub_width, sub_height);
    Rect rectBlue(0, (2*(sub_height + SPACE_HEIGHT) + TITLE_HEIGHT), sub_width, sub_height);

    // copy RGB histgram
	imageRed.copyTo(histImage(rectRed));
	imageGreen.copyTo(histImage(rectGreen));
	imageBlue.copyTo(histImage(rectBlue));

    // calc title param
    double fontScale = 1.0;
    int thickness = 2;
    int baseline=0;
    Size textSize = getTextSize(title, FONT_HERSHEY_SIMPLEX, fontScale, thickness, &baseline);

    // draw title
    int xt = (histImage.cols - textSize.width)/2;
    int yt = textSize.height + 1;
    putText(histImage, title, Point(xt, yt), FONT_HERSHEY_SIMPLEX, fontScale, BLACK, thickness, 8);

    return histImage;

}


/**
 * histgram_color
 */
int histgram_color(Mat src, string ouputTextFile, string imageTitle, int histSize, Mat &histImage)
{

    const int SUB_WIDTH = 640;
    const int SUB_HEIGHT = 200;


    MatND histRed = calcHistogram(src, 0, histSize);
    MatND histGreen = calcHistogram(src, 1, histSize);
    MatND histBlue = calcHistogram( src, 2, histSize);

    string data = matnd2Str(histRed) + matnd2Str(histGreen) + matnd2Str(histBlue);
    saveHistogram(ouputTextFile, data);

    histImage = createHistImageRGB(histRed, histGreen, histBlue, SUB_WIDTH, SUB_HEIGHT, imageTitle);

    return EXIT_SUCCESS;

}


/**
 * createOutputFileName
 */
void createOutputFileName(string input, int histSize, string &textFile, string &imageFile, string &imageTitle)
{

    string dir;
    string title;
    string ext;
    parseFileName(input, dir, title, ext);

    string str_size = to_string(histSize);

    string name =  title + UNDERBAR + str_size + "_hist";

    textFile = name + ".txt";
    imageFile = name + ".png";
    imageTitle = "Histgram: " + title+ " (" + str_size + ")";

}


/**
 * main
 */
int main( int argc, char** argv)
{

    cout << "OpenCV Version: " << CV_VERSION << endl;

    string input;
    int histSize = 256;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> [histSize] "  << endl;
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        input = argv[1];
    }

    if (argc == 3) {
        input = argv[1];
        histSize = atoi(argv[2]);
    }

    string textFile;
    string imageFile;
    string imageTitle;
    createOutputFileName(input, histSize, textFile, imageFile, imageTitle);

    // read image as color
    Mat src = imread( input, IMREAD_COLOR);

    if(!src.data ) {
        cerr << "imread faild: " << input << endl;
        return EXIT_FAILURE;
    }


    Mat histImage;
    histgram_color(src, textFile, imageTitle, histSize, histImage);

    imwrite(imageFile, histImage);
    cout << "save to: " << imageFile << endl;

    Mat img;
    //Mat img(histImage.rows, histImage.cols, histImage.type());

    resize(histImage, img, cv::Size(), 0.5, 0.5);

    namedWindow("image", 0);
    namedWindow("histogram", 0);

    imshow("image", src);
    imshow("histogram", img);
    waitKey(0);

    cout << "histogram_color Successfull" << endl;
    return EXIT_SUCCESS;

}
