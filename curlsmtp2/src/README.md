src - curlsmtp2
===============

curlsmtp2 sample <br/>

### sample code
SMTP Client <br/>
- client_text.cpp <br/>
send mail with plain text to SMTP server  <br/>
- client_attach.cpp <br/>
send mail with attached file to SMTP server <br/>
- client_utf8.cpp <br/>
send mail with UTF-8 encoding to SMTP server <br/>
- client_utf8_attach.cpp <br/>
send mail with UTF-8 encoding and  attached file to SMTP server <br/>
- send_mail_gmail.cpp <br/>
send mail to Gmail SMTP server <br/>


build code <br/>
% bash src/client_text.sh

% g++ src/client_text.cpp src/curlsmtp.cpp src/curlsmtp2.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` 

run code <br/>
% ./a.out
