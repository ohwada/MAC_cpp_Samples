/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */


#include "texture_util.hpp"

#include "TGALoader.hpp"

#include "parse_filename.hpp"

using namespace std;


/**
 * createWindowTitle
 */
string createWindowTitle(string input)
{

    string dir;
    string title;
    string ext;
    parseFileName(input, dir, title, ext);

    string window_title =  "Image Texture: " + title;

    return window_title;
}


/*
 * main
 */
int main(int argc , char ** argv) 
{

    TGAImage tgaImage; 
    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;
    const int WIN_POS_X = 100;
    const int WIN_POS_Y = 100;

    cout << "OpenGL/GLUT Texture" << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];

    string win_title = createWindowTitle(input);
            
  glutInit(&argc, argv); 

    setupWindow(win_title,
        WIN_WIDTH, 
        WIN_HEIGHT, 
        WIN_POS_X, 
        WIN_POS_Y );

	bool ret = tgaImage.ReadTGA(input);
    if(!ret){
        cerr << "Usage: " <<  "ReadTGA Faild "  << endl;
        return EXIT_FAILURE;
    }

	GLubyte* image = tgaImage.getImageData();
	GLuint width = tgaImage.getWidth();
	GLuint height = tgaImage.getHeight();
	GLuint internalFormat = tgaImage.getInternalFormat();
	GLenum format = tgaImage.getFormat();

    setupTexture(width, height, internalFormat, format, image);

    cout << "Texture Successfully" << endl;

  glutMainLoop();
                 
    return EXIT_SUCCESS;
}
