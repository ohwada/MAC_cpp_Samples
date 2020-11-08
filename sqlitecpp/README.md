SQLiteCpp
===============

sqlitecpp sample <br/>

SQLiteCpp : <br/>
a smart and easy to use C++ SQLite3 wrapper. <br/>
https://github.com/SRombauts/SQLiteCpp <br/>


###  install sqlite
see below <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/sqlitecpp/setup <br/>


### Preparation
Prepare sample record in database
% sqlite3 test.db
sqlite> create table test (id integer primary key, message text);
sqlite> insert into test (message) values ('Sierra');
sqlite> insert into test (message) values ('Mojave');
sqlite> insert into test (message) values ('Catalina');
sqlite> select * from test;
sqlite> .exit


## sample code
- select_record.cpp <br/>
select records from databese <br/>
- version.c <br/>
- display version <br/>
 

build sample code<br/>
% g++ select_record.cpp -std=c++11 `pkg-config --cflags --libs sqlitecpp` <br/>

run sample code <br/>
Usage: ./a.out <br/>

display as below <br/>
> SELECT * FROM test <br/>
> row: 1, Sierra <br/>
> row: 2, Mojave <br/>
> row: 3, Catalina <br/>


### Reference <br/>
- https://github.com/SRombauts/SQLiteCpp <br/>
- https://sqlite.org/ <br/>
