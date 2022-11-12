nodejs_http_parser: setup
===============


### Install
(1) Download souce files  
git clone https://github.com/nodejs/http-parser

(2) Create http_parser.xxx.a
copy Makefile to downloaded directory(http-parser)  
% make  

created libhttp_parser.2.9.4.a

(3) copy header files and lib files to system area 
(eg /usr/local/opt/nodejs_http_parser)
copy setup_lib.sh to downloaded directory(http-parser)
% bash setup_lib.sh

(4) copy config file (nodejs_http_parser.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs nodejs_http_parser


