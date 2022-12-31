/**
 *   posix-stream_descriptor2.cpp
 * 2022-06-01 K.OHWADA
 */

// standard input/output asynchronously with Boost.Asio
// require c++14
// https://amedama1x1.hatenablog.com/entry/2014/07/08/223531

#include <chrono>
#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/streambuf.hpp>
#include <unistd.h>


/**
 *   main
 */
int main()
{
    namespace asio = boost::asio;

    asio::io_service io_service{};

    auto input = asio::posix::stream_descriptor{io_service, ::dup(STDIN_FILENO)};

    asio::spawn(io_service, [&](auto yield) {
        asio::steady_timer timer{io_service};
        while (not io_service.stopped()) {
            timer.expires_from_now(std::chrono::seconds{1});
            timer.async_wait(yield);
            std::cout << "ticktack..." << std::endl;
        }
    });

    asio::streambuf input_buffer{};
    asio::async_read_until(input, input_buffer, '\n', [&](auto& error, auto bytes_transferred) {
        std::cout << "input data: " << &input_buffer << std::endl;
        io_service.stop();
    });

    io_service.run();
}