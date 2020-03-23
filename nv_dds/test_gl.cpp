/**
 * dds Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include<iostream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "nv_dds.h"

#include "parse_filename.hpp"


using namespace std;


//
//　global
//
nv_dds::CDDSImage ddsImage;
GLuint texID;


/**
 * Initialize
 */
void Initialize(string input)
{

// Gray
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glEnable(GL_DEPTH_TEST);

	//　generate Texture
	glGenTextures(1, &texID);

	//　Bind Texture
	glBindTexture(GL_TEXTURE_2D, texID);


// load image
    ddsImage.load(input);


// file info
    int width = ddsImage.get_width();
    int height = ddsImage.get_height();

    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;


    // assing to Texture
    ddsImage.upload_texture2D();

}


/**
 * Idle
 */
void Idle()
{
	glutPostRedisplay();
}


/**
 * Display
 */
void Display()
{
	double size = 0.5;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind Texture
	glBindTexture(GL_TEXTURE_2D, texID);

	// White
	glColor4f(1.0, 1.0, 1.0, 1.0);

	// Draw a rectangle with texture coordinates
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);	glVertex3d(-size, -size, 0.0);
	glTexCoord2d(0.0, 1.0);	glVertex3d(-size, size, 0.0);
	glTexCoord2d(1.0, 1.0);		glVertex3d(size, size, 0.0);
	glTexCoord2d(1.0, 0.0);	glVertex3d(size, -size, 0.0);
	glEnd();

	// bind Texture　
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable texture mapping
	glDisable(GL_TEXTURE_2D);

	Idle();
	glutSwapBuffers();
}

/**
 * Keyboard
 */
void Keyboard(unsigned char key, int x, int y)
{

	const char CHAR_Q = 'q';

	switch ( key )
	{
	case CHAR_Q:
        // quit this Program
		exit(0);
		break;

	default:
		break;
	} // switch

}


/**
 * main
 */
int main( int argc, char **argv )
{

    nv_dds::CDDSImage ddsImage;

    const int WIN_WIDTH = 512;
    const int WIN_HEIGHT = 512;
    const int WIN_POS_X = 100;
    const int WIN_POS_Y = 100;


	cout << "dds: OpenGL" << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title =  "GL dds: " + fname;





    // open GL window
	glutInit(&argc, argv);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(win_title.c_str());
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);

    // initialize
	Initialize(input);

	glutMainLoop();


    return EXIT_SUCCESS;
}

