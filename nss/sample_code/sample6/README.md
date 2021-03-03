sample6 - nss
===============

Sample Code 6: <br/>
 Symmetric Keys in NSS database <br/>

- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_Sample6 <br/>

### sample code

 - sample6.c <br/>
 Example code to illustrate generation of a secret symmetric key ring <br/>
that PERSISTS in the NSS database. The symmetric keys can then be used <br/>
 without ever exposing them in the clear. <br/>

### Preparation 

 Before running this example, create the NSS database <br/>
  enter "test" when prompted for password <br/>

> % certutil -N -d . <br/>

created files <br/>
- cert9.db <br/>
- key4.db <br/>
- pkcs11.txt <br/>


### build code

> % gcc sample6.c `pkg-config --cflags --libs nss` <br/>

run code <br/>

> % ./a.out <br/>

display as below <br/>
> key length of generated key is 32 <br/>
> mechanism of key is 4229 (asked for 4229) <br/>
> Found key! <br/>


### reference
- https://github.com/nss-dev/nss

