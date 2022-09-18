/**
 * face_detect.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/davisking/dlib/blob/master/examples/face_detection_ex.cpp

 #define DLIB_PNG_SUPPORT 
 #define DLIB_JPEG_SUPPORT 

#include <iostream>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>


using namespace dlib;
using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{  

    string file("images/lena.png");

    bool is_pyramid = false;

    if (argc == 3) {
        file  = argv[1];
        is_pyramid = (bool)std::stoi(argv[2]);
    } else if (argc == 2) {
        file  = argv[1];
    } else { 
        cout << "Usage: " << argv[0] << " <imgFile> " << endl;
  }

  cout << file  << endl;
  cout << boolalpha <<   "is_pyramid: " <<  is_pyramid << endl;

    try
    {

        frontal_face_detector detector = get_frontal_face_detector();
        image_window win;

       
            cout << "processing image " << file << endl;
            array2d<unsigned char> img;
            load_image(img, file);

            // upsample the image we make the detector run slower since it must
            // process a larger image.
            if( is_pyramid ) {
                pyramid_up(img);
            }

            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces it can find in the image.
            std::vector<rectangle> dets = detector(img);

            cout << "Number of faces detected: " << dets.size() << endl;

            // Now we show the image on the screen and the face detections as
            // red overlay boxes.
            win.clear_overlay();
            win.set_image(img);
            win.add_overlay(dets, rgb_pixel(255,0,0));

            cout << "Hit enter to quit" << endl;
            cin.get();
        
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// processing image images/lena.png
// Number of faces detected: 1
