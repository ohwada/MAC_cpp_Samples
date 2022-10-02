
// Progression of committed changes
// https://github.com/ctabin/libzippp


#include <iostream>
#include <string>
#include "libzippp.h"

using namespace std;
using namespace libzippp;

class SimpleProgressListener : public ZipProgressListener {
public:
    SimpleProgressListener(void) {}
    virtual ~SimpleProgressListener(void) {}

    void progression(double p) {
        cout << "-- Progression: " << p << endl;
    }
};

int main(int argc, char** argv) {
  ZipArchive zf("archive.zip");
  /* add/modify/delete entries in the archive */

  //register the listener
  SimpleProgressListener spl;
  zf.addProgressListener(&spl);

  //adjust how often the listener will be invoked
  zf.setProgressPrecision(0.1);

  //listener will be invoked
  zf.close();

  return 0;
}
