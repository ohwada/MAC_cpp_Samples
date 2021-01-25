pop3 - vmail
===============

vmail Sample <br/>
recieve mail from POP3 (or MAP) server <br/>

### sample code 
- pop3_ubuntu.cpp <br/>
recievw mail from Ubuntu POP3 (or MAP) server <br/>
- pop3_userinput.cpp <br/>
user input username and password interactive
- pop3_gmail.cpp <br/>
recive mail from Gmail POP3 (or IMAP) server <br/>
- pop3_ocn.cpp <br/>
recive mail from OCN POP3 (or IMAP) server <br/>


build code <br/>
  % g++ pop3/pop3_ubuntu.cpp -std=c++11 `pkg-config --cflags --libs vmime_json`  -o pop <br/>  

run code <br/>
% ./a.out

display as below <br/>
> C: Connecting to ubuntu, port 995 <br/>
> S: +OK Dovecot (Ubuntu) ready.  <br/>
> 3 message(s) in your inbox
>  1 : vmime test : hoge@example.org


### Document
- https://ken-ohwada.hatenadiary.org/entry/2021/01/25/134954


### Reference 
- https://github.com/kisli/vmime

