/**
 * face_detect_landmark.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/davisking/dlib/blob/master/examples/face_landmark_detection_ex.cpp

#include <iostream>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include <dlib/image_io.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "parse_filename.hpp"


using namespace dlib;


/**
 * visualize
 */
void visualize(cv::Mat& image,  full_object_detection shape, 
double scale_width, double scale_height)
{
    const cv::Scalar GREEN(0, 255, 0);
    int thickness = 2;
        int radius = 3;

    auto rect = shape.get_rect();

    int x1 = (int) (rect.left() * scale_width );
    int y1 = (int) (rect.top() * scale_height );
    int x2 = (int) (rect.right()  * scale_width);
    int y2 = (int) (rect.bottom() * scale_height );

    std::cout << "x1 " << x1 << std::endl;
    std::cout << "x2 " << x2 << std::endl;
    std::cout << "y1 " << y1 << std::endl;
    std::cout << "y2 " << y2 << std::endl;

    cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, thickness);

 unsigned long num = shape.num_parts();
        for(int i=0; i<num; i++){
            dlib::point p = shape.part(i);
int x = p.x();
int y = p.y();
std::cout << "x: " << x << " y: " << y << std::endl;
        cv::circle(image, cv::Point(x, y), radius, GREEN, thickness);
        }

}



/**
 * ocv_draw
 */
bool ocv_draw(std::string input_file,  std::string output_file,       std::vector<full_object_detection> shapes, int face_width, int face_height)
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

   for(auto shape: shapes)
    {
        visualize(image,  shape, scale_width,  scale_height);
    } // for

// output image
    cv::imwrite(output_file, image);

    cv::imshow(WINNAME, image);

    return true;
}



/**
 *  dlib_face_detect
 */
bool dlib_face_detect(std::string input_file, bool is_pyramid,  std::vector<full_object_detection> &shapes,  int &width,   int &height)
{

    std::string model("/usr/local/share/dlib/shape_predictor_68_face_landmarks.dat");

    try
    {
    
        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        frontal_face_detector detector = get_frontal_face_detector();

        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.          
        shape_predictor sp;
        deserialize(model) >> sp;


        //image_window win, win_faces;
        // Loop over all the images provided on the command line.

            array2d<rgb_pixel> img;
            load_image(img, input_file);


            // Make the image larger so we can detect small faces.
        if(is_pyramid){
           pyramid_up(img);
        }

        width = img.nc();
        height = img.nr();
   
        std::cout << "width " << width << std::endl;
        std::cout << "height " << height << std::endl;


            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces in the image.
            std::vector<rectangle> dets = detector(img);
            std::cout << "Number of faces detected: " << dets.size() << std::endl;

            // Now we will go ask the shape_predictor to tell us the pose of
            // each face we detected.
         

            for (unsigned long j = 0; j < dets.size(); ++j)
            {
                full_object_detection shape = sp(img, dets[j]);
                std::cout << "number of parts: "<< shape.num_parts() << std::endl;

                std::cout << "pixel position of first part:  " << shape.part(0) << std::endl;
                std::cout << "pixel position of second part: " << shape.part(1) << std::endl;
                // You get the idea, you can get all the face part locations if
                // you want them.  Here we just store them in shapes so we can
                // put them on the screen.
                shapes.push_back(shape);
        } // for

    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{  

    string input_file("images/Tom_Cruise_avp_2014_4.jpg");
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
    string output_file = fname + string("_landmark.") + ext; 

 cout << input_file  << endl;
  cout << output_file << endl;
  cout << boolalpha <<   "is_pyramid: " <<  is_pyramid << endl;

    std::vector<full_object_detection> shapes;
    int width;
    int height;

    dlib_face_detect(input_file, is_pyramid,  shapes,  width,  height);

    ocv_draw(input_file,  output_file,  shapes, width, height);

    cv::waitKey(0);

    cout << "saved: " << output_file << endl;

    return EXIT_SUCCESS;
}

