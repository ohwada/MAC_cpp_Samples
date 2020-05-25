/**
 * id3lib Sample
 * 2020-03-01 K.OHWADA
 */

// get album picture in mp3 file

// Note :
// Nathaniel_Wyvern_-_Infiltrators.mp3 : No Picture
// id3lib NOT support id3 v2.4.0
// https://sourceforge.net/p/id3lib/bugs/203/

#include "id3tags.hpp"

#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main( int argc, char **argv )
{

    if(argc != 2){
        cout << "Usage: " << argv[0] << " <mp3File>"  << endl;
        return EXIT_FAILURE;
  }

    char *input = argv[1];


// tag
    ID3Tag *tag = ID3Tag_New();
    if (!tag){
            cout << "ID3Tag_New Field" << endl;
            return EXIT_FAILURE;
    }

    ID3Tag_Link(tag, input);


// Picture
    ID3Frame *frame_pic = ID3Tag_FindFrameWithID(tag, ID3FID_PICTURE);
    if (!frame_pic){
            cout << "No Picture"  << endl;
            return EXIT_FAILURE;
    }


// mime
// consider it as "jpg", if mime is not set
    string ext = (char *)".jpg";

    ID3Field *field_mime = ID3Frame_GetField(frame_pic, ID3FN_MIMETYPE);

    if(field_mime){
        string mime = getTextFromIso8859(field_mime);
        cout << "mime: "<< mime << endl;

        if (mime.find("png") != string::npos) {
            ext = (char *)".png" ;
        }

    } // if MIMETYPE

// output file
    string fname = getFileNameWithoutExt(input);
    string pngfile = fname + ext ;
    char* output = (char*)pngfile.c_str();

// data
    ID3Field *field_data = ID3Frame_GetField(frame_pic, ID3FN_DATA);
    if( !field_data ){
        cout << "GetField  data Failed" << endl;
        return EXIT_FAILURE;
    }

  ID3Field_ToFile(field_data, output);

    cout << "saved: " << output << endl;

    return EXIT_SUCCESS;
}
