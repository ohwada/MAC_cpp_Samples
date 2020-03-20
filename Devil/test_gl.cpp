/**
 * Devil Sample
 * 2020-02-01 K.OHWADA
 */



// display upside down
// because the OpenGL coordinates are reversed,
// load Image in the correct orientation


#include <string> 
#include<iostream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "devil_util.hpp" 

#include "parse_filename.hpp"


using namespace std;


//
//　global
//
GLuint texID;


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

	//glBindTexture(GL_TEXTURE_2D, texture.ID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// White
	glColor4f(1.0, 1.0, 1.0, 1.0);

	// Draw a rectangle with texture coordinates
    // OpenGL coordinates are upside down.
    //mapping texure
    // to display in the correct orientation
	glBegin(GL_QUADS);
	   glTexCoord2d(-1.0, 1.0);	glVertex3d(-size, -size, 0.0);
	   glTexCoord2d(-1.0, 0.0);	glVertex3d(-size, size, 0.0);
	   glTexCoord2d(0.0, 0.0);	glVertex3d(size, size, 0.0);
	   glTexCoord2d(0.0, 1.0);	glVertex3d(size, -size, 0.0);
	glEnd();
	//　
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable texture mapping
	glDisable(GL_TEXTURE_2D);

	Idle();
	glutSwapBuffers();
}


/**
 * main
 */
int main( int argc, char **argv )
{

const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;
const int WIN_POS_X = 100;
const int WIN_POS_Y = 100;


	cout << "Devil: OpenGL" << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];


    string fname = getFileNameWithExt(input);

    string win_title =  "GL Devil: " + fname;


	// Initialize DevIL.
	ilInit();

 // loadImage
    int width;
    int height;
    char* image = devil_loadImage(input, width, height);
	if (!image)
	{
        cerr << "mage_new Faild" << endl;
        return EXIT_FAILURE;
	}

    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;

	
    // open GL window
	glutInit(&argc, argv);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(win_title.c_str());
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);


// Gray
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glEnable(GL_DEPTH_TEST);

	//　generate Texture
	glGenTextures(1, &texID);

	//　Bind Texture
	glBindTexture(GL_TEXTURE_2D, texID);

	//　Texture assignment
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);


	glutMainLoop();

    devil_printError();

    return EXIT_SUCCESS;
}

