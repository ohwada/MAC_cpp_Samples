libquickmail
===============

libquickmail Sample <br/>
send mail to SMTP server <br/>
- support file attachment <br/>


libquickmail : <br/>
C library for sending e-mail (with attachments) from C/C++ <br/>
wrapper for libcurl smtp <br/>
https://sourceforge.net/projects/libquickmail/ <br/>


### setup for libquickmail 
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libquickmail/setup <br/>


### sample code
- smtp-tls-auth.c <br/>
send mail to SMTP server with TLS and AUTH <br/>
- smtp-attach.c <br/>
send mail with attached files <br/>
- smtp-html.c <br/>
// send mail with html body <br/>
- smtp-gmail.c <br/>
send mail to Gmail SMTP server <br/>
- test_mail_json.c <br/>
 parse mail json file <br/>


build code <br/>
% gcc src/smtp-tls-auth.c src/quickmail.c `pkg-config --cflags --libs libcurl` `pkg-config --cflags --libs json-c` <br/>  

run code <br/>
% a.out

display as below <br/>
> libquickmail 0.1.27 <br/>
> < 220 VirtualBox ESMTP Postfix (Ubuntu) <br/>
> \> AUTH PLAIN <br/>
> < 235 2.7.0 Authentication successful <br/>


### Reference <br/>
- https://github.com/cdevelop/libquickmail/
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md

