curlsmtp2
===============

this project is fork from <br/>
https://github.com/honeyligo/curlsmtp <br/>

added the following tfeatures <br/>
- able to set separately CURLOPT_USERNAME and CURLOPT_MAIL_FROM <br/>
- UTF-8 encoding subject and message  <br/>
- Gmail xouath  <br/>


### setup
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/curlsmtp2/setup <br/>

### sample code

#### src
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
send mail to Gmail SMTP server <br/

 
#### xoauth
- client_gmail_xoauth.cpp <br/>
send mail to Gmail SMTP server with xoauth <br/>


### Reference <br/>
- https://curl.haxx.se/libcurl/c/
- https://github.com/honeyligo/curlsmtp <br/>
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md


