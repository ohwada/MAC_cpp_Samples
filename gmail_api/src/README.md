src - gmail api 
===============

C++ version <br/>
send and recieve mail with Gmail API <br/>


### sample codes
- get_mail.cpp <br/>
get mail with Google API <br/>
- send_mail.cpp <br/>
send mail using Google API <br/>
- send_mail_attach.cpp <br/>
send mail with attached file using Google API <br/>
- send_mail_utf8.cpp <br/>
send mail with using UTF-8 encoding Google API <br/>

- test_parseListResponseJson.cpp <br/>
test for parseListResponseJson <br/>
- test_parseMessageResponseJson.cpp <br/>
test for parseMessageResponseJson <br/>
- test_mail_json.cpp <br/>
test for getGmailParam <br/>
- test_parseAccessTokenJson.cpp <br/>
test for  parseAccessTokenJson <br/>
- test_readClientJsonFile.cpp <br/>
test for readClientJsonFile <br/>
- test_readRefreshTokenJsonFile.cpp <br/>
test for readRefreshTokenJsonFile <br/>
- test_http_post_to_file.cpp <br/>
 test for http_post_to_file <br/>
- test_http_post_to_memory.cpp <br/>
 test for http_post_to_memory <br/>


build code <br/>
% g++ src/get_mail.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` -o get <br/>  

run code <br/>
% ./a.out

display as below <br/>
> Connected to www.googleapis.com <br/>
> You have 100 mails <br/>

