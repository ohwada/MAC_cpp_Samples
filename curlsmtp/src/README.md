src - curlsmtp
===============

curlsmtp Sample <br/>
send mail to SMTP server  <br/>

### sample code
- send_mail_text.cpp <br/>
send mail with plain text to SMTP server  <br/>
- send_mail_attach.cpp <br/>
send mail with attached file to SMTP server <br/>
- send_mail_utf8.cpp <br/>
send mail with UTF-8 encoding to SMTP server <br/>
- send_mail_gmail.cpp <br/>
send mail to Gmail SMTP server <br/>
- send_mail_gmail_xoauth.cpp <br/>
send mail to Gmail SMTP server with xoauth <br/>

- test_mail_json.cpp <br/>
test for getGmailParam <br/>


build code <br/>
% g++ src/send_mail_text.cpp src/curlsmtp.cpp -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` <br/>

run code <br/>
% ./a.out

display as below <br/>
> Connected to ubuntu <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/





