/**
 *   posix-stream_descriptor1.cpp
 * 2022-06-01 K.OHWADA
 */

// Output what is input
// https://blog.myon.info/entry/2018/10/14/boost-asio-posix-stream_descriptor/
 
#include <iostream>
#include <boost/asio.hpp>

extern "C" {
#include <unistd.h>
}


/**
 *   main
 */
auto main() -> int {
  boost::asio::io_context ctx{};

  boost::asio::posix::stream_descriptor stream_in{ctx, ::dup(STDIN_FILENO)};
  boost::asio::posix::stream_descriptor stream_out{ctx, ::dup(STDOUT_FILENO)};

  boost::asio::streambuf buffer{};
  boost::system::error_code error{};

  while (boost::asio::read(stream_in, buffer, boost::asio::transfer_at_least(1), error)) {
    boost::asio::write(stream_out, buffer);
  }

  if (error != boost::asio::error::eof) {
    std::cerr << error.message() << std::endl;
    return 1;
  }
}


// % echo hello | bin/stream1
// hello

