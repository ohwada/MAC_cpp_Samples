 libmicrohttpd
===============

libmicrohttpd sample <br/>

libmicrohttpd : <br/>
a small C library that is supposed to make it easy to run an HTTP server <br/>
https://www.gnu.org/software/libmicrohttpd/ <br/>

###  install libmicrohttpd
    see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libmicrohttpd/setup.md <br/>

## sample code
- http_server.c <br/>
HTTP Server <br/>
- https_server.c <br/>
HTTPS Server <br/>
- version.c <br/>
- display version <br/>
 

build sample code<br/>
% gcc src/http_server.c `pkg-config --cflags --libs libmicrohttpd`  <br/>

run sample code <br/>
Usage: ./a.out [port]  <br/>

access localhost:8080 by web brawser <br/>
chrome_http_server.png


### Reference <br/>
- https://www.gnu.org/software/libmicrohttpd/manual/html_node/index.html
- https://github.com/rboulton/libmicrohttpd

