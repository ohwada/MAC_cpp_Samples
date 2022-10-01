/**
 * httpd_file_browser.cpp
 * 2022-06-01 K.OHWADA
 */

// change log
// change "directory_listing.h" to directory_listing.hpp

// oroginal https://github.com/storozhilov/httpxx/blob/master/examples/httpd_file_browser.cpp
// HTTPXX - Example of use. Based on ASIO library.
// 'libboost-dev' and 'libasio-dev' packages have to be installed.
//
// Note: Does not restrict maximum service duration for slow client.

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <httpxx.h>

// #include "directory_listing.h"
#include "directory_listing.hpp"

using namespace boost::asio;
using namespace httpxx;

// image size is about 1MB
// const std::size_t BufferSize = 4096U;  // 4 KB
const std::size_t BufferSize = 1024000U;  // 1 MB

const std::size_t EnvelopePartSize = 1024U; // 1KB

const short PORT = 9999;

io_service service;
ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), PORT));

// warning: auto_ptr is deprecated
std::auto_ptr<ip::tcp::socket> accept_socket;

/**
 * class HttpTask
 */
class HttpTask : public boost::enable_shared_from_this<HttpTask>, boost::noncopyable
{
public:

// warning: auto_ptr is deprecated
	HttpTask(std::auto_ptr<ip::tcp::socket>& s) :

		_socket(s),
		_buffer(),
		_request_parser(24U, 1024U, 24U),
		_packet()
	{}

	~HttpTask()
	{
		_socket->close();
		std::clog << "Serving of client has been completed" << std::endl;
	}

	void async_execute()
	{
		_socket->async_receive(boost::asio::buffer(_buffer), boost::bind(&HttpTask::on_receive,
					shared_from_this(), _1, _2));
	}
private:
	void on_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
	{

//std::cout << _buffer << std::endl;

		if (error) {
			std::cerr << "Data retrival error: " << error.message() << std::endl;
			return;
		}
		std::clog << bytes_transferred << " bytes have been received from peer" << std::endl;

		// Reading and parsing data until complete HTTP-response has been received
		std::ostream dummy(0);
		try {
			std::pair<bool, size_t> res = _request_parser.parse(_buffer, bytes_transferred, dummy);
			if (!res.first) {
				_socket->async_receive(boost::asio::buffer(_buffer),
						boost::bind(&HttpTask::on_receive, shared_from_this(), _1, _2));
				return;
			}
		} catch (std::exception& e) {
			std::cerr << "HTTP-request parsing error: " << e.what() << std::endl;
			return;
		} catch (...) {
			std::cerr << "HTTP-request parsing unknown error" << std::endl;
			return;
		}

		// Composing and sending response
		std::ostringstream body;
		std::string mime;

		// list_directory(Uri(_request_parser.secondToken()).path(), body);
		list_directory(Uri(_request_parser.secondToken()).path(), body, mime);

		if (body.str().size() > sizeof(_buffer) - EnvelopePartSize) {
			std::cerr << "No enough space for HTTP-response body in I/O-buffer" << std::endl;
			return;
		}

		body.str().copy(_buffer + EnvelopePartSize, body.str().size());
		Headers headers;

		// headers.add("Content-Type", "text/html");
		headers.add("Content-Type", mime);

		headers.add("Connection", "close");

// TODO
// 404 (File)Not Found

		MessageComposer 
		responseComposer(_request_parser.thirdToken(), "200", "OK");
		try {
			_packet = responseComposer.prependEnvelope(_buffer,
					EnvelopePartSize, headers, body.str().size());
		} catch (std::exception& e) {
			std::cerr << "HTTP-response composition error: " << e.what() << std::endl;
			return;
		} catch (...) {
			std::cerr << "HTTP-response composition unknown error" << std::endl;
			return;
		}
		_socket->async_send(boost::asio::buffer(_packet.first, _packet.second),
				boost::bind(&HttpTask::on_send, shared_from_this(), _1, _2));
	}

	void on_send(const boost::system::error_code& error, std::size_t bytes_transferred)
	{
		if (error) {
			std::cerr << "Data sending error: " << error.message() << std::endl;
			return;
		}
		std::clog << bytes_transferred << " bytes have been sent to peer" << std::endl;
		_packet.first = static_cast<const char *>(_packet.first) + bytes_transferred;
		_packet.second -= bytes_transferred;
		if (_packet.second <= 0U) {
			return;
		}
		_socket->async_send(boost::asio::buffer(_packet.first, _packet.second),
				boost::bind(&HttpTask::on_send, shared_from_this(), _1, _2));
	}

// warning: auto_ptr is deprecated
	std::auto_ptr<ip::tcp::socket> _socket;

	char _buffer[BufferSize];
	MessageParser _request_parser;
	MessageComposer::Packet _packet;
};

void accept_handler(const std::error_code& error)
{
	if (error) {
		std::cerr << "Accepting connection error: " << error.message() << std::endl;
		return;
	}
	std::clog << "Connection accepted" << std::endl;
	boost::shared_ptr<HttpTask> task(new HttpTask(accept_socket));
	accept_socket.reset(new ip::tcp::socket(service));
	acceptor.async_accept(*accept_socket, accept_handler);
	task->async_execute();
}

using namespace std;


/**
 * main
 */
int main(int argc, char * argv[])
{
	acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	accept_socket.reset(new ip::tcp::socket(service));
	acceptor.async_accept(*accept_socket, accept_handler);

	cout << "listen port " << PORT << endl;

	service.run();

	return 0;
}
