json_dto: setup
===============


### Prerequisites
- C++14 compiler
- rapidjson

### Install
(1) Download souce files  
git clone https://github.com/Stiffstream/json_dto

(2) copy header files to system area 
(eg /usr/local/opt/json_dto)
copy setup_hdr.sh to downloaded directory
% bash setup_hdr.sh

(4) copy config file (json_dto.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags json_dto


