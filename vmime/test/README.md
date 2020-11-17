test - vmail
===============

vmail Sample <br/>
test for utility file and function <br/>

### sample code 
- test_mail_json.cpp <br/>
test for getGmailParam <br/> <br/>
- test_file_util.cpp <br/>
test for getTimestampFileName <br/>

- test_utf8_to_iso2022jp.cpp <br/>
test for utf8_to_iso2022jp() <br/>
- test_iso2022jp_to_utf8.cpp <br/>
test for iso2022jp_to_utf8() <br/>
- test_vmime_header.cpp <br/>
test for decode_header() <br/>

- test_readClientJsonFile.cpp <br/>
est for readClientJsonFile <br/>
- test_readRefreshTokenJsonFile.cpp <br/>
test for readRefreshTokenJsonFile <br/>
- test_parseAccessTokenJson.cpp <br/>
test for parseAccessTokenJson <br/>

- test_http_post_to_file.c <br/>
post to postman echo server,  save response to local file <br/>
- test_http_post_to_memory.c <br/>
post to postman echo server,  copy response to memory  <br/>

- test_certificateVerifier_gmail.cpp <br/>
verify pop.gmail.com cert file <br/>
- test_certificateVerifier_ocn.cpp <br/>
verify pop.ocn.ne.jp cert file <br/>
- test_certificateVerifier_ubuntu.cpp <br/>
verify ubuntu cert file <br/>


build code <br/>
  % g++ test_mail_json.cpp -std=c++11 `pkg-config --cflags --libs vmime_json` <br/>  

run code <br/>
% ./a.out

display as below <br/>
> smtp_url: smtp://smtp.gmail.com:587
> user: user@gmail.com
> passwd: 123456789


### Reference <br/>
- https://github.com/kisli/vmime

