c_src - mail builder
===============

sample codes that create mail message <br/>
C samples <br/>
 - support file attachment <br/>
- support UTF-8 encoding <br/>
- support ISO-2022-JP encoding <br/>

## sample code
- create_mail_text.c <br/>
create simple text mail  <br/>
- create_mail_utf8.c  <br/>
create mail with UTF-8 encoding <br/>
- create_mail_attach.c <br/>
create mail with attached file <br/>
- create_mail_attach_two.c <br/>
create mail with Two attached file <br/>

- create_mail_iso2022jp.c  <br/>
create mail with ISO_2022-JP encoding <br/>
require libiconv <br/>

build code <br/>
% gcc c_src/create_mail_attach.c <br/>

run code <br/>
usage: ./a.out [file] <br/>
% ./a.out <br/>

display as below <br/>
saved to: mail_20201202112647.eml <br/>
display by thunderbird <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/mail_builder/screenshot/thunderbird_create_mail_attach.png" width="300" /><br/>

### Reference
- RFC 2822 : Internet Message Format  <br/>
https://tools.ietf.org/html/rfc2822  <br/>

