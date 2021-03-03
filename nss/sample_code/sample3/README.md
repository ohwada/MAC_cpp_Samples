sample3 - nss
===============

Sample Code 3: <br/>
Hashing, MAC <br/>

- https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_Sample3 <br/>

### sample code

 - sample3.cpp <br/>
Demonstration program for hashing and MACs <br/>

build code <br/>
g++ sample3.cpp `pkg-config --cflags --libs nss` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> Part 1 -- Simple hashing <br/>
> length: 16 <br/>
> 74 63 9a 51 ba 5c 5a c8 37 a6 30 11 a5 1d cb d5 <br/>
> Part 2 -- Hashing with included secret key
0x7f95f1c132a0 <br/>
> length: 16 <br/>
> d2 d0 5b 90 3f e2 54 92 35 f8 7b c7 38 14 85 fb <br/>
> Part 3 -- MAC (with secret key) <br/>
> length: 16 <br/>
> f4 8d 91 08 2c 08 c7 7d 62 e1 be d3 61 5c e8 55 <br/>


### reference
- https://github.com/nss-dev/nss

