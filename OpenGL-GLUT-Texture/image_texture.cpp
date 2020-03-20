/*
 * OpenGL Sample
 * 2020-02-01 K.OHWADA
 */


#include "texture_util.hpp"

#include "parse_filename.hpp"

using namespace std;


/*
 * readImage
 */
char* readImage(string input, int &width, int &height)  
{

    char header[18]; 

  /* texture file open */  
    FILE *fp = fopen(input.c_str(), "rb");
    if(fp==NULL){  
	    cerr << "Could not open file : " << input << endl;
        return NULL;  
    } 


	// read header information
    int num = sizeof(header);
	int ret = fread(header, 1, num, fp);
    if(ret < num){
		cerr << "Could not read header : " << input << endl;
		return NULL;
    }


	// determine width and height
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];


	// create image buffer
    int bufsize = 4*width*height;
    char *image = new char[bufsize];

    // tga order B G R A
    // image order R G B A

  for(int y=0;y<height;y++){  
    for(int x=0;x<width;x++){ 
        int index = 4*width*y + 4*x; 
      image[index+2] = fgetc(fp); /* B */  
      image[index+1] = fgetc(fp); /* G */  
      image[index+0] = fgetc(fp); /* R */  
      image[index+3] = fgetc(fp); /* alpha */  
    } // x 
  } //y


  fclose(fp); 

    return image; 
}


/*
 * main
 */
int main(int argc , char ** argv) 
{

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

    string fname = getFileNameWithExt(input);

    string win_title =  "Image Texture: " + fname;

 
    // open window           
  glutInit(&argc, argv); 

    setupWindow(win_title,
        WIN_WIDTH, 
        WIN_HEIGHT, 
        WIN_POS_X, 
        WIN_POS_Y );

// read Image
    int width;
    int height;
	char* image = readImage(input, width, height);
    if(!image){
        cerr <<  "readImage Faild "  << input << endl;
        return EXIT_FAILURE;
    }

    // file info
    string str_size = " ( " + to_string(width)  + " x " + to_string(height) + " )";
    cout << "loadImage: " << input  << str_size << endl;

    // show in window
    setupTexture((GLubyte*)image, width, height, GL_RGBA, GL_RGBA);

    cout << "Texture Successfully" << endl;

  glutMainLoop();
                 
    return EXIT_SUCCESS;
}
