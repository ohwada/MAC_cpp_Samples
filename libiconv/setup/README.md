setup-  libiconv
===============

setup for  libiconv <br/>

###  install libiconv
% brew install libiconv  <br/>
https://formulae.brew.sh/formula/libiconv  <br/>

## setup for pkgconfig
% bash setup.sh <br/>

check pkgcomfig <br/>
% pkg-config --cflags --libs iconv <br/>
> -I/usr/local/Cellar/libiconv/1.16//include <br/>
> -L/usr/local/Cellar/libiconv/1.16//lib <br/>
> -liconv <br/>

### Reference 
- https://www.gnu.org/software/libiconv/


