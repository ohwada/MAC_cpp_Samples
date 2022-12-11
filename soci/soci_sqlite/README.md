soci: sqlite
===============

### Reference  
soci SQLite3 Backend Referenc  
http://soci.sourceforge.net/doc/master/backends/sqlite3/  


### Preparation  
create test.db  
see below  
https://github.com/ohwada/MAC_cpp_Samples/tree/master/sqlite/setup/create_test_db.md  


## Sample  
- soci_sqlite.cpp  

Build and Run:  
% make sqlite  
% bin/sqlite  
> select count(*) from testtable  
> count: 3  

