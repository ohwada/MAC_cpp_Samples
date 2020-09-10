/**
 * gflags sample
 * 2020-03-01 K.OHWADA
 */

// parse commandline flags
// append text to text file
// reference : https://qiita.com/xeno14/items/bd8991b626b17e071c0a

#include <iostream>
#include <fstream>
#include <string>
#include <gflags/gflags.h>

using namespace std;


// Flag definitions
DEFINE_string(filename, "", "file name to write or read");
DEFINE_bool(read, false, "read file and show text");
DEFINE_string(append_text, "", "append text to the file");


/**
 * read_text
 * output the contents of the file to standard output
 */
int read_text(const string& filename) {
  std::ifstream ifs(filename.c_str());
  if (!ifs) {
    std::cerr << "Failed to open " << filename << std::endl;
    return 1;
  }
  string buf;
  while (std::getline(ifs, buf)) {
    std::cout << buf << std::endl;
  }
  return 0;
}


/**
 * append_text
 * append a string to the file
 */
int append_text(const string& filename, const string& append_text) {
  std::ofstream ofs(filename.c_str(), std::ios::app);
  if (!ofs) {
    std::cerr << "Failed to open " << filename << std::endl;
    return 1;
  }
  ofs << append_text << std::endl;
  return 0;
}



/**
 * usage
 */
int usage(string argv0 )
{
    cout << "Usage: " << argv0 << " --filename <textFile> [ --append_text <yourText> ] [ -- read ] " << endl;
    cout << "Help: " << argv0 << " --help" << endl;
    return 2;
}



/**
 * main
 */
int main(int argc, char* argv[]) 
{

  // remove the flags defined by gflags
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  int return_value = 0;

    string filename = FLAGS_filename;
    bool read = FLAGS_read;
    string text = FLAGS_append_text;

  // processing for each flag
    if ( filename.empty() ) {
        return_value = usage( argv[0] );
   } else if ( read ) {
        return_value = read_text(filename);
    } else if ( !text.empty()) {
        return_value = append_text(filename, text);
    } else {
        return_value = usage( argv[0] );
    }

  return return_value;
}

