src - libcurl
===============

libcurl Sample <br/>
get web page from http server <br/>


### sample codes
- simpe.c <br/>
 very simple HTTP GET from example.com <br/>
- https.c <br/>
get web page html from google.com <br/>
- http-post.c <br/>
 post to postman echo server <br/>
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
% gcc src/simple.c `pkg-config --cflags --libs libcurl` <br/>  

run code <br/>
% a.out > simple_result.html

created "simple_result.html"

### Reference <br/>
- https://curl.haxx.se/libcurl/c/
