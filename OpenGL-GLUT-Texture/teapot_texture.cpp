/**
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */


#include <string> 
#include <iostream>

#include "texture_util.hpp"

#include "parse_filename.hpp"

using namespace std;


/**
 * initShadeModel
 */
void initShadeModel(void) 
{

    const GLfloat lLIGHT_POSITION_1[4] = {0.0f,3.0f, 5.0f, 1.0f};
    const GLfloat lLIGHT_POSITION_2[4] = {5.0f,3.0f, 0.0f, 1.0f};

  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, lLIGHT_POSITION_1);
    glLightfv(GL_LIGHT1, GL_POSITION, lLIGHT_POSITION_2);
}


/**
 * display
 */
void display_teapot(void)
{

    // Gray
	glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // White
	glColor3f(1.0, 1.0, 1.0);

	glutSolidTeapot(0.7);

	glFlush();
 	glutSwapBuffers();
}


/**
 * idle
 */
void idle_teapot(void)
{
	glutPostRedisplay();
}



/**
 * reshape
 */
void reshape_teapot(int w, int h)
{

	glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,
                   (double)w/h,
                   0.1,
                   100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(-0.5, 2.1, 2.0,
              0.0, 0.0, 0.0,
              0.0, 4.0, 0.0);

}


/**
 * keyboard
 */
void keyboard_teapot(unsigned char key, int x, int y)
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
	}  // switch

}


/**
 * main
 */
int main(int argc, char** argv)
{

	const int WIN_WIDTH = 500;
	const int WIN_HEIGHT = 500;
	const int WIN_POS_X = 100;
	const int WIN_POS_Y = 100;

    cout << "Teapot Texture" << endl;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
        return EXIT_FAILURE;
    }

    string  input = argv[1];

    string fname = getFileNameWithExt(input);

    string win_title =  "Teapot Texture: " + fname;


// open window
   glutInit(&argc, argv);	
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (WIN_WIDTH, WIN_HEIGHT);	
   glutInitWindowPosition (WIN_POS_X, WIN_POS_Y);	
   glutCreateWindow (win_title.c_str());							
   glutDisplayFunc(display_teapot);		
    glutIdleFunc(idle_teapot);		
    glutReshapeFunc(reshape_teapot);			
    glutKeyboardFunc(keyboard_teapot); 

   initShadeModel();

    // load Texture
    bool ret = loadTexture(input, false);
    if(!ret){
        cerr << "loadTexture Faild: " << input << endl;
        return EXIT_FAILURE;
    }

    cout << "loadTexture: " << input << endl;

   glutMainLoop();

    return EXIT_SUCCESS;				
}
