// Add data to an archive
// https://github.com/ctabin/libzippp


#include <iostream>
#include <string>
#include "libzippp.h"

using namespace std;
using namespace libzippp;


int main(int argc, char** argv) 
{
    string file("data/sample1.zip");

  ZipArchive zf(file);
  zf.open(ZipArchive::Write);

  // Advanced usage : change the compression method. Default is DEFLATE.
#ifdef LIBZIPPP_USE_BZIP2
    zf.setCompressionMethod(entry, CompressionMethod::BZIP2);
#endif

  zf.addEntry("folder/subdir/");

  const char* textData = "Hello,World!";
  zf.addData("helloworld.txt", textData, 12);

  zf.close();

  return 0;
}
