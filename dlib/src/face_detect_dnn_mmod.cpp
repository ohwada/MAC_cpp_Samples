/**
 * face_detect_dnn_mmod.cpp
 * 2022-06-01 K.OHWADA
 */

// Max-Margin Object Detection(MMOD)
// reference : https://github.com/davisking/dlib/blob/master/examples/dnn_mmod_face_detection_ex.cpp

#include <iostream>
#include <chrono>
#include <dlib/dnn.h>
#include <dlib/data_io.h>
#include <dlib/image_processing.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "parse_filename.hpp"


// ============

using namespace dlib;

template <long num_filters, typename SUBNET> using con5d = con<num_filters,5,5,2,2,SUBNET>;
template <long num_filters, typename SUBNET> using con5  = con<num_filters,5,5,1,1,SUBNET>;

template <typename SUBNET> using downsampler  = relu<affine<con5d<32, relu<affine<con5d<32, relu<affine<con5d<16,SUBNET>>>>>>>>>;
template <typename SUBNET> using rcon5  = relu<affine<con5<45,SUBNET>>>;

using net_type = loss_mmod<con<1,9,9,1,1,rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;

// ============



/**
 * visualize
 */
void visualize(cv::Mat& image,  dlib::mmod_rect face,         double scale_width,         double scale_height)
{
    const cv::Scalar GREEN(0, 255, 0);
    int thickness = 2;

    auto r = face.rect;

    int x1 = (int) (r.left() * scale_width );
    int y1 = (int) (r.top() * scale_height );
    int x2 = (int) (r.right() * scale_width );
    int y2 = (int) (r.bottom() * scale_height );

    std::cout << "x1 " << x1 << std::endl;
    std::cout << "x2 " << x2 << std::endl;
    std::cout << "y1 " << y1 << std::endl;
    std::cout << "y2 " << y2 << std::endl;

    cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, thickness);
}


/**
 * ocv_draw
 */
bool ocv_draw(std::string input_file,  std::string output_file,    std::vector<dlib::mmod_rect> faces, int face_width, int face_height)
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

        double scale_width = 
        (double)width / (double)face_width;
        double scale_height = 
        (double)height / (double)face_height;

    for (auto face: faces) 
    {
        visualize(image,  face, scale_width,  scale_height);
    } // for

// output image
    cv::imwrite(output_file, image);

    cv::imshow(WINNAME, image);


    return true;
}

/**
 *  dlib_face_detect
 */
bool dlib_face_detect(std::string file, int max_pyramid,    std::vector<dlib::mmod_rect> &faces,  int &width,   int &height)
{

    std::string model("/usr/local/share/dlib/mmod_human_face_detector.dat");

    try
    {
        net_type net;
        deserialize(model) >> net;  

        dlib::matrix<dlib::rgb_pixel> img;
        dlib:: load_image(img, file);


// Upsampling the image will allow us to detect smaller faces 
// but will cause 
// the program to use more RAM and run longer.
        const int MAX_SIZE = 1800*1800;
  
        int i = 0;
        if(max_pyramid > 0){ 
            for(i=0; i<max_pyramid; i++) {
                pyramid_up(img);
                if(img.size() > MAX_SIZE){
                    break;
                }
            } // for
        } // if

     std::cout << "pyramid up: " << i << std::endl;

// image size of upsampled
        width = img.nc();
        height = img.nr();
   
        std::cout << "width " << width << std::endl;
        std::cout << "height " << height << std::endl;


        faces = net(img);

        std::cout << "size: " << faces.size() << std::endl;

    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}


/**
 * print_ elapsed_time
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
    int max_pyramid = 0;

    if (argc == 3) {
        input_file  = argv[1];
         max_pyramid = std::stoi(argv[2]);
    } else if (argc == 2) {
        input_file  = argv[1];
    } else { 
        cout << "Usage: " << argv[0] << " <imgFile> " << endl;
  }


    string fname = getFileNameWithoutExt(input_file);
    string ext = getFileNameExt(input_file);
    string output_file = fname + string("_dnn_") 
        + to_string(max_pyramid) + string(".")+ ext; 


  cout << input_file  << endl;
  cout << output_file << endl;
  cout <<   "max_pyramid: " <<  max_pyramid << endl;

    std::vector<dlib::mmod_rect> faces;
    int width;
    int height;

    auto start = std::chrono::high_resolution_clock::now();

    dlib_face_detect(input_file, max_pyramid, faces,  width, height);

    print_elapsed_time(start);

    ocv_draw(input_file,  output_file,  faces, width, height);

    cv::waitKey(0);

    cout << "saved: " << output_file << endl;

    return EXIT_SUCCESS;
}