/**
 * gzip.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://azsprinkle.hatenablog.com/entry/2012/06/17/213507

#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include "parse_filename.hpp"

using namespace std;
namespace io = boost::iostreams;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string infile("data/sample1.txt");

  if(argc == 2) {
      	infile = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file] " << endl;
    }

    std::string fname = getFileNameWithExt(infile);

    string outfile = fname + string(".gz");

    cout << infile << endl;
    cout << outfile << endl;

    auto input = io::mapped_file_source(infile);

    // gzip data and write to file
    io::filtering_ostream out;
    out.push(io::gzip_compressor());
    out.push(io::file_descriptor_sink(outfile));
    out << input.data();
    io::close(out); 

    return 0;
}
