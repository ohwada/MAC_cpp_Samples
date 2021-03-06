ex_bulk - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_bulk

Using the bulk interface, secondary indexes, and subdatabases  <br/>
This demonstrates how to fetch and modify many records within a single call of DB->get(), DB->put(), and DB->del().  <br/>
It also shows how to:  <br/>
 a) define a custom btree key comparison function, so that records are ordered as natural integers,  <br/>
 b) store two databases in a single Berkeley DB file, and  <br/>
 c) construct a secondary “index” database for quick record access via a component of the data field.  <br/>


build code <br/>

> % gcc ex_bulk.c  `pkg-config --cflags --libs libdb` <br/>

run code <br/>

> % ./a.out <br/>

created  "ex_bulk.db"  in "EX_BULK" directory  <br/>


### Reference
- https://github.com/berkeleydb/libdb <br/>

