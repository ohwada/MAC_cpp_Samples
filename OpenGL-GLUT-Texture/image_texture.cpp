/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include <iostream>

#include "texture_util.hpp"

#include "parse_filename.hpp"

using namespace std;


/*
 * main
 */
int main(int argc , char ** argv) 
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;
    const int WIN_POS_X = 100;
    const int WIN_POS_Y = 100;

    cout << "Image Texture" << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];

    string fname = getFileNameWithExt(input);

    string win_title =  "Image Texture: " + fname;

 
    // open window           
  glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);  
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);          
    glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);      
    glutCreateWindow(win_title.c_str());
    setupFunc();

    // load Texture
    bool ret = loadTexture(input, true);
    if(!ret){
        cerr << "loadTexture Faild: " << input << endl;
        return EXIT_FAILURE;
    }

    cout << "loadTexture: " << input << endl;

  glutMainLoop();
                 
    return EXIT_SUCCESS;
}
