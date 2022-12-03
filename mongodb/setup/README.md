mongodb: setup
===============


### Install server  
(1) install by brew  
% brew tap mongodb/brew  
% brew install mongodb-community  

(2) confirm  
% brew info mongodb-community  
% % mongod --version  

(3) start mongodb server  
 %   brew services start mongodb/brew/mongodb-community

(4) connect to mongodb server
% mongosh
test> db.version()
test> show dbs
test> exit

### Install client  library
(1) install by brew 
 % brew install mongo-c-driver  
https://formulae.brew.sh/formula/mongo-c-driver  

(2) confirm 
% pkg-config --cflags --libs libmongoc-1.0  


### Reference  
- Install MongoDB Community Edition on macOS  
https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-os-x/

- brewからmongodbがなくなったのでmongodb-communityをインストールする  
https://qiita.com/kazuki5555/items/b80f1f313137dffbb351 

