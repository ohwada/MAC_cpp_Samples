setup - abseil
===============

setup for abseil <br/>


###  install abseil
% brew install abseil <br/>
https://formulae.brew.sh/formula/abseil <br/>


###  set up for pkg-config
% bash copy_pkgconfig.sh <br/>

check for pkg-config <br/>
% pkg-config --cflags --libs abseil <br/>
> -I/usr/local/Cellar/abseil/20200225.2/include 
> -L/usr/local/Cellar/abseil/20200225.2/lib -labsl_base 
> ...
> -labsl_time -labsl_time_zone


### Reference <br/>
- https://abseil.io/ <br/>

