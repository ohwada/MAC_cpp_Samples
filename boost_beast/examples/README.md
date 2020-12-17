examples : boost_beast
===============

beast examples <br/>

The files in this directory are modified versions of  downloaded from below <br/>
- https://github.com/boostorg/beast/blob/develop/example <br/>

### sample code
- http_client_sync.cpp <br/>
HTTP client, synchronous <br/>
- http_client_sync_ssl.cpp <br/>
HTTP SSL client, synchronous <br/>

- http_server_sync.cpp <br
HTTP server, synchronous <br/>
- http_server_sync_ssl.cpp <br/
HTTP SSL server, synchronous <br/>

- http_client_async.cpp <br/>
// HTTP client, asynchronous <br/>
- http_client_async_ssl.cpp <br/>
TODO: build error <br/>

- http_server_async.cpp <br/>
HTTP server, asynchronous <br/>
- http_server_async_ssl.cpp <br/>
HTTP SSL server, asynchronous <br/>

- http_client_coro.cpp <br/>
HTTP client, coroutine <br/>
- http_client_coro_ssl.cpp <br/>
HTTP SSL client, coroutine <br/>

- http_server_stackless.cpp <br/>
HTTP server, stackless coroutine <br/>


### build sample code
g++ http_client_sync.cpp -std=c++11 `pkg-config --cflags --libs boost` 

### run sample code
Usage: ./a.out [host] [port] [target] [HTTP version: 1.0 or 1.1(default)] <br/>

display as below <br/>
> connect: www.example.com : 80 <br/>
> \<title\> Example Domain \</title\> <br/>


### Reference <br/>
- https://www.boost.org/

