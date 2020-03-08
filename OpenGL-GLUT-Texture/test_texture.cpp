/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 * reference : http://www.oit.ac.jp/is/L231/pukiwiki/index.php?%E6%84%9F%E8%A6%9A%E3%83%A1%E3%83%87%E3%82%A3%E3%82%A2%E7%A0%94%E7%A9%B6%E5%AE%A4/OpenGL/%E3%83%86%E3%82%AF%E3%82%B9%E3%83%81%E3%83%A3%E3%83%9E%E3%83%83%E3%83%94%E3%83%B3%E3%82%B0#s205ba9e
 */

#include "texture_util.hpp"

#include "pixels.h"

using namespace std;

 

/*
 * createWindowTitle
 */
string createWindowTitle(int mode, int size)
{
    string label = "Color Matrix Texture: ";
    if(mode == 2){
        label = "CheckerBoard Texture: ";
    }

    string str_size = to_string(size);
   string win_title = label + str_size + " x " + str_size;
    return win_title;
}


/*
 * main
 */
int main(int argc , char ** argv) 
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;
    const int WIN_POS_X = 100;
    const int WIN_POS_Y = 100;


// Usage: test <mode> <image size>
// mode 1 : use Color Matrix pattern
// mode 2 : use CheckerBoard pattern
// try "test 2 16"

    const int MODE_COLOR = 1;
    const int MODE_CHECKER = 2;

    int mode = MODE_COLOR;
    int size = 2;

    cout << "OpenGL/GLUT Texture" << endl;

    if (argc > 2) {
        mode = atoi(argv[1]);
        size = atoi(argv[2]);
    } else {
        cout << "Usage: " << argv[0] << " <mode> <size> "  << endl;
    }

   string win_title = createWindowTitle(mode, size);


    // ColorMatrixPixel
    const int SCALE = 1;
    int width = SCALE * size;
    int height = SCALE * size;
    char* pixel = createColorMatrixPixel(size, SCALE);


    if(mode == MODE_CHECKER) {
        // CheckerBoard
        width = size;
        height = size;
        pixel = createCheckerBoardPixel(width, height);             
    }


  glutInit(&argc, argv); 

    setupWindow(win_title,
        WIN_WIDTH, 
        WIN_HEIGHT, 
        WIN_POS_X, 
        WIN_POS_Y );

    setupTexture((GLubyte* )pixel, width, height, GL_RGBA, GL_RGBA);

    cout << "Texture Successfully" << endl;

// you can operate by key input
// 'q' : quit this program
// 't' : toggle to draw image twice horizontally or not 
// for an Exercise of how to use Texture
// Space bar : toggle to spin or not 

  glutMainLoop();
                 
    return EXIT_SUCCESS;
}
