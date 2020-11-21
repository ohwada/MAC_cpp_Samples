setup - curlpp
===============

setup for curlpp <br/>


###  install curlpp
% brew install curlpp <br/>
https://formulae.brew.sh/formula/curlpp <br/>


###  set up for pkg-config
% bash setup.sh <br/>

check for pkg-config <br/>
% pkg-config --cflags --libs curlpp <br/>
> -I/usr/local/Cellar/curlpp/0.8.1/include  <br/>
> -L/usr/local/Cellar/curlpp/0.8.1/lib  <br/>
> -lcurlpp -lcurl  <br/>


### TODO

use the latest libcurl <br/>
in current built with pre-installed libcurl <br/>

see version.cpp
https://github.com/ohwada/MAC_cpp_Samples/tree/master/curlpp/src/version.cpp <br/>

### Reference <br/>
- https://github.com/jpbarrette/curlpp

