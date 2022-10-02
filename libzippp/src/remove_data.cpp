// Remove data from an archive
// https://github.com/ctabin/libzippp

#include <iostream>
#include <string>
#include "libzippp.h"

// TODO:
// return -4
//  LIBZIPPP_ERROR_INVALID_PARAMETER -4


using namespace std;
using namespace libzippp;

int main(int argc, char** argv) 
{
  ZipArchive zf("sample1.zip");
  zf.open(ZipArchive::Write);
  int ret1 = zf.deleteEntry("helloworld.txt");
    cout << "ret1: " << ret1 << endl;
  int ret2 = zf.deleteEntry("folder/subdir/");
    cout << "ret2: " << ret2 << endl;
  zf.close();
  
  return 0;
}
