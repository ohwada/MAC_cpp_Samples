/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 * reference : http://nn-hokuson.hatenablog.com/entry/2017/02/24/171230
 */


#include "texture_util.hpp"

#include "devil_util.hpp"

#include "parse_filename.hpp"

using namespace std;



/**
 * main
 */
int main(int argc , char ** argv) 
{

    cout << "OpenGL/glfw Texture" << endl;

const int WIN_WIDTH  = 640;
const int WIN_HEIGHT = 480;
const int SWAP_INTERVAL = 1;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];


    // win title
    string fname = getFileNameWithExt(input);
    string win_title =  "glfw Texture: " + fname;


	// Initialize DevIL.
	ilInit();

    int width; 
    int height;
    char *image = devil_loadImage(input, width, height);
    if(!image) {
        cerr << "readImage Faild: " << input << std::endl;
        return EXIT_FAILURE;
    }

    // print file info
    string str_width = std::to_string(width);
   string str_height = std::to_string(height);
    string filesize = " ( " + str_width + " x " +  str_height + " ) ";
   cout << "readImage: " << input << filesize << std::endl;


    if( !glfwInit() ){
        cerr << "glfwInit Faild"  << endl;
        return EXIT_FAILURE;
    }


    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, win_title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        cerr << "glfwCreateWindow Faild"  << endl;
        return EXIT_FAILURE;
    }
    

    // Synchronization with Window
    glfwMakeContextCurrent(window);
    glfwSwapInterval(SWAP_INTERVAL);
    
    GLuint programId = crateShader();
    
    dumpGLInfo();

    GLuint texID = setupTexture(image, width, height);


    // loop
    while (!glfwWindowShouldClose(window)) {

        // drawing
        display(programId, texID);
      
        // Swap buffers
        glfwSwapBuffers(window);
        
        // Waiting for event
        glfwPollEvents();
    }


    glfwTerminate();

    cout << "OpenGL Successfuly"  << endl;

    return EXIT_SUCCESS;
}
