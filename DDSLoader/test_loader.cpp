/*
 * DDSLoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl7.html
 */

/***********************************************************************
　　Main.cpp

　　DDS Texture Mapping

　　Date : Nov 01, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo :
*************************************************************************/

//
//　include
//
#include <string>
#include <iostream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "DDSLoader.h"

#include "parse_filename.hpp"

using namespace std;

//
//　global
//
DDSImage ddsImage;
GLuint texID;
int WindowWidth = 512;
int WindowHeight = 512;


//
//　prototype
//
void Initialize(string input);
void Display();
void Idle();
void Reshape(int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);


//----------------------------------------------------------------------------------------------------
//　　main
//　　Desc : Main entry point
//----------------------------------------------------------------------------------------------------
int main( int argc, char **argv )
{

int WIN_POS_X = 100;
int WIN_POS_Y = 100;

	cout << "dds: OpenGL" << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];

    string fname = getFileNameWithExt(input);

    string win_title =  "ogl DDSLoader: " + fname;

	// open window
	glutInit(&argc, argv);
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(win_title.c_str());
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	
	Initialize(input);
	
	glutMainLoop();

    return EXIT_SUCCESS;
}


//----------------------------------------------------------------------------------------------------
//　　Initialize
//　　Desc : Initialization
//----------------------------------------------------------------------------------------------------
void Initialize(string input)
{

// Gray
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glEnable(GL_DEPTH_TEST);

	//  Load texture
	texID = ddsImage.Load(input);

    int width = ddsImage.getWidth();
    int height = ddsImage.getHeight();
    string format = ddsImage.getDdsFormat();

    // file info
    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;
    cout << "DDS format: " << format   << endl;

}

//---------------------------------------------------------------------------------------------------
//　　Idle
//　　Desc : Processing when idling
//---------------------------------------------------------------------------------------------------
void Idle()
{
	glutPostRedisplay();
}

//---------------------------------------------------------------------------------------------------
//　　Reshape
//　　Desc : Resize
//---------------------------------------------------------------------------------------------------
void Reshape(int x, int y)
{
	WindowWidth = x;
	WindowHeight = y;
	if ( WindowWidth < 1 ) WindowWidth = 1;
	if ( WindowHeight < 1 ) WindowHeight = 1;
}

//---------------------------------------------------------------------------------------------------
//　　Display
//　　Desc : Drawing to window
//---------------------------------------------------------------------------------------------------
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
	glTexCoord2d(0.0, -1.0);	glVertex3d(-size, size, 0.0);
	glTexCoord2d(1.0, -1.0);	glVertex3d(size, size, 0.0);
	glTexCoord2d(1.0, 0.0);	glVertex3d(size, -size, 0.0);
	glEnd();

	// bind Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable texture mapping
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

//---------------------------------------------------------------------------------------------------
//　　Mouse
//　　Desc : Mouse processing
//---------------------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	switch ( button )
	{
	case GLUT_LEFT_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_MIDDLE_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	default:
		break;
	}
	

}

//--------------------------------------------------------------------------------------------------
//　　Motion
//　　Desc : rocessing when drag Mouse
//-------------------------------------------------------------------------------------------------
void Motion(int x, int y)
{
    // nop
}

//--------------------------------------------------------------------------------------------------
//　　PassiveMotion
//　　Desc : processing when move Mouse
//--------------------------------------------------------------------------------------------------
void PassiveMotion(int x, int y)
{
    // nop
}

//--------------------------------------------------------------------------------------------------
//　　Keyboard
//　　Desc : Keyboard processing
//--------------------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------------------
//　　Special
//　　Desc : Special key processing
//--------------------------------------------------------------------------------------------------
void Special(int key, int x, int y)
{
	switch ( key )
	{
	case GLUT_KEY_F1:
		break;

	case GLUT_KEY_F2:
		break;

	case GLUT_KEY_F3:
		break;

	case GLUT_KEY_F4:
		break;

	case GLUT_KEY_F5:
		break;

	case GLUT_KEY_F6:
		break;

	case GLUT_KEY_F7:
		break;

	case GLUT_KEY_F8:
		break;

	case GLUT_KEY_F9:
		break;

	case GLUT_KEY_F10:
		break;

	case GLUT_KEY_F11:
		break;

	case GLUT_KEY_F12:
		break;

	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;

	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_HOME:
		break;

	case GLUT_KEY_END:
		break;

	case GLUT_KEY_INSERT:
		break;
	}// switch

}
