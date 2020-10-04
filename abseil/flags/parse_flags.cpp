/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// parse comand line flags

// macOS
 // g++ parse_flags.cpp   -std=c++11  -framework CoreServices  `pkg-config --cflags --libs abseil_flags` 

// reference : https://abseil.io/docs/cpp/guides/flags

#include <iostream>
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/time/time.h"

using namespace std;


// Defining Flags
ABSL_FLAG(bool, big_menu, false,
          "Include 'advanced' options in the menu listing");
ABSL_FLAG(std::string, output_dir, "foo/bar/baz/", "output file dir");
ABSL_FLAG(std::vector<std::string>, languages,
          std::vector<std::string>({"english", "french", "german"}),
          "comma-separated list of languages to offer in the 'lang' menu");
ABSL_FLAG(absl::Duration, timeout, absl::Seconds(30), "Default RPC deadline");



/**
 * main
 */
int main(int argc, char* argv[])
{

// Parsing Flags
    absl::ParseCommandLine(argc, argv);

// Read the flag
    bool big = absl::GetFlag(FLAGS_big_menu);
    string dir = absl::GetFlag(FLAGS_output_dir);
    vector<string> languages = absl::GetFlag(FLAGS_languages);
    absl::Duration d = absl::GetFlag(FLAGS_timeout);

    cout  << std::boolalpha << "big menu: " << big << endl;
    cout << "output dir: " << dir << endl;
    cout << "timeout: " << d << endl;

    cout << "languages: " ;
    for(string x: languages){
        cout << x << ", ";
    }
    cout << endl;

    return 0;
}


// % ./a.out
// big menu: false
// output dir: foo/bar/baz/
// timeout: 30s
// languages: english, french, german, 


// % ./a.out -big_menu -output_dir abc -timeout 10s  -languages jpanese,chinese 
// big menu: true
// output dir: abc
// timeout: 10s
// languages: jpanese, chinese, 

