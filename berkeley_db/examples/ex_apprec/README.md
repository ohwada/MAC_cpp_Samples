ex_apprec - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_apprec

Extending the transaction system for your application <br/>
It is possible to add your own record types to the transaction log, and register functions to be called when those records are backed out during DB_TXN->abort() or processed during database recovery.   <br/>
This example adds support for a transactionally-protected “make directory” operation.  <br/>


### TODO: <br/>
This example doea not work <br/>
display error as elow when build code <br/>
ex_appre_auto.h:13:8: error: unknown type name __DB_IMPORT <br/>


build code <br/>

> % gcc ex_apprec.c  `pkg-config --cflags --libs libdb` <br/>


### Reference
- - https://github.com/berkeleydb/libdb <br/>

