/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 * reference : http://www.oit.ac.jp/is/L231/pukiwiki/index.php?%E6%84%9F%E8%A6%9A%E3%83%A1%E3%83%87%E3%82%A3%E3%82%A2%E7%A0%94%E7%A9%B6%E5%AE%A4/OpenGL/%E3%83%86%E3%82%AF%E3%82%B9%E3%83%81%E3%83%A3%E3%83%9E%E3%83%83%E3%83%94%E3%83%B3%E3%82%B0#s205ba9e
 */

#include "texture_util.hpp"

#ifdef USE_TGA
 #include "TGALoader.hpp"
 TGAImage tgaImage;
#endif

using namespace std;


// global variable
float g_spin = 0.0;  
bool g_is_spin = true; 
bool g_is_twice = false;



/**
 * loadTexture
 */
bool loadTexture(string filename, bool isReverse)
{

	char *image;
    int width;
    int height;
    char *data;


#ifdef USE_TGA
	//　Read file
    bool ret = tgaImage.ReadTGA(filename);
	if ( !ret ) {
        std::cerr << "ReadTGA faild: " << filename << endl;
		return false;
    }

	image = tgaImage.getImageData();
    width = tgaImage.getWidth();
    height = tgaImage.getHeight();
    data = image;

    // file info
    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << filename  << str_size << endl;
#endif


    if(isReverse){
        data = reverseUpsideDown(image, width, height);
    }

	// assign Texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); 

    // Texture param
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T); 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	return true;
}


/*
 * stupTexture
 */
void stupTextureReverse(char *image, int width, int height)  
{

    char *data = reverseUpsideDown(image, width, height);

	// assign Texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLubyte* )data); 

    // Texture param
    glDepthFunc(GL_LEQUAL);  
    glEnable(GL_DEPTH_TEST);  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

}


/*
 * displayTexPolygon
 */
void displayTexPolygon()  
{  

	// Draw a rectangle with texture coordinates
    // OpenGL coordinates are upside down.
    //mapping texure
    // to display in the correct orientation
  glEnable(GL_TEXTURE_2D);  
  glBegin(GL_QUADS);

// displayed upside down
// becasuse the coordinates of OpenGL are upside down,
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
 * ssetupFunc
 */
void setupFunc()
{          
    glutDisplayFunc(display_quads);
    glutIdleFunc(idle_quads);               
    glutReshapeFunc(reshape_quads);
    glutKeyboardFunc(keyboard_quads); 
}


/*
 * display
 */
void display_quads(void)  
{

    // Gray 
    glClearColor(0.5, 0.5, 0.5, 1.0); 
  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);  
  glPushMatrix();  

    glTranslatef(0.0, 0.0,-20.0);  
    glRotatef(g_spin, 0.0, 1.0, 0.0);  
    glColor3f(1.0, 1.0, 1.0);  
    displayTexPolygon();  

    if(g_is_spin){  
        g_spin+=1.0;
    }
  
  glPopMatrix();  
  glFlush();  
  glutSwapBuffers(); 
 
}


/**
 * idle
 */
void idle_quads(void)
{
	glutPostRedisplay();
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

} 


/*
 * reshape
 */
void reshape_quads(int w, int h)  
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
void keyboard_quads(unsigned char key, int x, int y)
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
 * reverse UpsideDown
 */
char* reverseUpsideDown(char *src, int width, int height)
{

    int bufsize = 4 * width * height;
    char* buff = new char[bufsize];

    for(int y = 0;  y<height; y++)
    {
        for(int x = 0; x<width; x++)
        {
            int col     = x;
            int row     = height - y - 1;
            int src_index   = (row * width + col) * 4;
            int index_rev  = (row * width + (width - col)) * 4;
            int buf_index = bufsize - index_rev;
            buff[buf_index + 0] = src[src_index + 0]; // R
            buff[buf_index + 1] = src[src_index + 1]; // G
            buff[buf_index + 2] = src[src_index + 2]; // B
            buff[buf_index + 3] = src[src_index + 3]; // A
        }
    }

    return buff;
}

