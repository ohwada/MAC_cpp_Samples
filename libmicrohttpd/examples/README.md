examples - libmicrohttpd
===============

libmicrohttpd examples <br/>

## example code
- minimal_example.c <br/>
minimal example for how to use libmicrohttpd <br/>
- minimal_example_comet.c <br/>
generate an infinite stream with libmicrohttpd <br/>
- querystring_example.c <br/>
get the query string from libmicrohttpd <br/>

- post_example.c <br/>
POST requests using libmicrohttpd <br/>
- refuse_post_example.c <br/>
refuse a POST request properly <br/>

- fileserver_example.c <br/>
libmicrohttpd to serve files <br/>
- fileserver_example_dirs.c <br/>
libmicrohttpd to serve files (with directory support) <br/>

- authorization_example.c <br/>
libmicrohttpd with HTTP authentication <br/>
- digest_auth_example.c <br/>
digest auth with libmicrohttpd <br/>

- display pkg_version.c <br/>
display package version <br/>


build sample code<br/>
% gcc minimal_example.c `pkg-config --cflags --libs libmicrohttpd`  <br/>

run sample code <br/>
Usage: ./a.out  [port] <br/>

access localhost:8080 by web brawser <br/>
chrome_minimal_example.png
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libmicrohttpd/screenshot/chrome_minimal_example.png" width="300" /> <br/>


### Reference <br/>
- https://www.gnu.org/software/libmicrohttpd/manual/html_node/index.html


