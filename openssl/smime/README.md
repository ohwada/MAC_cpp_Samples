smime - openssl
===============

openssl S/MIME sample <br/>


### sample code
send mail from Jiro to Taro <br/>
- test_encrypt.c <br/>
S/MIME encrypt decrypt example <br/>
- test_sign.c <br/>
S/MIME sign verify example <br/>

build code <br/>
% gcc test_encrypt.c  `pkg-config --cflags --libs openssl` -o test <br/>

run code  <br/>
Usage: ./test  [input] <br/>

display as below <br/>
> saved: encrypted.txt <br/>
> saved: decrypted.txt <br/>
> successful <br/>


### Reference <br/>
- https://github.com/openssl/openssl

