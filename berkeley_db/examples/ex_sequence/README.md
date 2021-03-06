ex_sequence - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_sequence

Using sequences to automatically generate item identifiers  <br/>
This shows how a DB_SEQUENCE provides a stream of increasing or decreasing 64-bit integers. <br/>


build code <br/>

> % gcc ex_sequence.c  `pkg-config --cflags --libs libdb` <br/>

run code <br/>

> % ./a.out <br/>
> Got sequence number 0 <br/>
> Got sequence number 1 <br/>
> Got sequence number 2 <br/>

created "sequence.db" <br/>


### Reference
- https://github.com/berkeleydb/libdb <br/>

