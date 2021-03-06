ex_mpool - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_mpool

This example fills a plain file (not a database) with data and performs random reads of it through the MPOOL file interface.  <br/>
It displays the read throughput in blocks and megabytes per second.  <br/>
It could be used as the basis for code which preloads an important database into the Berkeley DB cache. <br/>


build code <br/>

> % gcc ex_mpool.c  `pkg-config --cflags --libs libdb`  <br/>

run code <br/>

> % ./a.out <br/>

display as below <br/>
> cachesize: 20480; pagesize: 1024; N pages: 50
> retrieve 1000 random pages... successful.

created files <br/>
- __db.001 <br/>
- __db.002 <br/>
- __db.003 <br/>
- mpool <br/>


### Reference
- - https://github.com/berkeleydb/libdb <br/>

