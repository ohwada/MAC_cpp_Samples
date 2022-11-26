mysqlpp: setup
===============


### Install  
(1) install by brew  
% brew install mysql-connector-c++  
https://formulae.brew.sh/formula/mysql-connector-c++


(2) copy config file (mysqlcppconn.pc) to system area   
% bash setup_pkgconfig.sh  
% pkg-config --cflags --libs mysqlcppconn  

