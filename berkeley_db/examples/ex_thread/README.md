ex_thread - berkeley-db
===============

berkeley-db exsamples <br/>


### ex_thread

Multithreaded reads and writes  <br/>
The ex_thread example demonstrates multithreaded access.   <br/>
It shows how to prepare and open the environment and database handles so that they can be safely shared by freely running threads.   <br/>
The example also demonstrates deadlock handling, which is nearly always needed by such applications.  <br/>


Preparation <br/>

> % mkdir TESTDIR <br/>

build code <br/>

> % gcc ex_thread.c  `pkg-config --cflags --libs libdb` <br/>

run code <br/>

> % ./a.out <br/>
> Running: readers 4, writers 4 <br/>
> write thread 2 starting: tid: 123145434849280 <br/>
> write thread 3 starting: tid: 123145435385856 <br/>
> deadlock thread starting: tid: 123145439141888 <br/>
> writer:  3: adds:   10: deletes:   10: aborts:    0: txns:   20 <br/>
> writer:  2: adds:    6: deletes:   14: aborts:    0: txns:   20 <br/>

created "access.db" in TESTDIR directory <br/>


### Reference
- https://github.com/berkeleydb/libdb <br/>

