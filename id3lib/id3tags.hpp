/**
 * id3lib Sample
 * 2020-03-01 K.OHWADA
 */

#include <id3.h>
#include <string>
#include <iostream>

#ifndef _ID3TAGS_H_
#define _ID3TAGS_H_

std::string getTextFromIso8859(ID3Field *field);

std::string getTextFromUtf8(ID3Field *field);

void printId3libVersion(void);

#endif // _ID3TAGS_H_

