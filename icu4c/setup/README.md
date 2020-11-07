setup- icu4c
===============

setup for icu4c <br/>

###  install icu4c
% brew install icu4c <br/>
https://formulae.brew.sh/formula/icu4c <br/>

## setup for pkgconfig
% bash setup.sh <br/>

check pkgcomfig <br/>
% pkg-config --cflags --libs icu-uc <br/>
> -I/usr/local/Cellar/icu4c/67.1/include <br/>
> -L/usr/local/Cellar/icu4c/67.1/lib <br/>
>  -licuuc -licudata <br/>

### Reference <br/>
- http://site.icu-project.org/home

