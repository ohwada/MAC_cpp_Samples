/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 * reference : http://www.oit.ac.jp/is/L231/pukiwiki/index.php?%E6%84%9F%E8%A6%9A%E3%83%A1%E3%83%87%E3%82%A3%E3%82%A2%E7%A0%94%E7%A9%B6%E5%AE%A4/OpenGL/%E3%83%86%E3%82%AF%E3%82%B9%E3%83%81%E3%83%A3%E3%83%9E%E3%83%83%E3%83%94%E3%83%B3%E3%82%B0#s205ba9e
 */


#include "texture_util.hpp"

// global variable
float g_spin = 0.0;  
bool g_is_spin = true; 
bool g_is_twice = false;

/*
 * setupWindow
 */
void setupWindow(std::string title, int width, int height, int x, int y) 
{ 
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);  
    glutInitWindowSize(width, height);          
    glutInitWindowPosition(x, y);      
    glutCreateWindow(title.c_str());

    dumpGLInfo();
}


/*
 * displayTexPolygon
 */
void displayTexPolygon()  
{  
  glEnable(GL_TEXTURE_2D);  
  glBegin(GL_QUADS);  
  glTexCoord2f(0.0, 0.0); glVertex3f(-5.0,-5.0, 0.0);  
  glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 5.0, 0.0); 
 
// for an Exercise of how to use Texture
    if(g_is_twice) {
        // draw image twice horizontally
        glTexCoord2f(2.0, 1.0); glVertex3f( 5.0, 5.0, 0.0);  
        glTexCoord2f(2.0, 0.0); glVertex3f( 5.0,-5.0, 0.0); 
    } else {
        glTexCoord2f(1.0, 1.0); glVertex3f( 5.0, 5.0, 0.0);  
        glTexCoord2f(1.0, 0.0); glVertex3f( 5.0,-5.0, 0.0);
    }

  glEnd();  
  glDisable(GL_TEXTURE_2D);  
}


/*
 * display
 */
void display(void)  
{  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  
  glPushMatrix();  
  {  
    glTranslatef(0.0, 0.0,-20.0);  
    glRotatef(g_spin, 0.0, 1.0, 0.0);  
    glColor3f(1.0, 1.0, 1.0);  
    displayTexPolygon();  
  }

    if(g_is_spin){  
        g_spin+=1.0;
    }
  
  glPopMatrix();  
  glFlush();  
  glutSwapBuffers();  
}


/*
 * setupTexture
 */
void setupTexture(GLubyte* image, int width, int height, GLint internalformat, GLenum format)   
{ 

// Gray 
    glClearColor(0.5, 0.5, 0.5, 1.0); 
 
    glDepthFunc(GL_LEQUAL);  
    glEnable(GL_DEPTH_TEST); 
  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, image);  

    glutIdleFunc(display);              
    glutDisplayFunc(display);           
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); 

} 


/*
 * reshape
 */
void reshape(int w, int h)  
{  
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);  
  glMatrixMode(GL_PROJECTION);            
  glLoadIdentity();               
  glFrustum(-5.0, 5.0,-5.0, 5.0, 5.0, 500.0);   
  glMatrixMode(GL_MODELVIEW);             
  glLoadIdentity();               
}


/**
 *  setTwice
 */
void setTwice(bool flag)
{
    g_is_twice = flag;
}


/**
 * keyboard
 */
void keyboard(unsigned char key, int x, int y)
{

	const char CHAR_Q = 'q';
	const char CHAR_T = 't';
	const char CHAR_SPACE = ' ';

	switch ( key )
	{
	case CHAR_Q:
        // quit this Program
		exit(0);
		break;

	case CHAR_T:
        // toggle draw twice or not
        g_is_twice = !g_is_twice;
		break;

	case CHAR_SPACE:
        // toggle spin or not
        g_is_spin = !g_is_spin;
		break;

	default:
		break;
	}  // switch

}

/**
 * dumpGLInfo
 */
void dumpGLInfo() 
{

    std::string vendor = (char *)glGetString(GL_VENDOR);
    std::string renderer = (char *)glGetString(GL_RENDERER);
    std::string version = (char *)glGetString(GL_VERSION);

    std::cout << "OpenGL Vender: " << vendor << std::endl;
    std::cout << "OpenGL Renderer: " << renderer << std::endl;
    std::cout << "OpenGL Version: " << version << std::endl;
    std::cout << "GLUT Version: " <<  GLUT_API_VERSION << std::endl;

}