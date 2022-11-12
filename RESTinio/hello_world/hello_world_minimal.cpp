/**
 * hello_world_minimal.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/Stiffstream/restinio/tree/master/dev/sample/hello_world_minimal

#include <restinio/all.hpp>

using namespace std;


/**
 * main
 */
int main()
{
	unsigned short PORT = 8080;

	cout << "listen port: " << PORT << endl;

	restinio::run(
		restinio::on_this_thread<>()
			.port(PORT)
			.address("localhost")
			.request_handler([](auto req) {
				return req->create_response().set_body("Hello, World minimal").done();
			}));

	return 0;
}
