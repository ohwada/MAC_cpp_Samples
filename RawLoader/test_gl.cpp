/**
 * RawLoader Sample
 * 2020-02-01 K.OHWADA
 * reference : http://asura.iaigiri.com/OpenGL/gl4.html
 */


/***********************************************************************
　　Main.cpp

　　RAW Texture Mapping

　　Date : Aug 27, 2007
　　Version : 1.0
　　Author : Pocol
　　Memo :
*************************************************************************/

//
//　include
//
#include <iostream>
#include <iostream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>


#include "RawLoader.h"

#include "parse_raw_filename.hpp"

using namespace std;


//
//　global
//
int WindowWidth = 512;
int WindowHeight = 512;
RAWImage rawImage;
GLuint texID;


//
//　prototype
//
bool Initialize(string filename);
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

    const int WIN_POS_X = 100;
    const int WIN_POS_Y = 100;


	cout << "RawLoader: gl " << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];

    string fname = getFileNameWithExt(input);

    string win_title =  "ogl RawLoader: " + fname;

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
	
	cout << "RawLoader Successfully" << endl;

	glutMainLoop();

    return EXIT_SUCCESS;
}


//---------------------------------------------------------------------------------------------------
//　　Load
//　　Desc : Read file and create texture
//---------------------------------------------------------------------------------------------------
bool Load(const std::string filename, const GLuint width, const GLuint height, bool alphaFlag)
{

	bool ret = rawImage.ReadRAW(filename, width, height, alphaFlag);
    if(!ret){
        return false;
    }


    char* imageData = rawImage.getImageData();

    GLenum format;
    GLuint internalFormat;

	if ( alphaFlag )
	{
		format = GL_RGBA;
		internalFormat = GL_RGBA;
	}
	else
	{
		format = GL_RGB;
		internalFormat = GL_RGB;
	}


	// generate Texture
	glGenTextures(1, &texID);

	// Bind Texture
	glBindTexture(GL_TEXTURE_2D, texID);

	if ( alphaFlag ) glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	else glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Texture assignment
	gluBuild2DMipmaps(
		GL_TEXTURE_2D,
		internalFormat,
		width,
		height,
		format,
		GL_UNSIGNED_BYTE,
		imageData );

	// Specifying how to scale the texture
	glTexParameteri(GL_TEXTURE_2D, 	GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, 	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// Texture environment
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//
	glBindTexture(GL_TEXTURE_2D, 0);

	// Release memory
	delete [] imageData;
	imageData = NULL;

	return true;
}



//----------------------------------------------------------------------------------------------------
//　　Initialize
//　　Desc : Initialization
//----------------------------------------------------------------------------------------------------
bool Initialize(string filename)
{

// Gray
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glEnable(GL_DEPTH_TEST);

	//parse file param
	int width;
	int height;
	bool alpha;
	bool ret1 = parse_raw_file_param(filename, width, height, alpha);
	if(!ret1){
        cerr << "parse_file_param Faild: " << filename << endl;
		return false;
	}

	// Load texture
    bool ret2 = Load(filename, width, height, alpha);
    if(ret2){
        string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
        cout << "loadImage: " << filename  << str_size << endl;
    } else {
        cerr << "loadImage Faild: " << filename << endl;
    }

    return ret2;
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
//　　Desc : ウDrawing to window
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
    // OpenGL coordinates are upside down.
    //mapping texure
    // to display in the correct orientation
	glBegin(GL_QUADS);
	   glTexCoord2d(-1.0, 1.0);	glVertex3d(-size, -size, 0.0);
	   glTexCoord2d(-1.0, 0.0);	glVertex3d(-size, size, 0.0);
	   glTexCoord2d(0.0, 0.0);	glVertex3d(size, size, 0.0);
	   glTexCoord2d(0.0, 1.0);	glVertex3d(size, -size, 0.0);
	glEnd();

	// bind Texture　
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable texture mapping
	glDisable(GL_TEXTURE_2D);

	Idle();
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
//　　Desc : processing when drag Mouse
//-------------------------------------------------------------------------------------------------
void Motion(int x, int y)
{
}

//--------------------------------------------------------------------------------------------------
//　　PassiveMotion
//　　Desc : processing when move Mouse
//--------------------------------------------------------------------------------------------------
void PassiveMotion(int x, int y)
{
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
	}

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
	} // switch

}
