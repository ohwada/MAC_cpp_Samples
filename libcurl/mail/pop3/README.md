pop3 - libcurl
===============

libcurl Sample <br/>
recieve mail frm POP3 or IMAP server <br/>


### sample codes
- pop3-ssl.c <br/>
recieve mail from POP3 server with ssl <br/>
- imap-ssl.c <br/>
get list from IMAP server with SSL <br/>
- test_mail_json.c <br/>
test for getGmailParam <br/>


build code <br/>
% gcc pop3/pop3-ssl.c `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs json-c` -o pop3_ssl <br/> 

% gcc pop3/pop3-ssl.c `pkg-config --cflags --libs json-c` -lcurl <br/>  

run code <br/>
% ./a.out

display as below <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/

