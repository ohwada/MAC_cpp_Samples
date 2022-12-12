mysqlpp: simple
===============

### Preparation  
create database, mysql_cpp_data and create stock table
see below   
https://github.com/ohwada/MAC_cpp_Samples/tree/master/mysqlpp/resetdb   


### samples
- simple1.cpp
Example showing the simplest way to get data from 
a MySQL table with MySQL++.

 - simple2.cpp
 Retrieves the entire contents of the sample stock table
using a "store" query, and prints it out.

 - simple3.cpp
Example showing how to use the 'use' method of retrieving
	a table, as opposed to the more common 'store' method illustrated by the simple2 example.


Build and Run:  
% make simple1
% bin/simple1 -u root
> We have:
> Nürnberger Brats
> Pickle Relish
> Hot Mustard
> Hotdog Buns


TODO:  
simple3.cpp  
simple3(16505,0x106ad5dc0) malloc: *** error for object 0x7fe7b1424610: pointer being freed was not allocated  

