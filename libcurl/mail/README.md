mail - libcurl
===============

libcurl Sample <br/>
send recieve mail <br/>


### ssmtp
- smtp-tls-auth.c 
 send mail to SMTP server <br/>

build code <br/>
% gcc smtp/smtp-tls-auth.c `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs json-c` <br/>  

run code <br/>
% ./a.out

display as below <br/>
> 220 VirtualBox ESMTP Postfix (Ubuntu) 
> 235 2.7.0 Authentication successful 


### pop3
recieve mail from POP3 or IMAP server <br/>
- pop3-ssl.c <br/>
recieve mail from POP3 server  <br/>
- imap-ssl.c <br/>
get list from IMAP server  <br/>

### xoauth
send mail to Gmail server with xoauth2 <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/
