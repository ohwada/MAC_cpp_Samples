pop3 - vmail
===============

vmail Sample <br/>
recieve mail from POP3 (or MAP) server <br/>

### sample code 
- pop3_ssl.cpp <br/>
recievw mail from POP3 (or MAP) server with SSL <br/>
- pop3_userinput.cpp <br/>
user input username and password interactive
- pop3_gmail.cpp <br/>
recive mail from Gmail POP3 (or IMAP) server <br/>
- pop3_ocn.cpp <br/>
recive mail from OCN POP3 (or IMAP) server <br/>
- test_vmime_header.cpp <br/>
test for decode_header() <br/>


build code <br/>
  % g++ pop3/pop3_ssl.cpp -std=c++11 `pkg-config --cflags --libs vmime_json`  -o pop <br/>  

run code <br/>
% ./a.out

display as below <br/>
> C: Connecting to ubuntu, port 995 <br/>
> S: +OK Dovecot (Ubuntu) ready.  <br/>
> 3 message(s) in your inbox
>  1 : vmime test : hoge@example.org


### Reference <br/>
- https://github.com/kisli/vmime
