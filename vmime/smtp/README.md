smtp - vmail
===============

vmail Sample <br/>
send mail to SMTP server <br/>

### sample code
- smtp_ubuntu.cpp <br/>
send mail to Ubuntu SMTP server  <br/>
- smtp_ubuntu_userinput.cpp <br/>
// user input username and password interactive <br/>
- smtp_ubuntu_attach.cpp <br/>
send mail with attached file to Ubuntu SMTP server <br/>
- smtp_ubuntu_attach_two.cpp <br/>
send mail with two attached files to Ubuntu SMTP server <br/>
- smtp_ubuntu_html_embed.cpp <br/>
send mail with HTML and embedded image to Ubuntu SMTP server <br/>
- smtp_ubuntu_utf8.cpp <br/>
send mail with UTF8 encode to Ubuntu SMTP server <br/>
- smtp_ubuntu_iso2022jp.cpp <br/>
send mail with ISO2022JP encode to Ubuntu SMTP server <br/>
- smtp_gmail.cpp <br/>
send mail to Gmail SMTP server <br/>
- smtp_ocn.cpp <br/>
send mail to OCN SMTP server <br/>
- sendmail.cpp <br/>
send mail using sendmail command <br/>
- version.cpp <br/>
display version <br/>

build code <br/>
% g++ smtp/smtp_ubuntu_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime_json` -o attach  <br/>  

run code <br/>
% ./attach

display as below <br/>
> saved mail_20201226230615.eml <br/>

display by thunderbird <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/result/thunderbird_smtp_attach.png" width="300" /><br/>

### Document
- https://ken-ohwada.hatenadiary.org/entry/2020/12/31/152731

### Reference <br/>
- https://github.com/kisli/vmime

