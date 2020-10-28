libcurl
===============

libcurl Sample <br/>
get web page from http server <br/>

libcurl : <br/>
the multiprotocol file transfer library <br/> 
https://curl.haxx.se/libcurl/ <br/>


###  install libcurl and setup
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libcurl/setup <br/>


### sample codes
get web page from http server <br/>
- simpe.c <br/>
 very simple HTTP GET from example.com <br/>
- https.c <br/>
get web page html from google.com <br/>


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
- smtp-gmail-xoauth.c <br/>
send mail to Gmail SMTP server with xoauth2 <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/

