/**
 * Devil Sample
 * 2020-02-01 K.OHWADA
 */

#include <string> 
#include<iostream>

#include <IL/il.h>

char* devil_loadImage(std::string fileName, int &width, int &height);


bool devil_saveImage(std::string fileName, char *data, int width, int height);

char* reverseUpsideDown(char *src, int width, int height);

void devil_printError();

