smtp - libcurl
===============

libcurl Sample <br/>
send mail to SMTP server <br/>


### sample codes
- smtp-auth.c <br/>
 send mail to SMTP server with TLS and AUTH <br/>
- smtp-gmail.c <br/>
send mail to Gmail SMTP server  <br/>
- test_mail_json.c <br/>
test for getGmailParam <br/>


build code <br/>
% gcc smtp/smtp-tls-auth.c `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs json-c` <br/> 

run code <br/>
% ./a.out

display as below <br/>
> 220 VirtualBox ESMTP Postfix (Ubuntu) 
> 235 2.7.0 Authentication successful 


### Reference <br/>
- https://curl.haxx.se/libcurl/c/

