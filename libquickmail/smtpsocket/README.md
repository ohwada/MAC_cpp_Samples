smtpsocket - libquickmail
===============

libquickmail sample <br/>
send mail to SMTP Server using smtpsocket <br/>

### sample code
- test_quickmail.c <br/>
send mail to SMTP Server with AUTH <br/>
- test_smtpsocket.c <br/>
test for smtpsocket.c  <br/>
send mail to SMTP Server  <br/>


build code <br/>
% gcc test_quickmail.c quickmail.c smtpsocket.c  `pkg-config --cflags --libs json-c`  -DNOCURL <br/>  

run code <br/>
% a.out

display as below <br/>
> < 220 VirtualBox ESMTP Postfix (Ubuntu) <br/>


### Reference <br/>
- https://github.com/cdevelop/libquickmail/
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md

