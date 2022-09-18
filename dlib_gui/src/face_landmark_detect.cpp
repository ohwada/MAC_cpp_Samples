/**
 * face_landmark_detect.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/davisking/dlib/blob/master/examples/face_landmark_detection_ex.cpp


 #define DLIB_PNG_SUPPORT 
 #define DLIB_JPEG_SUPPORT 


#include <iostream>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
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

    string model("/usr/local/share/dlib/shape_predictor_68_face_landmarks.dat");

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
       

        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        frontal_face_detector detector = get_frontal_face_detector();

        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.  Here we are just
        // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
        // as a command line argument.
        shape_predictor sp;
        deserialize(model) >> sp;


        image_window win, win_faces;
    
            cout << "processing image " << file << endl;
            array2d<rgb_pixel> img;
            load_image(img,  file);

            // Make the image larger so we can detect small faces.
            if( is_pyramid ) {
                pyramid_up(img);
            }

            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces in the image.
            std::vector<rectangle> dets = detector(img);
            cout << "Number of faces detected: " << dets.size() << endl;

            // Now we will go ask the shape_predictor to tell us the pose of
            // each face we detected.
            std::vector<full_object_detection> shapes;
            for (unsigned long j = 0; j < dets.size(); ++j)
            {
                full_object_detection shape = sp(img, dets[j]);
                cout << "number of parts: "<< shape.num_parts() << endl;
                cout << "pixel position of first part:  " << shape.part(0) << endl;
                cout << "pixel position of second part: " << shape.part(1) << endl;
                // You get the idea, you can get all the face part locations if
                // you want them.  Here we just store them in shapes so we can
                // put them on the screen.
                shapes.push_back(shape);
            } // for

            // Now let's view our face poses on the screen.
            win.clear_overlay();
            win.set_image(img);
            win.add_overlay(render_face_detections(shapes));

            // We can also extract copies of each face that are cropped, rotated upright,
            // and scaled to a standard size as shown here:
            dlib::array<array2d<rgb_pixel> > face_chips;
            extract_image_chips(img, get_face_chip_details(shapes), face_chips);
            win_faces.set_image(tile_images(face_chips));

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

