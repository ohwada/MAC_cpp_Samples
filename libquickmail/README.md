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
send mail to SMTP Server using libcurl <br/>
- smtp_tls_auth.c <br/>
send mail to SMTP server with TLS and AUTH <br/>
- smtp_attach.c <br/>
send mail with attached files <br/>
- smtp_html.c <br/>
// send mail with html body <br/>
- smtp_gmail.c <br/>
send mail to Gmail SMTP server <br/>


build code <br/>
% gcc src/smtp_tls_auth.c src/quickmail.c `pkg-config --cflags --libs libcurl` `pkg-config --cflags --libs json-c` <br/>  

run code <br/>
% a.out

display as below <br/>
> libquickmail 0.1.27 <br/>
> < 220 VirtualBox ESMTP Postfix (Ubuntu) <br/>
> \> AUTH PLAIN <br/>
> < 235 2.7.0 Authentication successful <br/>

### smtpsocket
send mail to SMTP Server using smtpsocket <br/>


### Document <br/>
- https://ken-ohwada.hatenadiary.org/entry/2020/12/20/150210 <br/>


### Reference <br/>
- https://github.com/cdevelop/libquickmail/ <br/>
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md <br/>


