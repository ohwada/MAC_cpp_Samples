mysql: setup
===============


### Install
(1) install by brew  
% brew install mysql 
https://formulae.brew.sh/formula/mysql  

(2) confirm 
% brew info mysql
% mysql --version
% pkg-config --cflags --libs mysqlclient

(3) start mysql server
 % brew services start mysql

(4)  connect mysql server
% mysql -u root
mysql> SELECT VERSION();
mysql> SHOW DATABASES;
mysql> exit


### Reference  
Mac へ MySQL を Homebrew でインストールする手順  
https://qiita.com/hkusu/items/cda3e8461e7a46ecf25d  

