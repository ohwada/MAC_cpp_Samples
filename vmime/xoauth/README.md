xoath - vmail
===============

vmail Sample <br/>
send mail to Gmail SMTP server with xoauth2 <br/>


### sample code
- smtp-gmail-xoauth.cpp <br/>
send mail to Gmail SMTP server with xoauth2 <br/>

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


build code <br/>
% g++ xoauth/smtp_gmail_xoauth.cpp -std=c++11 `pkg-config --cflags --libs vmime_json` `pkg-config --cflags --libs curlpp` -o gmail_xouath <br/>  

run code <br/>
% ./a.out <br/>

display as below <br/>
> C: Connecting to smtp.gmail.com, port 587 <br/>
> S: 220 smtp.gmail.com ESMTP  <br/>
> C: AUTH XOAUTH2 dXNlcj4BAQ== <br/>
> S: 235 2.7.0 Accepted <br/>


### description
This app runs in 4 steps

1. obtain Authorization Code with user consent 

 at first time,  the user obtain Authorization Code from Google server by web browser
and enter Authorization Code in this app

this app display message as below
> Enter the following URL into a browser:
> Enter the browser's response to confirm authorization:

google_user_consent.png
google_authorization_code.png

2. get Refresh Token using Authorization Code

this app get Refresh Token
and save it in current directory,  at first tome, 
reuse Refresh Token, from the second time onwards

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/setup/images/google_user_consent.png" width="300" />

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/setup/images/google_authorization_code.png" width="300" />


3. get a new Access Token using Refresh Token

4. login Gmail server using Access Token

https://developers.google.com/identity/protocols/OAuth2

Note;
Access tokens have limited lifetimes about one hour.
Refresh tokens have unlimited lifetimes

Creating short-lived service account credentials
- https://cloud.google.com/iam/docs/creating-short-lived-service-account-credentials

Do Google refresh tokens expire?
- https://stackoverflow.com/questions/8953983/do-google-refresh-tokens-expire#:~:text=The%20Google%20Auth%20server%20issued,revokes%20access%20to%20your%20application.



### Reference <br/>
- https://github.com/kisli/vmime
- https://developers.google.com/identity/protocols/OAuth2

