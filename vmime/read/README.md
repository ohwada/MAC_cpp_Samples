read - vmail
===============

vmail sample <br/>
read mail from file <br/>

### sample code
- read_mail_hello.cpp <br/>
read simple email like hello.eml <br/>

- read_mail_text.cpp <br/>
read mail with simple plane text body from file

- read_mail_attach.cpp <br/>
read mail with attached file from file

- read_mail_nest.cpp
read mail with nested multipart from file

build code <br/>
% g++ read/read_mail_hello.cpp -std=c++11 `pkg-config --cflags --libs vmime`  <br/>  

run code <br/>
% ./a,out

display as below <br/>
> The subject of the message is : Hello from VMime! <br/>
 > It was sent by: Vincent( email: vincent@vmime.org ) <br/>
> A simple message to test VMime <br/>

### Reference <br/>
- https://github.com/kisli/vmime
