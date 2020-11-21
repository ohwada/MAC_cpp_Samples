/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// post large data to "httpbin.org"

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/benchmark.cc


#include <iostream>
#include <chrono>
#include "httplib.h"


using namespace std;


/**
 * struct StopWatch
 */
struct StopWatch {
  StopWatch(const string &label) : label_(label) {
    start_ = chrono::system_clock::now();
  }
  ~StopWatch() {
    auto end = chrono::system_clock::now();
    auto diff = end - start_;
    auto count = chrono::duration_cast<chrono::milliseconds>(diff).count();
    cout << label_ << ": " << count << " millisec." << endl;
  }
  string label_;
  chrono::system_clock::time_point start_;
};
// struct StopWatch


/**
 * main
 */
int main(void) 
{

// A simple HTTP Request & Response Service.
const std::string HOST("httpbin.org");

const int PORT = 80;


// post data
  string body(1024 * 5, 'a');

  httplib::Client cli(HOST, PORT);

  for (int i = 0; i < 3; i++) {
    StopWatch sw(to_string(i).c_str());
    auto res = cli.Post("/post", body, "application/octet-stream");
    assert(res->status == 200);
  }

    return EXIT_SUCCESS;
}


// 0: 673 millisec.
// 1: 581 millisec.
// 2: 741 millisec.

