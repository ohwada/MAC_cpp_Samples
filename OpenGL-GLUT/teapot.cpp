/**
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */

// reference : https://qiita.com/totepo18/items/b2a6bdb8054f8c9a1cbe

#include <string> 
#include <iostream>

// macOS
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

using namespace std;

// global
const int MODE_WIRE = 0;
const int MODE_SOLID_WHITE = 1;
const int MODE_SOLID_ADS = 2;
int mode = MODE_SOLID_WHITE;


/**
 * display
 */
void display(void)
{
    if (mode == MODE_WIRE) {
        // White
	    glClearColor ( 1.0, 1.0, 1.0, 1.0 );
    } else {
        // Gray
	    glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if( mode == MODE_WIRE){
        // Black
	    glColor3f(0.0, 0.0, 0.0);
	    glutWireTeapot(0.6);
    } else {
        // White
	    glColor3f(1.0, 1.0, 1.0);
	    glutSolidTeapot(0.6);
    }

	glFlush();
 	glutSwapBuffers();
}


/**
 * idle
 */
static void idle(void)
{
	glutPostRedisplay();
}


/**
 * init
 */
void init(void) 
{

    const GLfloat LIGHT_POS_1[4] = {0.0f,3.0f, 5.0f, 1.0f};
    const GLfloat LIGHT_POS_2[4] = {5.0f,3.0f, 0.0f, 1.0f};

    const GLfloat RED[] = { 1.0, 0.0, 0.0, 1.0 };
    const GLfloat GREEN[] = { 0.0, 1.0, 0.0, 1.0 };

    const GLfloat AMBIENT[4] = {0.3f,0.5f, 0.0f, 1.0f};
    const GLfloat DIFFUSE[4] = {1.0f,1.0f, 0.3f, 1.0f};
    const GLfloat SPECULAR[4] = {1.0f,1.0f, 1.0f, 1.0f};
    const GLfloat SHININESS[4] = {20.0f};

  glShadeModel (GL_SMOOTH);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POS_1);
    glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_POS_2);

    if(mode == MODE_SOLID_ADS){
        // ADS (Ambient, Diffuse, and Specular)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, RED);
        glLightfv(GL_LIGHT0, GL_SPECULAR, RED);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, GREEN);
        glLightfv(GL_LIGHT1, GL_SPECULAR, GREEN);
        glMaterialfv(GL_FRONT, GL_AMBIENT, AMBIENT);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, DIFFUSE);
        glMaterialfv(GL_FRONT, GL_SPECULAR, SPECULAR);
        glMaterialfv(GL_FRONT, GL_SHININESS, SHININESS);
    }
}


/**
 * reshape
 */
void reshape(int w, int h)	
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
void keyboard(unsigned char key, int x, int y)
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
 * mouse
 */
void mouse(int button, int state, int x, int y)  
{ 
    // nop 
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
	const char* WIN_TITLE = "Teapot";

	cout <<  WIN_TITLE << endl;

    if (argc > 1  ) {
        mode =  atoi(argv[1]);
    } else {
        cout << "Usage: " << argv[0] << "[mode] " << endl;
    } 

// open window
   glutInit(&argc, argv);	
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize (WIN_WIDTH, WIN_HEIGHT);	
   glutInitWindowPosition (WIN_POS_X, WIN_POS_Y);	
   glutCreateWindow (WIN_TITLE);							
   glutDisplayFunc(display);		
   glutIdleFunc(idle);		
   glutReshapeFunc(reshape);			
    glutKeyboardFunc(keyboard); 
	glutMouseFunc(mouse);

   init ();

   glutMainLoop();

    return EXIT_SUCCESS;				
}
