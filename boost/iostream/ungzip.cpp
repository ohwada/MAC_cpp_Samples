/**
 * ungzip.cpp
 * 2022-06-01 K.OHWADA
 */


// TODO:
// if there is a space in the decompressed sentence,
// output is truncated there,
// therefore decompress first word only


// reference : https://azsprinkle.hatenablog.com/entry/2012/06/17/213507

#include <iostream>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include "parse_filename.hpp"

using namespace std;
namespace io = boost::iostreams;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string infile("data/sample2.txt.gz");

  if(argc == 2) {
      	infile = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file] " << endl;
    }

    string fname = getFileNameWithoutExt(infile);
    string ext1 = getFileNameExt(infile);
    string ext2 = getFileNameWithoutExt(ext1); 

    string outfile = fname + ("_out.") + ext2;

    cout << infile << endl;
    cout << outfile << endl;


// read data from file and gzip decompress
    io::filtering_istream in;
    in.push(io::gzip_decompressor());
    in.push(io::file_descriptor_source(infile));

    string str;
    in >> std::noskipws >> str;

    cout << std::noskipws << str << endl;

   std::ofstream fout(outfile); 

   fout << std::noskipws << str;

    fout.close();

    return 0;
}
