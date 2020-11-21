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
- http_client.c <br/>
 very simple HTTP Client <br/>
- https_client.c <br/>
Simple HTTPS Client <client>
- http_post.c <br/>
simple HTTP Post <br/>


build code <br/>
% gcc src/http_client.c `pkg-config --cflags --libs libcurl` <br/>  

run code <br/>
Usage: ./a.out  [host] <br/>

display as below<br/>
> \<title\> Example Domain \</title\>

### sample codes for mail
- smtp-auth.c <br/>
 send mail to smtp server with TLS and AUTH <br/>
- pop3-ssl.c <br/>
recieve mail from pop3 server with ssl <br/>
- smtp-gmail-xoauth.c <br/>
send mail to Gmail SMTP server with xoauth2 <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/

