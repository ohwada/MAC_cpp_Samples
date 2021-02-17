smime - openssl
===============

openssl Sample <br/>
S/MIME sign verify example 


### sample code
-  test_enc_dec.c
S/MIME encrypt decrypt example 
- test_sign_verify.c
S/MIME sign verify example 
- test_encrypt_sign_verify_decrypt.c
S/MIME encrypt sign verify decrypt example 


build code <br/>
% gcc  test_encrypt_decrypt.c `pkg-config --cflags --libs openssl` <br/>


run code  <br/>
Usage: ./a.out <br/>

display as below <br/>
> input: data/msg.txt  <br/>
> encrypt successful  <br/>
> saved: encrypted_noflags.txt  <br/>
> decrypt successful  <br/>
> saved: decrypted_encrypted_noflags.txt  <br/>
> test successful  <br/>


### Reference <br/>
- https://github.com/openssl/openssl

