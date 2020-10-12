libcurl
===============

libcurl Sample <br/>
get web page from http server <br/>

libcurl : <br/>
the multiprotocol file transfer library <br/> 
https://curl.haxx.se/libcurl/ <br/>


###  install libcurl
see setup
% brew install curl <br/>
https://formulae.brew.sh/formula/curl <br/>

setup for pkgconfig
% ln -s /usr/local/opt/curl/lib/pkgconfig/libcurl.pc /usr/local/lib/pkgconfig/libcurl.pc

confirm for pkgconfig
% pkg-config --cflags --libs libcurl
> -I/usr/local/Cellar/curl/7.72.0/include 
> -L/usr/local/Cellar/curl/7.72.0/lib -lcurl

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
- verson.c <br/>
display curl version <br/>


build code <br/>
% gcc src/simple.c `pkg-config --cflags --libs libcurl` <br/>  

run code <br/>
% a.out > simple_result.html

created "simple_result.html"

### sample codes for mail
- smtp-auth.c <br/>
 send mail to smtp server with TLS and AUTH <br/>
- pop3-ssl.c <br/>
recieve mail from pop3 server with ssl <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/

