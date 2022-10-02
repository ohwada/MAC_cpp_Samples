/**
 * file_read.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>

using namespace std;
namespace io = boost::iostreams;


/**
 * main
 */
int main(int argc, char* argv[])
{
    string file("data/sample1.txt");

    if(argc == 2) {
      	file = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file] " << endl;
    }

    cout << file << endl;

    auto input = io::mapped_file_source(file);

    cout << input.data() << endl;

    return 0;
}

> The quick brown fox jumps over the lazy dog
