create - vmail
===============

vmime Sample <br/>
create mail message <br/>

### sample code
- create_mail_text.cpp <br/>
create plain text mail <br/>
- create_mail_utf8.cpp <br/>
create mail with UTF8 encoding <br/>
- create_mail_iso2022jp.cpp <br/>
create mail with ISO2022JP encoding <br/>
- create_mail_attach.cpp <br/>
create mail with attaced file <br/>
- create_mail_attach_two.cpp <br/>
create mail with Two attaced files  <br/>
- create_mail_html.cpp  <br/>
create mail with HTML  <br/>
- create_mail_embed.cpp  <br/>
create mail with HTML embedded image  <br/>
- version.cpp <br/>
display version <br/>


biuld sample code  <br/>
g++ create/create_mail_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime` -o attach

run sample code  <br/>
Usage: attach  [file ] <br/>
%./attach <br/>

display as below <br/>
> saved mail_20201226230615.eml <br/>

display by thunderbird <br/>
create_mail_attach.cpp <br/>
display by thunderbird <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/screenshot/thunderbird_create_mail_attach.png" width="300" /><br/>

### Reference <br/>
- https://github.com/kisli/vmime
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md

