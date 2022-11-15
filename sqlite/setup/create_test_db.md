sqlite: create test db
===============

### create test db  
Prepare sample record in database  
% sqlite3 test.db  
sqlite> create table testtable (id integer primary key, name text);  
sqlite> insert into testtable (name) values ('aaa');  
sqlite> insert into testtable (name) values ('bbb');  
sqlite> insert into testtable (name) values ('ccc');  
sqlite> select * from testtable;  
sqlite> .quit  

