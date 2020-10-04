/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// return status code
// smple for absl::Status
// https://abseil.io/docs/cpp/guides/status

#include <iostream>
#include <fstream>
#include "absl/status/status.h"

using namespace std;


/**
 * Open
 */
absl::Status Open(string filename, string mode) 
{

    if (mode != "r"){
        string err1 = "bad mode: " + mode;
        return absl::InvalidArgumentError( err1 );
    }

    ifstream ifs(filename);
    bool is_good = ifs.good();

  if ( ! is_good) {
        string err2 = filename + " is missing";
        return absl::NotFoundError( err2 );
    }

    return absl::OkStatus(); 
}


/**
 * main
 */
int main(int argc, char* argv[])
{

    if(argc != 3){
        cout << "Usage: " << argv[0] << " <filename> <mode> " << endl;
        return 1;
    }

    string filename = argv[1];
    string mode = argv[2];

    absl::Status st = Open(filename, mode);
    if( st.ok() ){
        cout << "Ok" << endl;
    } else {
        cout << st << endl;
    }

    return 0;
}

// % ./a.out
// Usage: ./a.out \<filename\> \<mode\> 
// % ./a.out abc w 
// INVALID_ARGUMENT: bad mode: w
// % ./a.out abc r 
// NOT_FOUND: abc is missing 
// % ./a.out status.cpp r 
// Ok 

