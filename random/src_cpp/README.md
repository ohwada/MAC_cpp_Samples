random src_cpp
===============

C++ Sample <br/>
generate random number / string <br/>


### test_rand_int.cpp <br/>
generate random integer vusing mt19937 <br/>

Build  and Run file <br/>
% g++  test_rand_int.cpp -o integer <br/>
./integer <br/>

display as below <br/>
 random: 0 -> 999 <br/>
738 <br/>
461 <br/>


### test_rand_real.cpp <br/>
generate random floatig point number vusing mt19937 <br/>

Build  and Run file <br/>
% g++  test_rand_real.cpp -o real <br/>
./floation <br/>

### random_string.hpp <br/>
generate random string with rand.h <br/>
- genRandomStringMix()
- genRandomStringLower()
- genRandomStringUpper()
- genRandomStringDigit()

Buld and Run file <br/>
% g++  test_random_string.cpp -o string <br/>
./string <br/>

display as below <br/>
mode 1: mix lowercase upercase degit <br/>
M5ltjQQxhg <br/>
jLhG7zOWe0 <br/>

### passwd.hpp <br/>
generate random password <br/>

Build and Run file 
% g++  test_passwd.cpp -o passwd 
% ./mkpasswd <br/>

display as below <br/>
> dhJI96&k2
> 69&Jhkd2I

### mkpasswd.cpp <br/>
generate password <br/>
resemble like LINUX mkpasswd <br/>
- https://linux.die.net/man/1/mkpasswd

Require tclap <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/tclap <br/>

Build and Run file 
% g++  mkpasswd.cpp -DDEBUG -o mkpasswd `pkg-config --cflags --libs tclap` 
% ./mkpassword <br/>

display as below <br/>
> l : 9 <br/>
> d: 2 <br/>
> c:2 <br/>
> C: 2 <br/>
>s: 1 <br/>
> ypDH93_3S <br/>
> Dp9Sy33_H <br/>


### Reference <br/>
- https://en.cppreference.com/w/cpp/header/random

