setup - libcurl
===============

setup for libcurl <br/>


### Note: 
curl (libcurl) is preinstalled on macOS <br/>
excutable binary <br/>
% curl --version <br/>
curl 7.64.1  <br/>

header files <br/>
% ls /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/curl <br/>

librariy files <br/>
% ls /usr/lib/libcurl* <br/>

can not remove /usr/lib/libcurl.4.dylib <br/>
because this is restricted file <br/>

###  install latest libcurl
% brew install curl <br/>
https://formulae.brew.sh/formula/curl <br/>

### setup for pkgconfig
% bash setup.sh <br/>

confirm for pkgconfig <br/>
% pkg-config --cflags --libs libcurl <br/>
> -I/usr/local/Cellar/curl/7.72.0/include <br/>
> -L/usr/local/Cellar/curl/7.72.0/lib -lcurl <br/>


### Library required for mail
- json-c <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/json-c <br/>


### gmail.json
create gmail.json including Your account and Your password <br/>
and place on Your home directory <br/>

template <br/>
gmail.json <br/>
- https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libcurl/setup/gmail.json <br/>


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
