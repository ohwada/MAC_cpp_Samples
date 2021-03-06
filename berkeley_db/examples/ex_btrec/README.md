ex_btrec - berkeley-db
===============

berkeley-db exsamples <br/>

### ex_btrec

Using a btree with both keys and record numbers <br/>
This program shows how to store automatically numbered records in a btree database, by setting its DB_RECNUM flag.  <br/>
This variety of database can locate a record in two ways: <br/>
either by specifying the key, or by specifying the dynamic logical “record number”<br/>
the relative location of the record in thedatabase, 
as in the line numbers of a text file.  <br/>
After populating the database with 1000 key-value pairs, it 
then switches to a query phase, 
where youselect records not by the key, 
but by the automatically assigned, 
dynamically changing record number.  <br/>


build code <br/>

> % gcc ex_btrec.c  `pkg-config --cflags --libs libdb` <br/>

run code <br/>

> % ./a.out <br/>
> ex_btrec: database contains 1000 records <br/>
> recno #> 1 <br/>
> k/d	0001addresser : resserdda1000 <br/>
> next	0002cataract : tcaratac2000 <br/>
> retrieved recno: 2 <br/>

created "access.db" <br/>

### Reference
- https://github.com/berkeleydb/libdb <br/>

