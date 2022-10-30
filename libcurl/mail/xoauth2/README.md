xoauth - libcurl: xoauth2
===============

send mail to Gmail SMTP server with xoauth  
suport  (OOB) flow Migration  

### OAuth 2.0 Mechanism  
https://developers.google.com/gmail/imap/xoauth2-protocol  

Out-Of-Band (OOB) flow Migration Guide  
https://developers.google.com/identity/protocols/oauth2/resources/oob-migration?hl=en  

### require   
- libmicrohttpd  
- json-c  

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
- smtp_gmail_xoauth.c 
- local_server.c
- request_auth_code.c
- request_access_token.c


### Document
https://ken-ohwada.hatenadiary.org/entry/2022/10/30/112802  

