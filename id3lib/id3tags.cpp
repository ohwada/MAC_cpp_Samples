/**
 * id3lib Sample
 * 2020-03-01 K.OHWADA
 */


// original : https://github.com/jmckaskill/qsmp/blob/master/id3lib/examples/demo_simple.cpp
//
// You can use codecvt or utf_converter,  instead of libiconv
//
/* $Id: demo_simple.cpp,v 1.1 2002/07/23 13:47:58 t1mpy Exp $

 * Copyright 2000 Scott Thomas Haug <scott@id3.org>
 *  
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "id3tags.hpp"

using namespace std;


// global
const int ID3TAGS_BUF_SIZE = 1024;
char * iso8859_buf = new char [ID3TAGS_BUF_SIZE];
unicode_t * nicode_buf = new unicode_t[ID3TAGS_BUF_SIZE];


/**
 * getTextFromIso8859
 */
string getTextFromIso8859(ID3Field *field)
{
    int numChars = ID3Field_GetASCII(field, iso8859_buf, ID3TAGS_BUF_SIZE);
    iso8859_buf[numChars+1] = '\0';
    string str = (char *)&iso8859_buf[0];
    return str;
}


/**
 * getTextFromUtf8
 */
string getTextFromUtf8(ID3Field *field)
{

    ID3Field_GetUNICODE(field, nicode_buf, ID3TAGS_BUF_SIZE);
    std::string u8 = (char *)&nicode_buf[0];
    return u8;
}


/**
 * printId3libVersion
 */
void printId3libVersion(void)
{
    const char DOT = '.';
    string ver = 
        to_string(ID3LIB_MAJOR_VERSION)
        + DOT
        + to_string(ID3LIB_MINOR_VERSION)
        + DOT
        + to_string(ID3LIB_PATCH_VERSION);

    cout << "id3lib Version: " << ver <<endl;

}

