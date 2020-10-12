xoauth - libcurl
===============

libcurl Sample <br/>
send mail to Gmail SMTP server with xoauth <br/>


### sample codes
- smtp-gmail-xoauth.c <br/>
send mail to Gmail SMTP server with xoauth2 <br/>
- test_mail_json.c <br/>
test for getGmailParam <br/>
- test_readClientJsonFile.c <br/>
test for readClientJsonFile <br/>
- test_readRefreshTokenJsonFile.c <br/>
test for readRefreshTokenJsonFile <br/>
- test_parseAccessTokenJson.c <br/>
test for parseAccessTokenJson <br/>

build code <br/>
% gcc xoauth/smtp-gmail-xoauth.c `pkg-config --cflags --libs libcurl` `pkg-config --cflags --libs json-c` -o gmail_xoauth <br/>  

run code <br/>
% ./a.out

display as below <br/>
> Connected to smtp.gmail.com (2404:6800:4008:c00::6c) port 587 (#0) <br/>
> \> AUTH OAUTHBEARER <br/>
> < 334 <br/>
> \> bixhPWlvdC5.....0PXNtdH <br/>
> \< 235 2.7.0 Accepted <br/>


### description
This app runs in 4 steps

1. obtain Authorization Code with user consent 

 at first time,  the user obtain Authorization Code from Google server by web browser
and enter Authorization Code in this app

this app display message as below
> Enter the following URL into a browser:
> Enter the browser's response to confirm authorization:

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libcurl/setup/images/google_user_consent.png">

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libcurl/setup/images/google_authorization_code.png">

2. get Refresh Token using Authorization Code

this app get Refresh Token
and save it in current directory,  at first tome, 
reuse Refresh Token, from the second time onwards

3. get a new Access Token using Refresh Token

4. login Gmail server using Access Token


### Reference <br/>
- https://curl.haxx.se/libcurl/c/
- https://developers.google.com/identity/protocols/oauth2 

