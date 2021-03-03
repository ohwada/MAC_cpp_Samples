sample5 - nss
===============

Sample Code 5:   <br/>
PKI Encryption with a raw public & private key in DER format  <br/>

- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_Sample5 <br/>

### sample code

 - sample5.c <br/>
Example code to illustrate PKI crypto ops (encrypt with public key, decrypt with private key) <br/>

build code <br/>
gcc sample5.c `pkg-config --cflags --libs nss` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> Public Key Modulus 64 bytes  <br/>
> Buffer being encrypted =  <br/>
> ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJK  <br/>
> Result of decryption, outlen = 64  <br/>
> Result of decryption, buf =   <br/>
> ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJK  <br/>


### reference
- https://github.com/nss-dev/nss

