/**
 * OpenCV Sample
 * 2020-01-01 K.OHWADA
 */

#include "histogram_util.hpp"


using namespace cv;
using namespace std;


/**
 * createHistImage
 */
Mat createHistImage(MatND mat, int width, int height, Scalar color)
{

    Mat histImage = Mat::ones(height, width, CV_8UC4)*255;
    histImage = Scalar::all(255);
    int rows = histImage.rows;

    MatND hist(mat.rows, mat.cols, mat.type());
    normalize(mat, hist, 0, rows, NORM_MINMAX, CV_32F);

	vector<float> v;
	hist.copyTo(v); 
    int size = v.size();

    int binW = cvRound((double)histImage.cols/size);

// frame
    int thickness = 1;
    int x[] = {1, (width-1),  (width-1), 1, 1};
    int y[] = {1, 1, (height-1), (height-1), 1};
    for(int i=0; i<4; i++) {
        line( histImage, Point(x[i], y[i]),
                   Point(x[i+1], y[i+1]), BLACK, thickness);
    }

    int index = 0;
	for(vector<float>::iterator it=v.begin(); it!=v.end(); ++it){

		int val = *it;

        float x1= index*binW;
        float x2 = (index+1)*binW;
        index ++;

        float y1 = rows;
        float y2 =  rows - cvRound(val);

        rectangle( histImage, Point(x1, y1),
                   Point(x2, y2), color, -1, 8, 0);

    }

    return histImage;
}



/**
 * matnd2Str
 */
string matnd2Str(MatND mat)
{
	vector<int> v;
	mat.copyTo(v); 

	string COMMA = ", ";

	string data = "";
	for(vector<int>::iterator it=v.begin(); it!=v.end(); ++it){
		int val = *it;
		string str = to_string(val);
     	data += str + COMMA;
	}
     data += LF;

	return data;
}


/**
 * calcHistogram
 */
MatND calcHistogram(Mat src, int ch, int size)
{

    MatND hist;

	int channels[] = {ch};
	int histSize[] = {size};

    calcHist(&src, 1, channels, Mat(), hist, 1, histSize, 0);

    return hist;
}


/**
 * saveHistogram
 */
int saveHistogram(string output, string data)
{

    // open
    ofstream fout; 
    fout.open(output, ios::out); 
    if (fout.fail()){ 
        cerr << "open output file failed: " << output << endl;
        return 1;
    } 

    // write
    fout<< data;
    fout.close();

    cout << "save to: " << output << endl;
    return 0;
}
