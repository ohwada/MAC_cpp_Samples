smtp - vmail
===============

vmail Sample <br/>
send mail to SMTP server <br/>

### sample code
- smtp_tls_auth.cpp <br/>
send mail to SMTP server with TLS and AUTH <br/>
- smtp_userinput.cpp <br/>
// user input username and password interactive <br/>
- smtp-attach.cpp <br/>
send mail with attached file to SMTP server <br/>
- smtp_html_embed.cpp <br/>
send mail with HTML and embedded image to SMTP server <br/>
- smtp_utf8.cpp <br/>
send mail with UTF8 encode to SMTP server <br/>
- smtp_iso2022jp.cpp <br/>
send mail with ISO2022JP encode to SMTP server <br/>
- smtp_gmail.cpp <br/>
send mail to Gmail SMTP server <br/>
- smtp_ocn.cpp <br/>
send mail to OCN SMTP server <br/>
- test_mail_json.cpp <br/>
test for getGmailParam <br/> <br/>
- test_file_time.cpp <br/>
test for getTimestampFileName <br/>
- test_vmime_charset.cpp <br/>
test for utf8_to_iso2022jp() <br/>


build code <br/>
% g++ smtp/smtp_tls_auth.cpp -std=c++11 `pkg-config --cflags --libs vmime_json` -o smtp_tls   <br/>  

run code <br/>
% ./a.out

display as below <br/>
> C: Connecting to ubuntu, port 25 <br/>
> S: 220 VirtualBox ESMTP Postfix (Ubuntu) <br/>


result of smtp-html-embed.cpp <br/>
display by thunderbird <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/result/thunderbird_html_embed.png" width="300" /><br/>


### Reference <br/>
- https://github.com/kisli/vmime

