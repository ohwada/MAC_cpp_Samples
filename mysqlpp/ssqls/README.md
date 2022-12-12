mysqlpp: ssqls
===============


### Preparation  
create database, mysql_cpp_data and create stock table
see below   
https://github.com/ohwada/MAC_cpp_Samples/tree/master/mysqlpp/resetdb   


### samples
 - ssqls1.cpp
Example that produces the same results as simple1, 
but it uses a Specialized SQL Structure to store the results instead of a MySQL++ Result object.

 - ssqls2.cpp
Example showing how to insert a row using the Specialized
	SQL Structures feature of MySQL++.

 - ssqls3.cpp 
Example showing how to update an SQL row 
using the Specialized SQL Structures feature of MySQL++.

- ssqls4.cpp 
Example very similar to ssqls1.cpp, except that 
it stores its result set in an STL set container.  
This demonstrates
how one can manipulate MySQL++ result sets 
in a very natural C++ style.

 - ssqls5.cpp 
Example showing how to use the equal_list() member of some SSQLS types 
to build SELECT queries with custom WHERE clauses.

- ssqls6.cpp 
Example showing how to insert a collection row 
using the Specialized SQL Structures feature of MySQL++ and Query::insertfrom().


Build and Run:  
% make ssqls2
% bin/ ssqls2 -u root
> Query: INSERT INTO `stock` (`item`,`num`,`weight`,`price`,`sDate`,`description`) VALUES ('Hot Dogs',100,1.5,NULL,'1998-09-25',NULL)
> Query: select * from stock
> Records found: 27


TODO:
- ssqls1.cpp
ssqls1(16842,0x117a85dc0) malloc: *** error for object 0x7f817ac0ff80: pointer being freed was not allocated

- ssqls4.cpp
ssqls4(17175,0x111b54dc0) malloc: *** error for object 0x7ff323c241c0: pointer being freed was not allocated


