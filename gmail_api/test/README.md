test - gmail api 
===============

gmail api sample <br/>
test for utility file and function <br/>


## sample codes

### for c_src 
- test_c_readMailParam.c <br/>
test for getGmailParam <br/>
- test_c_parseAccessTokenJson.c <br/>
test for  parseAccessTokenJson <br/>
- test_c_readListResponseJsonFile.c <br/>
test for readListResponseJsonFile <br/>
- test_c_readMessageResponseJsonFile.c <br/>
test for readMessageResponseJsonFile <br/>
- test_c_readRefreshTokenJsonFile.c <br/>
test for   readRefreshTokenJsonFile <br/>

###  for src 
- test_src_parseListResponseJson.cpp <br/>
test for parseListResponseJson <br/>
- test_src_parseMessageResponseJson.cpp <br/>
test for parseMessageResponseJson <br/>

- test_src_readAttchmentJsonFile.cpp <br/>
test for readAttchmentJsonFile <br/>

- test_src_readMailParam.cpp <br/>
test for getGmailParam <br/>
- test_src_parseAccessTokenJson.cpp <br/>
test for  parseAccessTokenJson <br/>
- test_src_readClientJsonFile.cpp <br/>
test for readClientJsonFile <br/>
- test_src_readRefreshTokenJsonFile.cpp <br/>
test for readRefreshTokenJsonFile <br/>
- test_src_http_post_to_file.cpp <br/>
 test for http_post_to_file <br/>
- test_src_http_post_to_memory.cpp <br/>
 test for http_post_to_memory <br/>


build code <br/>
% gcc test/test_c_readMailParam.c  `pkg-config --cflags --libs json-c` <br/>

run code <br/>
% ./a.out

display as below <br/>
> smtp_url: smtp://smtp.gmail.com:587 <br/>
> smtp_server: smtp.gmail.com  <br/>
> smtp_port: 993  <br/>
