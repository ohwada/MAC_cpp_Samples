sample4 - nss
===============

NSS Sample Code 4: <br/>
PKI Encryption <br/>

- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_Sample4 <br/>

### sample code

 - sample4.c <br/>
Example code to illustrate PKI crypto ops (encrypt with public key, decrypt with private key) <br/>

### Preparation 

Code assumes that you have set up a NSS database with a certificate and a private key. 
The db password should be "test" and the cert nickname should be "TestCA"
 Here is one way of doing it:

 (1) create CA cert db, if -f not provided, prompts for passwd

 > % certutil -N -d . <br/>

created files <br/>
- cert9.db <br/>
- key4.db <br/>
- pkcs11.txt <br/>


 (2) create CA cert, self-signed, generates key-pair <br/>

 > % certutil -S -s "CN=Test CA, O=BOGUS Inc, L=Mtn View, ST=CA, C=US" -n TestCA -t CTu,CTu,CTu -v 60 -x -d .   <br/>

A random seed must be generated that will be used in the
creation of your key.  One of the easiest ways to create a
random seed is to use the timing of keystrokes on a keyboard.
To begin, type keys on the keyboard until this progress meter
is full.  DO NOT USE THE AUTOREPEAT FUNCTION ON YOUR KEYBOARD!

(3) confirm certificate list <br/>

> % certutil -L -d . <br/>
> Certificate Nickname   Trust Attributes <br/>
> TestCA CTu,Cu,Cu <br/>


### build code 

> % g++ sample3.cpp `pkg-config --cflags --libs nss` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> Public Key Modulus 256 bytes <br/>
> Buffer being encrypted =  <br/>
> ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU <br/>
> Result of decryption, outlen = 256 <br/>
> Result of decryption, buf = <br/>
> ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU <br/>


### reference
- https://github.com/nss-dev/nss

