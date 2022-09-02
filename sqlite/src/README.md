sqlite: src
===============


### Preparation
Prepare sample record in database
% sqlite3 test.db
sqlite> create table testtable (id integer primary key, name text);
sqlite> insert into testtable (name) values ('aaa');
sqlite> insert into testtable (name) values ('bbb');
sqlite> insert into testtable (name) values ('ccc');
sqlite> select * from testtable;
sqlite> .quit


## samples
- select.c  
- insert.c  
- create_table.c  
- delete.c  
- transaction.c  
- update.c  
- version.c  


Build and Run:  
% make select  
% cd bin  
% ./select  
 > 1 aaa  
> 2 bbb  
> 3 ccc  

