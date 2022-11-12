RESTinio: setup
===============

### Prerequisites
- C++14 compiler  

- asio 1.12.1  
http://think-async.com/Asio/  

- nodejs/http-parser 2.8.1  
https://github.com/nodejs/http-parser  

- fmtlib 5.2.1.  
https://fmt.dev/latest/index.html  

- SObjectizer 5.5.22.1  
https://sourceforge.net/projects/sobjectizer/  

For building samples, benchmarks and tests:  

- Mxx_ru 1.6.13  
https://sourceforge.net/projects/mxxru/  

- rapidjson 1.1.0  
https://github.com/Tencent/rapidjson  

- json_dto 0.2.3  
https://github.com/Stiffstream/json_dto  

- clara 1.1.5  
https://github.com/catchorg/Clara  

- Catch2 2.4.2  
https://github.com/catchorg/Catch2  


### Install
(1) Download souce files  
git clone https://github.com/Stiffstream/restinio

(2) copy header files to system area 
(eg /usr/local/opt/restinio)
copy setup_hdr.sh to downloaded directory
% bash setup_hdr.sh

(3) copy config file (restinio.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs restinio


