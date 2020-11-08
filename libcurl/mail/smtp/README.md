smtp - libcurl
===============

libcurl Sample <br/>
send mail to SMTP server <br/>


### sample codes
- smtp_tls_auth.c <br/>
 send mail to SMTP server with TLS and AUTH <br/>
- smtp_gmail.c <br/>
send mail to Gmail SMTP server  <br/>
- test_mail_json.c <br/>
test for getGmailParam <br/>


build code <br/>
% gcc smtp/smtp_tls_auth.c `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs json-c` <br/> 

run code <br/>
% ./a.out

display as below <br/>
> 220 VirtualBox ESMTP Postfix (Ubuntu) 
> 235 2.7.0 Authentication successful 

### Document <br/>
- https://ken-ohwada.hatenadiary.org/entry/2020/11/08/115532

### Reference <br/>
- https://curl.haxx.se/libcurl/c/

