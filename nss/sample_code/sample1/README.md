sample1 - nss
===============

NSS Sample Code 1: <br/>

Key Generation and Transport Between Servers. <br/>
This is an example program that demonstrates how to do key generation and transport between cooperating servers.  <br/>

- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_Sample1<br/>

### sample code

 - sample1.cpp <br/>
 Key management for keys share among multiple hosts

build code <br/>
g++ sample1.cpp `pkg-config --cflags --libs nss` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> getPrivateKey: list = 0x0 <br/>
> getPrivateKey: list = 0x7ff8ff818420 <br/>
> getPrivateKey: list = 0x7ff901009820 <br/>
> getPrivateKey: list = 0x0 <br/>
> getPrivateKey: list = 0x7ff90080f420 <br/>
> Wrapped Encryption Key <br/>
> length: 128 <br/>
> 87 3b 5b b5 9e 39 99 b1 5f 2c 22 7c f6 69 6e 3a 9d 89 57 67 c2 43 40 a6 7c c6 22 7b c5 96 7b 2d 1a 1d 6d 14 0d 69 c6 e5 ef aa de e7 cd 77 a7 e7 55 89 1f 90 3e 1b 1f a9 b9 bf 76 0a 93 02 19 5b bc b1 37 14 e1 c1 98 41 e7 03 01 14 e5 21 e3 e1 86 8b 21 7a 53 fc a0 22 02 fe 58 5d 9f 49 df 31 3e 7a 2e 0b 1a d7 6b 63 4b 72 8e d2 0a 8e 00 7f c5 c6 7e 7f 2e 99 ba fd 96 00 c7 ab 3f e9 bd 46  <br/>
> Wrapped MAC Key <br/>
> length: 128 <br/>
> 69 dc 4a 7f 4d 5b b7 a9 4e 42 66 28 ec 6b d7 97 25 2a a0 9c db 60 40 d4 06 fa b4 a5 08 2e 03 03 fd 96 96 35 a9 95 30 3b 5f 08 be 6a f5 93 d2 21 91 17 46 0b 54 ef c7 db 0a 9d 75 46 7c 30 1f 97 63 9b 75 21 d1 bc 8a 3f 91 ac 3c 5e 71 89 48 1c 34 28 f7 5b 38 c4 56 2d 57 ee d6 73 51 cb 3f d3 e9 88 ae fc c9 db e3 06 1f aa c5 28 8c f0 7e 8b 87 8a 4a 0b 2d 9d 8a a5 7a af 0c 70 a1 f6 ca 8c  <br/>
> getPrivateKey: list = 0x7ff900009020 <br/>
> List Private Keys <br/>
> Key: Server1 <br/>
> Key: Server2 <br/>
> Done <br/>

created files <br/>
- cert9.db	<br/>
- key4.db <br/>
- pkcs11.txt <br/>


### reference
- https://github.com/nss-dev/nss


