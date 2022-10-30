src - gmail api : oauth2
===============

C++ version <br/>
send and recieve mail with Gmail API <br/>
suport  (OOB) flow Migration  

### OAuth 2.0 Mechanism  
https://developers.google.com/gmail/imap/xoauth2-protocol  

Out-Of-Band (OOB) flow Migration Guide  
https://developers.google.com/identity/protocols/oauth2/resources/oob-migration?hl=en  

### require   
- POCO  
- curlpp  
 jsoncpp  


### Usage
(1) run Local Server by local_server.c  
(2) request auth code by Web Brawser  
(3) User grant access request  
(4) Google Server return auth code to Local Server  
(5) Local Server request refresh token  
(6) Desktop App request access token  
(7) Desktop App send mail using access token  

Using OAuth 2.0 to Access Google APIs
https://developers.google.com/identity/protocols/oauth2?hl=en


### sample codes
- send_mail_text.cpp
- http_server.cpp  
- request_access_token.cpp  

Build and Run:  
% make server  
% bin/server  
> listen port 3000

NOTE:  
this version support send mail only  
get mail (read mail) later  
