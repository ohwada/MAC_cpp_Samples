/**
 * conv_ogg_to_wav_list.cpp
 * 2022-06-01 K.OHWADA
 */

// convert ogg files and oga files in the directory
// to wav format files at once


// g++ conv_ogg_to_wav_list.cpp -std=c++11 -o list `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg`


#include <iostream>
#include <vector>
#include <string> 
#include"ogg_to_wav.hpp"
#include "file_list.hpp"
#include"parse_filename.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char** argv) 
{

    if (argc != 2) {
        cout << "Usage: " << argv[0]  << " <oggDir> " << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];	

    if( !isDir(input) ) {
        cerr << "NOT directory: " << input << endl;
        return EXIT_FAILURE;
    }


// mkdir
    string dir = input + string("_wav");
    if( !isDir(dir) ) {
        bool ret1 = makeDir(dir, 0777);
        if(ret1){
            cout << "mkdir: " << dir << endl;
        }else{
            cerr << "mkdir faild: " << dir << endl;
            return EXIT_FAILURE;
        }
    }

// get list
   string path(input);
    string ext1("ogg");
    string ext2("oga");
    std::vector<std::string> vec;
    string error; 
    bool ret2 = getFileListExt2(path, ext1, ext2, vec, error );
    if(!ret2){
        cout << error << endl;
    }

    for( string file: vec) {
        cout << file << endl;
        string wav =  add_wav_ext(file);
        string in = makePath(input, file);
        string out = makePath(dir, wav);
        ogg_to_wav(in, out);
    } // for

	return EXIT_SUCCESS;
}
