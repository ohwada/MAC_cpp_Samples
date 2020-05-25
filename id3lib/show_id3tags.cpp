/**
 * id3lib Sample
 * 2020-03-01 K.OHWADA
 */

// show id3 tag of mp3 file with libiconv
// original : https://github.com/jmckaskill/qsmp/blob/master/id3lib/examples/demo_simple.cpp

// Note :
// Nathaniel_Wyvern_-_Infiltrators.mp3 : Not found: Title
// id3lib NOT support id3 v2.4.0
// https://sourceforge.net/p/id3lib/bugs/203/

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

#include "TextEncodeConverter.hpp"

using namespace std;

// global
TextEncodeConverter converter;

const int BUF_SIZE = 1024;
unicode_t * unicode_buf = new unicode_t[BUF_SIZE];
bool flag_debug = false;


/**
 * getTextFromUtf16
 */
string getTextFromUtf16(ID3Field *field)
{

    int numChars = ID3Field_GetUNICODE(field, unicode_buf, BUF_SIZE);

    string u8;
    converter.convChars(
        (char *)unicode_buf, 
        2*numChars, 
        TEXT_ENC_UTF16BE,
        u8);

    return u8;
}


/**
 * getText
 */
string getText(ID3Frame *frame, char* name, bool flag_debug)
{

    ID3Field *field_enc = ID3Frame_GetField(frame, ID3FN_TEXTENC);
    if( !field_enc ){
        cout << "GetField  textenc Failed" << endl;
        return "";
    }

    ID3Field *field_text = ID3Frame_GetField(frame, ID3FN_TEXT);
    if( !field_text ){
        cout << "GetField  text Failed" << endl;
        return "";
    }

    int enc = ID3Field_GetINT(field_enc);

    string str;
    char *str_enc;

    if(enc == ID3TE_ISO8859_1){
        str_enc = (char *)"ISO8859_1";
        str = getTextFromIso8859(field_text);
    }else if(enc == ID3TE_UTF16){
        str_enc = (char *)"UTF16";
        str = getTextFromUtf16(field_text);
    }else if(enc == ID3TE_UTF8){
        str_enc = (char *)"UTF8";
        str = getTextFromUtf8(field_text);
    }

    if(flag_debug){
        cout << name << " enc: " << str_enc << " ( " << enc << " ) " << endl;
    }

    return str;
}


/**
 * printFindFrame
 */
void printFindFrame(ID3Tag *tag, ID3_FrameID id, char * name)
{
    ID3Frame *frame = ID3Tag_FindFrameWithID(tag, id);
    if (!frame){
        cout << "Not found: " << name << endl;
        return;
    }

    string text = getText(frame, name, flag_debug);
    if(text.empty()){
        cout << "getText Failed: " << name << endl;
        return;
    }

    cout << name << ": " << text << endl;
}


/**
 * main
 */
int main( int argc, char **argv )
{
      char *filename;

    if (argc == 3){
        filename = argv[1];
        flag_debug = atoi( argv[2] );
    }else if(argc == 2){
        filename = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <mp3File> [debug] "  << endl;
        return EXIT_FAILURE;
  }


    printId3libVersion();

    ID3Tag *tag = ID3Tag_New();
    if (!tag){
            cout << "ID3Tag_New Field" << endl;
            return EXIT_FAILURE;
    }

    ID3Frame *frame;

    ID3Tag_Link(tag, filename);

    printFindFrame(tag, ID3FID_TITLE, (char *)"Title");

    printFindFrame(tag, ID3FID_LEADARTIST, (char *)"Artist");

    printFindFrame(tag, ID3FID_COMPOSER, (char *)"Composer");

    printFindFrame(tag, ID3FID_ALBUM, (char *)"Album");

    printFindFrame(tag, ID3FID_YEAR, (char *)"Year");

    printFindFrame(tag, ID3FID_COMMENT, (char *)"Comment");

    cout << endl;  // empty line

    return EXIT_SUCCESS;
}

