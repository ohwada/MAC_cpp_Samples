src - curlsmtp
===============

curlsmtp sample <br/>

### Note: 
cannot set separately <br/>
CURLOPT_USERNAME and CURLOPT_MAIL_FROM <br/>
try curlsmtp2 <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/curlsmtp<br/>

### sample code
- client_text.cpp <br/>
send mail with plain text to SMTP server  <br/>
- client_attach.cpp <br/>
send mail with attached file to SMTP server <br/>
- client_utf8.cpp <br/>
send mail with UTF-8 encoding to SMTP server <br/>
- client_gmail.cpp <br/>
send mail to Gmail SMTP server <br/>

 build code <br/>
% bash src/build_client_text.sh <br/>

run code <br/>
% ./client_text <br/>

### Reference <br/>
- https://curl.haxx.se/libcurl/c/
- https://github.com/honeyligo/curlsmtp <br/>

