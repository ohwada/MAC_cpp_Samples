/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// SSE (Server Send Event) server

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/ssesvr.cc

//
//  sse.cc
//
//  Copyright (c) 2020 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include "httplib.h"

using namespace httplib;
using namespace std;



/**
 * class EventDispatcher
 */
class EventDispatcher {
public:

// constractor
  EventDispatcher() {
    id_ = 0;
    cid_ = -1;
  }

// wait_event
  void wait_event(DataSink *sink) {
    unique_lock<mutex> lk(m_);
    int id = id_;
    cv_.wait(lk, [&] { return cid_ == id; });
    if (sink->is_writable()) { sink->write(message_.data(), message_.size()); }
  }

// send_event
  void send_event(const string &message) {
    lock_guard<mutex> lk(m_);
    cid_ = id_++;
    message_ = message;
    cv_.notify_all();
  }

private:
  mutex m_;
  condition_variable cv_;
  atomic_int id_;
  atomic_int cid_;
  string message_;
};
// class EventDispatcher


/**
 * html
 */
const auto html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>SSE demo</title>
</head>
<body>
<script>
const ev1 = new EventSource("event1");
ev1.onmessage = function(e) {
  console.log('ev1', e.data);
}
const ev2 = new EventSource("event2");
ev2.onmessage = function(e) {
  console.log('ev2', e.data);
}
</script>
</body>
</html>
)";
// html


/**
 * main
 */
int main(void) 
{

    const char *HOST = "localhost";

    const int PORT = 1234;

  EventDispatcher ed;

  Server svr;

// root "/"
  svr.Get("/", [&](const Request & /*req*/, Response &res) {
    res.set_content(html, "text/html");
  });

// event1
  svr.Get("/event1", [&](const Request & /*req*/, Response &res) {
    cout << "connected to event1..." << endl;
    res.set_chunked_content_provider("text/event-stream",
                                     [&](size_t /*offset*/, DataSink &sink) {
                                       ed.wait_event(&sink);
                                       return true;
                                     });
  });

// event2
  svr.Get("/event2", [&](const Request & /*req*/, Response &res) {
    cout << "connected to event2..." << endl;
    res.set_chunked_content_provider("text/event-stream",
                                     [&](size_t /*offset*/, DataSink &sink) {
                                       ed.wait_event(&sink);
                                       return true;
                                     });
  });

  thread t([&] {
    int id = 0;
    while (true) {
      this_thread::sleep_for(chrono::seconds(1));
      cout << "send event: " << id << std::endl;
      std::stringstream ss;
      ss << "data: " << id << "\n\n";
      ed.send_event(ss.str());
      id++;
    }
  });

  svr.listen(HOST, PORT);

    return EXIT_SUCCESS;
}

