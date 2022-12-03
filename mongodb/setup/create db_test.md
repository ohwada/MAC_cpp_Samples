mongodb: create db_test
===============

create db_test
https://qiita.com/Ki4mTaria/items/5b2029464db6515f8bfb

### command  
% mongosh
use db_test
db.cl_test.insert({id:1, name:'aaa'});
db.cl_test.insert({id:2, name:'bbb'});
db.cl_test.insert({id:3, name:'ccc'});
db.cl_test.find();
exit

