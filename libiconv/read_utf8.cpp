/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */

// read UTF8 file


#include <iostream>
#include <string>

#include "TextReader.hpp"

#include "parse_filename.hpp"

using namespace std;


/*
 * main
 */
int main(int argc, char** argv)
{

    const int BUF_SIZE  = 1024;
    char* buf = new char[BUF_SIZE];

    TextReader reader;

    string input;
    int flag_debug = 0;

    if (argc == 3) {
        input = argv[1];
        flag_debug = atoi(argv[2]);
    }else if (argc == 2) {
        input = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <textFile> [debug] "  << endl;
        return EXIT_FAILURE;
    }


    try {

        int ret1 = reader.open(input);
        if(ret1 != 0){
            cerr << "[FAILED] Could not open " << input << endl;
            return EXIT_FAILURE;
        }

        int line_count = 0;
        bool flag_loop = true;

        while(flag_loop){

            line_count++;
            int len = reader.getLine(buf, BUF_SIZE);
            if(len == TEXT_READER_EOF){
                flag_loop = false;
                break;
            }

            cout <<  line_count << " : " << buf << endl;

        } // while

        reader.close();

    } catch (char *e) {
            cerr << "EXCEPTION : " << e << endl;
                return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

