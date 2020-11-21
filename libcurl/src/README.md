src - libcurl
===============

libcurl Sample <br/>
get web page from http server <br/>


### sample codes
- http_client.c <br/>
 very simple HTTP Client <br/>
Get from example.com <br/>
- https_client.c <br/>
Simple HTTPS Client <client>
Get web from example.com

- http_post.c <br/>
// simple HTTP POST using the easy interface <br/>
// post to postman-echo.com <br/>
- http_to_file.c <br/>
get HTTP page, save into a local file <br/>
- http_to_memory.c <br/>
get HTTP page, copy into memory <br/>
- http_post_to_file.c <br/>
post to postman echo server,  save response to local file <br/>
- http_post_to_memory.c <br/>
post to postman echo server,  copy response to memory <br/>
- http_customheader.c <br/>
http request to postman echo server with custom headers <br/>
- verson.c <br/>
display curl version <br/>


build code <br/>
% gcc src/http_client.c `pkg-config --cflags --libs libcurl` <br/>  

run code <br/>
% a.out

display as below <br/>
> \<title\>Example Domain\</title\> <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/

