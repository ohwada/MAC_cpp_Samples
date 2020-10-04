/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// validating Flag Values

 // g++ validate_flag_value.cpp  -std=c++11  -framework CoreServices  `pkg-config --cflags --libs abseil_flags` 

// reference : https://abseil.io/docs/cpp/guides/flags

#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/marshalling.h"
#include "absl/strings/string_view.h"

using namespace std;


/**
 * struct PortNumber
 */
struct PortNumber {
  explicit PortNumber(int p = 0) : port(p) {}

  int port;  // Valid range is [0..32767]
};


// Returns a textual flag value corresponding to the PortNumber `p`.
std::string AbslUnparseFlag(PortNumber p) {
  // Delegate to the usual unparsing for int.
  return absl::UnparseFlag(p.port);
}


// Parses a PortNumber from the command line flag value `text`.
// Returns true and sets `*p` on success; returns false and sets `*error`
// on failure.
bool AbslParseFlag(absl::string_view text, PortNumber* p, std::string* error) {
  // Convert from text to int using the int-flag parser.
  if (!absl::ParseFlag(text, &p->port, error)) {
    return false;
  }
  if (p->port < 0 || p->port > 32767) {
    *error = "not in range [0,32767]";
    return false;
  }
  return true;
}


// Defining Flags
ABSL_FLAG(PortNumber, port, PortNumber(0), "What port to listen on");



/**
 * main
 */
int main(int argc, char* argv[])
{

// Parsing Flags
    absl::ParseCommandLine(argc, argv);

// Read the flag
    struct PortNumber p;
    p  = absl::GetFlag(FLAGS_port);

    cout << "port: " << p.port << endl;

    return 0;
}


// % ./a.out
// port: 0


// % ./a.out -port 100
// port: 100


// % ./a.out -port 32768
// ERROR: Illegal value '32768' specified for flag 'port'; not in range [0,32767]



