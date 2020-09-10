/**
 * glog sample
 * 2020-03-01 K.OHWADA
 */

// write log to file
// reference : http://etc2myday.jugem.jp/?eid=219


#include <gflags/gflags.h>
#include <glog/logging.h>


/**
 * main
 */
int main(int argc, char** argv)
{

// dont forget make this directory 
    FLAGS_log_dir = "./log";

    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "INFO";
    LOG(WARNING) << "WARNING";
    LOG(ERROR) << "ERROR";

// it will ABORT、if run this line
// LOG(FATAL) << "FATAL";

    return 0;
}

