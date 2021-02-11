smtp - network
===============

C network sample <br/>
SMTP Client using socket functions <br/>

### sample code
- smtp_client_text.c <br/>
send plain text message <br/>
- smtp_client_utf8.c <br/>
send message with UTF-8 encoding <br/>
- smtp_client_attac.c <br/>
send message with attached file <br/>


build code  <br/>
% gcc smtp_client_text.c <br/>

run code <br/>
Usage: ./a.out <br/>

display as below <br/>
> connect to: ubuntu : 25 
> * \<HELO localhost 
> * \>220 VirtualBox ESMTP Postfix (Ubuntu)

smtp_client_attac.c <br/>
display by thunderbird <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/network/screenshot/thunderbird_smtp_client_attach.png" width="300" />


### Reference <br/>
- http://techdatebook.seesaa.net/article/452940846.html
- http://srgia.com/docs/rfc2822j.html
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md
- https://github.com/ohwada/MAC_cpp_Samples/tree/master/mail_builder/c_src
