src - postfix
===============

postfix sample <br/>
send mail using mail command or sensdmail command <br/>
- suport UTF-8 encoding <br/>

### sample code
- mail.c <br/>
send mail using mail command <br/>
- sendmail_text.c <br/>
send plain text mail using sendmail command <br/>
- sendmail_utf8.c <br/>
send plain text mail with UTF-8 encoding using sendmail command <br/>

build code
% gcc mail.c `pkg-config --cflags --libs json-c`

run code
./a.out

### Reference <br/>
- http://www.postfix.org/

