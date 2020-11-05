xoauth - curlsmtp 
===============

curlsmtp Sample <br/>

send mail to Gmail SMTP server with xoauth <br/>


### sample code
- send_mail_gmail_xoauth.cpp <br/>
send mail to Gmail SMTP server with xoauth <br/>


- test_parseAccessTokenJson.cpp <br/>
test for  parseAccessTokenJson <br/>
- test_readClientJsonFile.cpp <br/>
 test for readClientJsonFile <br/>
- test_readRefreshTokenJsonFile.cpp <br/>
test for readRefreshTokenJsonFile <br/>

- test_http_post_to_file.cpp <br/>
post to postman echo server,  save response to local file <br/>
- test_http_post_to_memory.cpp <br/>
post to postman echo server,  copy response to memory <br/>


build code <br/>
% g++ xoauth/send_mail_gmail_xoauth.cpp src/curlsmtp.cpp  -std=c++11 `pkg-config --cflags --libs libcurl`  `pkg-config --cflags --libs jsoncpp` <br/>

run code <br/>
% ./a.out

display as below <br/>
> Connected to smtp.gmail.com (2404:6800:4008:c00::6c) port 587 (#0) <br/>

### description
This app runs in 4 steps

1. obtain Authorization Code with user consent 

 at first time,  the user obtain Authorization Code from Google server by web browser
and enter Authorization Code in this app

this app display message as below
> Enter the following URL into a browser:
> Enter the browser's response to confirm authorization:

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/curlsmtp/setup/images/google_user_consent.png" width="300" />

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/smtp/setup/images/google_authorization_code.png" width="300" />

2. get Refresh Token using Authorization Code

this app get Refresh Token
and save it in current directory,  at first tome, 
reuse Refresh Token, from the second time onwards

3. get a new Access Token using Refresh Token

4. login Gmail server using Access Token


### Reference <br/>
- https://curl.haxx.se/libcurl/c/





