setup - libcurl
===============

setup for libcurl <br/>


### Note: 
curl (libcurl) is preinstalled on macOS <br/>
% curl --version <br/>
curl 7.64.1  <br/>


###  install latest libcurl
% brew install curl <br/>
https://formulae.brew.sh/formula/curl <br/>

### setup for pkgconfig
% ln -s /usr/local/opt/curl/lib/pkgconfig/libcurl.pc /usr/local/lib/pkgconfig/libcurl.pc

confirm for pkgconfig
% pkg-config --cflags --libs libcurl
> -I/usr/local/Cellar/curl/7.72.0/include 
> -L/usr/local/Cellar/curl/7.72.0/lib -lcurl


### requires for mail
- json-c <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/json-c<br/>

### gmail.json
create gmail.json include Your account and Your password <br/>
and place on Your home directory <br/>

template <br/>
gmail.json <br/>


### Gmail setting
This sample codes use how to authenticate user with username and password. <br/>
if you use this method with Gmail, <br/>
Allow less secure apps to access your Gmail account <br/>
- https://devanswers.co/allow-less-secure-apps-access-gmail-account/ <br/>

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libcurl/setup/images/google_acount.png" width="300" />

### Gmail with oauth2
obtain OAuth 2.0 client credentials from the Google API Console. <br/>
and place on Your home directory <br/>

Using OAuth 2.0 to Access Google APIs <br/> 
- https://developers.google.com/identity/protocols/oauth2 <br/>

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libcurl/setup/images/google_api_console.png" width="300" />
