src - gmail api 
===============

C++ version <br/>
send and recieve mail with Gmail API <br/>

### Note
At October 2022
Out-of-band (OOB) flow is deprecated On Gmail 

Out-Of-Band (OOB) flow Migration Guide
https://developers.google.com/identity/protocols/oauth2/resources/oob-migration?hl=en


try ouath2  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/gmail_api/oauth2


TODO:  
upload large image  
can not upload 512x512 size (164KB)  


### sample codes
- get_mail.cpp <br/>
get mail with Google API <br/>
- send_mail_text.cpp <br/>
send mail using Google API <br/>
- send_mail_attach.cpp <br/>
send mail with attached file using Google API <br/>
- send_mail_utf8.cpp <br/>
send mail with using UTF-8 encoding Google API <br/>


build code <br/>
% g++ src/get_mail.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o get <br/>  

run code <br/>
% ./a.out

display as below <br/>
> Connected to www.googleapis.com <br/>
> You have 100 mails <br/>


### reference
- https://github.com/ohwada/MAC_cpp_Samples/tree/master/mail_builder/src