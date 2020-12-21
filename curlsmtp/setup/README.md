setup - curlsmtp
===============

setup for curlsmtp <br/>

### install curlsmtp
download files
% git clone https://github.com/honeyligo/curlsmtp <br/>
% ./configure <br/>

you need three files <br/>
- curlsmtp.cpp <br/>
- curlsmtp.h <br/>
- ustd_string.h <br/>


### Library required 
- libcurl <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libcurl <br/>
- jsoncpp <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/jsoncpp <br/>


### gmail.json
create gmail.json including Your account and Your password <br/>
and place on Your home directory <br/>

template <br/>
gmail.json <br/>
- https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/curlsmtp/setup/gmail.json <br/>


### Gmail setting
This sample codes use how to authenticate user with username and password. <br/>
if you use this method with Gmail, <br/>
Allow less secure apps to access your Gmail account <br/>
- https://devanswers.co/allow-less-secure-apps-access-gmail-account/ <br/>

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/curlsmtp/setup/images/google_acount.png" width="300" />


### Reference <br/>
- https://curl.haxx.se/libcurl/c/
- https://github.com/honeyligo/curlsmtp <br/>

