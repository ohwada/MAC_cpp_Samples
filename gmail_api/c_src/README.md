c_src - gmail api 
===============

C version <br/>
send and recieve mail with Gmail API <br/>


### sample codes
- get_mail.c <br/>
get mail with Google API <br/>
- send_mail.c <br/>
send mail with Google API <br/>


build code <br/>
% gcc c_src/get_mail.c `pkg-config --cflags --libs libcurl` `pkg-config --cflags --libs json-c` <br/>  

run code <br/>
% ./a.out

display as below <br/>
> Connected to www.googleapis.com <br/>
> You have 100 mails <br/>

### reference
- https://github.com/ohwada/MAC_cpp_Samples/tree/master/mail_builder/c_src
