nss
===============

nss sample <br/>

nss : <br/>
Mozilla Network Security Services <br/>
https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS <br/>

###  install nss
brew install nss <br/>
https://formulae.brew.sh/formula/nss <br/>

You can use certutil command <br/>

> % certutil  <br/>
> certutil - Utility to manipulate NSS certificate databases <br/>
> Usage:  certutil \<command\> -d \<database-directory\> \<options\> <br/>

check pkgconfig <br/>

> % pkg-config --cflags --libs nss <br/>
> -I/usr/local/Cellar/nss/3.59/include/nss <br/>
> -I/usr/local/Cellar/nspr/4.29/include/nspr  <br/>
> -L/usr/local/Cellar/nss/3.59/lib -L/usr/local/Cellar/nspr/4.29/lib <br/> 
> -lnss3 -lnssutil3 -lsmime3 -lssl3 -lplds4 -lplc4 -lnspr4 <br/>


### sample code

 - sample1 <br/>
 Key management for keys share among multiple hosts <br/>
 - sample2 <br/>
Example code to illustrate DES enccryption/decryption using NSS. <br/>
 - sample3 <br/>
Demonstration program for hashing and MACs <br/>
 - sample4 <br/>
Example code to illustrate PKI crypto ops (encrypt with public key, decrypt with private key) <br/>
- sample5 <br/>
Example code to illustrate PKI crypto ops (encrypt with public key, decrypt with private key) <br/>
 - sample6 <br/>
 Example code to illustrate generation of a secret symmetric key ring <br/>

- version.c <br/>
display version <br/>
 
### reference
- https://github.com/nss-dev/nss


