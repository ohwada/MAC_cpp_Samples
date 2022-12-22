beast : chat_multi
===============

<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/boost_beast/screenshots/chat_multi.png" width="300" />

### require
this sample  require beast latest version 344

version 330 if installed with brew
download from github
https://github.com/boostorg/beast/

330 does not have the following files
<boost/beast/http/message_generator.hpp>


### samples
- chat_multi.cpp

Buid andRun:
% make server
% bin/server
> listen port: 8090

Client:  
vist localhost:8090 by Web Brawser  

