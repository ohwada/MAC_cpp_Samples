gmail api 
===============

Gmail API sample <br/>
send and recieve mail with Gmail API <br/>
- support file attachment <br/>
- support UTF-8 encoding  <br/>

### setup
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/gmail_api/setup <br/>

### sample code of C version
- get_mail.c <br/>
get mail with Google API <br/>
- send_mail.c <br/>
send mail with Google API <br/>


### sample code of C++ version
- get_mail.cpp <br/>
get mail with Google API <br/>
- send_mail.cpp <br/>
send mail with Google API <br/>


build code <br/>
% g++ src/get_mail.cpp -std=c++11 `pkg-config --cflags --libs curlpp` `pkg-config --cflags --libs jsoncpp` <br/>  

run code <br/>
% ./a.out

display as below <br/>
> Connected to www.googleapis.com <br/>
> You have 100 mails <br/>

### description
This app runs in 4 steps

1. obtain Authorization Code with user consent 

 at first time,  the user obtain Authorization Code from Google server by web browser
and enter Authorization Code in this app

this app display message as below
> Enter the following URL into a browser:
> Enter the browser's response to confirm authorization:

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gmail_api/setup/images/google_user_consent_readonly.png" width="300" />

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gmail_api/setup/images/google_authorization_code.png" width="300" />

2. get Refresh Token using Authorization Code

this app get Refresh Token
and save it in current directory,  at first tome, 
reuse Refresh Token, from the second time onwards

3. get a new Access Token using Refresh Token

4. access Gmail API server using Access Token


### Reference <br/>
- https://developers.google.com/identity/protocols/oauth2 
- https://github.com/ohwada/MAC_cpp_Samples/blob/master/mail.md
- https://github.com/ohwada/MAC_cpp_Samples/tree/master/mail_builder

