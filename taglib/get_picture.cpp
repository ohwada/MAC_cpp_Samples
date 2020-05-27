/**
 * taglib Sample
 * 2020-03-01 K.OHWADA
 */

// get album picture in mp3 file
// referemce : https://stackoverflow.com/questions/4752020/how-do-i-use-taglib-to-read-write-coverart-in-different-audio-formats


// taglib headers
#include<tbytevector.h>
#include<mpegfile.h>
#include<id3v2tag.h>
#include<id3v2frame.h>
#include <attachedpictureframe.h>

#include<string>
#include<iostream>

#include "parse_filename.hpp"

using namespace std ;


/**
 * main
 */
int main(int argc, char** argv)
{
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <mp3File>"  << endl;
        return EXIT_FAILURE;
  }

    char *input = argv[1];

    TagLib::MPEG::File mp3File(input);

    TagLib::ID3v2::Tag * mp3Tag= mp3File.ID3v2Tag();
    if(!mp3Tag)
    {
        cout << "ID3v2Tag Faild: "<< input <<endl;
        return EXIT_FAILURE;
    }

    //look for picture frames only
    TagLib::ID3v2::FrameList  listOfMp3Frames = mp3Tag->frameListMap()["APIC"];  
      
    if(listOfMp3Frames.isEmpty())
    {
            cout << "no picture" <<endl;
            return EXIT_FAILURE;
    }

    // get first PictureFrame
    TagLib::ID3v2::AttachedPictureFrame * pictureFrame;
    TagLib::ID3v2::FrameList::ConstIterator it= listOfMp3Frames.begin();
    for(; it != listOfMp3Frames.end() ; it++) {
            //cast Frame * to AttachedPictureFrame*
            pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *> (*it); 
            break;
    }

    TagLib::String mimetype = pictureFrame->mimeType();
    cout << "mimetype: " << mimetype << endl;

    // consider it as "jpg", if mime is not set
    string ext = (char *)".jpg";
       int pos = mimetype.find("png");
     if (pos != string::npos){
            ext = (char *)".png";
        }

        // output file
        string fname = getFileNameWithoutExt(input);
        string outfile = fname + ext ;
          char* output = (char*)outfile.c_str();

        // save to output file
        FILE *fout = fopen(output, "wb");
        fwrite(pictureFrame->picture().data(), pictureFrame->picture().size(), 1, fout);
        fclose(fout);

        cout << "saved: " << output << endl;

        return EXIT_SUCCESS;
}

