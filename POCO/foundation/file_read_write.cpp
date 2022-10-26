/**
 *  file_read_write.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include "poco_file_stream.hpp"


using namespace std;


/**
 *  main
 */
int main()
{

    string inpath1("data/yellow_submarine.txt");
    string outpath1("out/test.txt");

    string inpath2("data/baboon.png");
    string outpath2("out/test.png");

    string text = file_text_read(inpath1);

    // cout << text << endl;
    cout << "text size: " << text.size() << endl;

    file_text_write(outpath1, text);

    cout << "saved: " << outpath1 << endl;

    size_t read_size;
    string data = file_binary_read(inpath2, read_size);

    cout << "read size: " << read_size << endl;

    // cout << "data size: " << data.size() << endl;

    file_binary_write(outpath2, data, read_size);

    cout << "saved: " << outpath2 << endl;

    return 0;
}
