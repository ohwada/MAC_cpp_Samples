c11
===============

C Sample <br/>
since std C11 <br/>


### check_stdc_version.c
check stdc version <br/>

build  code <br/>
% gcc   check_stdc_version.c  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
Compliant with C11 <br/>

### timespec.c
display current timt <br/>

build  code <br/>
% gcc  timespec.c  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
timespec: 1597124880 (sec) : 247937000 (nsec) <br/>
Time: 2020-08-11 (Tue) 05:48:00 UTC <br/>
時刻: 2020-08-11 (火) 14:48:00 JST <br/>


### random.c
generate random number <br/>

build  code <br/>
% gcc  random.c  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
1188720232 <br/>
599176564 <br/>

### gets.c
sample for gets() <br/>
gets() was deprecated in C11 <br/>
This program gives the following warning when running <br/>
this program uses gets(), which is unsafe <br/>

### scanf.c
sample for scanf() <br/>

### input.h
get Chars / Int from stdin <br/>
substitute for gets() <br/>
- getInputChars() <br/>
- gets_sub() <br/>
- getChars() <br/>
- getInt() <br/>

test program for input.h <br/>
- test_get_input_chars.c
- test_get_chars.c
- test_gets_sub.c
 - test_get_int.c



### Reference
- https://en.wikipedia.org/wiki/C11_(C_standard_revision)
- https://smartbear.de/blog/test-and-monitor/c11-a-new-c-standard-aiming-at-safer-programming/

