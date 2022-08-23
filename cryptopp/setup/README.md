cryptopp: setup
===============


### Install
(1) Download souce files  
git clone  https://github.com/weidai11/cryptopp

(2) Create libcryptopp.a  
(2-1) add flowing in GNUmakefile.
> CXXFLAGS+=-stdlib=libc++

OS X (Command Line)
https://www.cryptopp.com/wiki/OS_X_(Command_Line)

(2-2) build
cd downloaded directory (cryptopp)  
% make  

TODO:  
get the following error  
> Undefined symbols for architecture x86_64:  
> CryptoPP::ChaCha_OperateKeystream_AVX2  


(3) copy header files and lib files to system area 
(eg /usr/local/opt/cryptopp)
copy setup_lib.sh to downloaded directory
% bash setup_lib.sh

(4) copy config file (cryptopp.pc) to system area 
% bash setup_pkgconfig.sh
% pkg-config --cflags --libs cryptopp

