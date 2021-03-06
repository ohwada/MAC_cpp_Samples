setup - berkeley-db
===============

setup for berkeley-db <br/>

###  install berkeley-db

> % brew install berkeley-db <br/>

https://formulae.brew.sh/formula/abseil <br/>

You can use db_dump command <br/>

> % db_dump -V <br/>
> Berkeley DB 18.1.32: (February 19, 2019) <br/>


###  set up for pkg-config

> % bash seutp.sh <br/>

check for pkg-config <br/>

> % pkg-config --cflags --libs libdb <br/>
> -I/usr/local/Cellar/berkeley-db/18.1.32_1/include  <br/>
>  -L/usr/local/Cellar/berkeley-db/18.1.32_1/lib  <br/>
> -ldb


### Reference
- - https://github.com/berkeleydb/libdb <br/>

