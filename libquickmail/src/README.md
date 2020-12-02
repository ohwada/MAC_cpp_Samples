src - libquickmail
===============

libquickmail sample <br/>
send mail to SMTP Server using libcurl <br/>

### sample code
- smtp_tls_auth.c <br/>
send mail to SMTP server with TLS and AUTH <br/>
- smtp_attach.c <br/>
send mail with attached files <br/>
- smtp_html.c <br/>
// send mail with html body <br/>
- smtp_gmail.c <br/>
send mail to Gmail SMTP server <br/>

- test_mail_json.c <br/>
 parse mail json file <br/>


build code <br/>
% gcc src/smtp_tls_auth.c  src/quickmail.c `pkg-config --cflags --libs libcurl` `pkg-config --cflags --libs json-c` <br/>  

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

