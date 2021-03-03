sample2 - nss
===============

NSS Sample Code 2: <br/>

Symmetric Encryption <br/>
Example code to illustrate DES enccryption/decryption using NSS. <br/>
 The example skips the details of obtaining the Key & IV to use, and just uses a hardcoded Key & IV. <br/>

- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_Sample2 <br/>

### sample code

 - sample2.c <br/>
Example code to illustrate DES enccryption/decryption using NSS. <br/>

build code <br/>
gcc sample2.c `pkg-config --cflags --libs nss` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> Clear Data: Encrypt me! <br/>
> Encrypted Data: ca 61 45 4f 07 50 8c 21 bd 86 46 ee fd fa 3f 9f  <br/>
> Decrypted Data: Encrypt me! <br/>


### reference
- https://github.com/nss-dev/nss

