mysql: create db_test
===============

create db_test  
https://qiita.com/Ki4mTaria/items/778ff9186bb4958bb667  

### command  

% mysql -uroot  
mysql> create database db_test;  
mysql> use db_test  
mysql> create table tb_test(id int,name varchar(256));  
mysql> insert into tb_test(id,name) values(1,"aaa");  
mysql> insert into tb_test(id,name) values(2,"bbb");  
mysql> insert into tb_test(id,name) values(3,"ccc");  
mysql> select id, name from tb_test;  
+------+------+  
| id   | name |  
+------+------+  
|    1 | aaa  |  
|    2 | bbb  |  
|    3 | ccc  |  
+------+------+  
3 rows in set (0.00 sec)  
mysql> exit  

