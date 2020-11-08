sqlite
===============

sqlite sample <br/>

sqlite : <br/>
SQLite is a C-language library that implements a small, fast, self-contained, high-reliability, full-featured, SQL database engine. <br/>
https://sqlite.org/ <br/>


###  install sqlite
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/sqlite/setup <br/>


### Preparation
Prepare sample record in database
% sqlite3 hello.db
sqlite> create table hello (id integer primary key, message text);
sqlite> insert into hello (message) values ('hello');
sqlite> select * from hello;
sqlite> .exit;


## sample code
- select_record.c <br/>
select records from database <br/>
- version.c <br/>
- display version <br/>
 

build sample code<br/>
% gcc select_record.c `pkg-config --cflags --libs sqlite3` <br/>

run sample code <br/>
Usage: ./a.out <br/>

display as below <br/>
> opened: hello.db <br/>
> sql: select * from hello; <br/>
> // id = 1, message = Sierra <br/>


### Reference <br/>
- https://sqlite.org/docs.html

