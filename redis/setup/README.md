redis: setup
===============


### Install server  
(1) install by brew  
% brew install redis

(2) confirm  
% brew info redis  
%  redis-server --version
% redis-cli --version

(3) start redis server  
 % brew services start redis

(4) connect to redis server
% redis-cli 
127.0.0.1> ping
127.0.0.1> set mykey1 "abc"
127.0.0.1> get mykey1
127.0.0.1> exit


### Install client  library
(1) install by brew 
% brew install hiredis
https://github.com/redis/hiredis

(2) confirm 
% pkg-config --cflags --libs hiredis


### Reference  
- Install Redis on macOS  
https://redis.io/docs/getting-started/installation/install-redis-on-mac-os/  

- Redis を macOS にインストールする手順 (Homebrew)  
https://weblabo.oscasierra.net/redis-macos-install-homebrew/  
