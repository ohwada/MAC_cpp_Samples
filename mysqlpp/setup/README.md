mysqlpp: setup
===============


### Require  
 the MySQL C API client library  


### Install  
(1) install by brew  
% brew install mysql++  
https://formulae.brew.sh/formula/mysql++  


(2) copy config file (mysqlpp.pc) to system area   
% bash setup_pkgconfig.sh  
% pkg-config --cflags --libs mysqlpp  

