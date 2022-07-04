/**
 * conv_ogg_to_wav.cpp
 * 2020-03-01 K.OHWADA
 */

// TODO :
// cannot be converted correctly　the following files 
// can create file, but strange sound
// bell.oga
// message.oga
// service-login.oga


#include <iostream>
#include <string> 
#include"ogg_to_wav.hpp"
#include"parse_filename.hpp"


using namespace std;

void print_result( int ret, string input, string output);


/**
 * main
 */
int main(int argc, char** argv) 
{

    if (argc != 2) {
        cout << "Usage: " << argv[0]  << " <oggFile> " << endl;
        return EXIT_FAILURE;
    }

   char* input = argv[1];	

if( isDir(input) ) {
    string path(input);
    string ext1("ogg");
    string ext2("oga");
string dir = input + string("_wav");
 mkdir( (char *)dir.c_str(), 0777);
    std::vector<std::string> vec;
    string error; 
    bool ret = getFileListExt2(path, ext1, ext2, vec, error );
    if(!ret){
        cout << error << endl;
    }

    for( string file: vec) {
        string wav = addExtWav(file);
        string in = makePath(input, file);
        string out = makePath(dir, wav);
        int ret1 =convOggToWav(in, out);
        print_result( ret1, in, out);
    } // for

} else if (isFile(input) ) {
    string fname = getFileNameWithExt(input);
    string output = addExtWav(fname);
    int ret2 =convOggToWav(input, output);
    print_result( ret2, input, output);
}
	return EXIT_SUCCESS;
}

/**
 * print_result
 */
void print_result( int ret, string input, string output)
{
    if(ret == DECODE_SUCCESS){
        cout << "saved: " << output << endl;
    } else if(ret == DECODE_ERR_INPUT) {
        cout << "fopen Faild: " << input << endl;
    } else if(ret == DECODE_ERR_OUTPUT) {
        cout << "fopen Faild: " << output << endl;
    } else if( ret == DECODE_ERR_FORMAT) {
        cout << "NOT ogg format: " << input << endl;
    } else if( ret == DECODE_ERR_WRITE) {
        cout << "write Faild: " << output << endl;
    }
}

