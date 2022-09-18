/**
 * face_detect_frontal.cpp
 * 2022-06-01 K.OHWADA
 */

// frontal_face_detector 
// hog + svm
// reference : https://kivantium.hateblo.jp/entry/2015/04/05/223841
// https://nhancv.medium.com/install-dlib-on-macos-946dc53f7d7e


#include <iostream>
#include <chrono>
#include <cstring>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_io.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "parse_filename.hpp"


/**
 * visualize
 */
void visualize(cv::Mat& image,  dlib::rectangle face, 
double scale_width, double scale_height)
{
    const cv::Scalar GREEN(0, 255, 0);
    int thickness = 2;

    int x1 = (int) (face.left() * scale_width );
    int y1 = (int) (face.top() * scale_height );
    int x2 = (int) (face.right()  * scale_width);
    int y2 = (int) (face.bottom() * scale_height );

    std::cout << "x1 " << x1 << std::endl;
    std::cout << "x2 " << x2 << std::endl;
    std::cout << "y1 " << y1 << std::endl;
    std::cout << "y2 " << y2 << std::endl;

    cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, thickness);
}


/**
 * ocv_draw
 */
bool ocv_draw(std::string input_file,  std::string output_file,    std::vector<dlib::rectangle> faces, int face_width, int face_height)
{
    const char* WINNAME = (char *)"dlib face detect";

    // load image in fullu color
    cv::Mat image;
    image = cv::imread(input_file, cv::IMREAD_UNCHANGED);

        if (image.empty())
        {
            std::cerr << "Cannot read image: " << input_file << std:: endl;
            return false;
        }

        int width = image.cols;
        int height = image.rows;

        // std::cout << "width " << width << std::endl;
        // std::cout << "height " << height << std::endl;

        double scale_width = 
        (double)width / (double)face_width;
        double scale_height = 
        (double)height / (double)face_height;

        // std::cout << "scale_width " << scale_width << std::endl;
        // std::cout << "scale_height " << scale_height << std::endl;

    for (int i = 0; i < faces.size(); i++) 
    {
        visualize(image,  faces[i], scale_width,  scale_height);
    } // for

// output image
    cv::imwrite(output_file, image);

    cv::imshow(WINNAME, image);

    return true;
}


/**
 *  dlib_face_detect
 */
bool dlib_face_detect(std::string file, bool is_pyramid, std::vector<dlib::rectangle> &faces,  int &width,   int &height)
{

    try{
    // load face detector
        dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
   
    // load image in grayscale
            dlib::array2d<unsigned char> img;
            dlib::load_image(img, file);

        // dlib::save_png(img, "out.png");

    // upsample the image we make the detector run slower since it must
    // process a larger image.
        if(is_pyramid){
            pyramid_up(img);
        }

        width = img.nc();
        height = img.nr();
   
        std::cout << "width " << width << std::endl;
        std::cout << "height " << height << std::endl;


  //
// get face rectangle
        faces = detector(img);

        std::cout << "size " << faces.size() << std::endl;

    }
    catch ( std::exception& e){
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}


/**
 * print_elapsed_time
 */
template< class CLOCK >
void print_elapsed_time(std::chrono::time_point<CLOCK> start)
{
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "  elapsed time: " << elapsed / 1000.0 << " sec." << std::endl;
}


using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{

    string input_file("images/lena.png");

    bool is_pyramid = false;

    if (argc == 3) {
        input_file  = argv[1];
         is_pyramid = (bool)std::stoi(argv[2]);
    } else if (argc == 2) {
        input_file  = argv[1];
    } else { 
        cout << "Usage: " << argv[0] << " <imgFile> " << endl;
  }


 
    string fname = getFileNameWithoutExt(input_file);
    string ext = getFileNameExt(input_file);
    string output_file = fname + string("_out.") + ext; 


  cout << input_file  << endl;
  cout << output_file << endl;
  cout << boolalpha <<   "is_pyramid: " <<  is_pyramid << endl;

    std::vector<dlib::rectangle> faces;
    int width;
   int height;

    auto start = std::chrono::high_resolution_clock::now();

    dlib_face_detect(input_file, is_pyramid,  faces,  width,   height);

    print_elapsed_time(start);

    ocv_draw(input_file,  output_file, faces, width,   height);

    cv::waitKey(0);

    cout << "saved: " << output_file << endl;

    return EXIT_SUCCESS;
}

