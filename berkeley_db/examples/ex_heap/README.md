ex_access - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_heap

Comparing the characteristics of btrees and heaps <br/>
This program demonstrates some differences between the heap and btree database types.
It starts by populating the database, and then switches into a phase of adding and removing data while keeping a fairly constant amount of data in the database. 
A DB_HEAP maintains a constant database size if the heap size is configured properly, while the btree database may continue to grow. <br/>


bild cpde  <br/>

> % gcc ex_heap.c  `pkg-config --cflags --libs libdb` <br/>


run code <br/>

> % ./a.out -h . <br/>
> About to enter the insert phase. <br/>
> Database type: Heap 	with configured heapsize = 0 gbytes and 720000 bytes. <br/>
> Pagesize: 4096 <br/>
> Initial records number: 10000 <br/>
> Number of repetitions: 1 <br/>
> Number of inserts per repetition: 10000 <br/>
> repetition 	 physical file size 	 running time <br/>
> 0 		     356352 		 0.01 seconds <br/>
> 1 		     700416 		 0.02 seconds <br/>

created "heap.db" <br/>

### Reference
- https://github.com/berkeleydb/libdb <br/>

