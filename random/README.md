random
===============

C++ Sample <br/>
generate random number / string <br/>

random header is part of the pseudo-random number generation library <br/>


### rand.h
generate random number using C rand() <br/>
- getRand()

build  code <br/>
% gcc  test_rand.c <br/>

run test code <br/>
Usage: ./a.out [min] [max] <br/>
ex) <br/>
./a.out <br/>

display as below <br/>
rand: 0 -> 999 <br/>
738 <br/>
461 <br/>

### random.h
generate random number using C random() <br/>
- getRandom()

build  code <br/>
% gcc  test_random.c <br/>

run test code <br/>
Usage: ./a.out [min] [max] <br/>
ex) <br/>
./a.out <br/>

display as below <br/>
random: 0 -> 999 <br/>
 676 <br/> 
 959 <br/>

### random_char.h
generate random char with rand.h <br/>

- genRandomCharMix()
- genRandomCharLower()
- genRandomCharUpper()
- genRandomCharDegit()
- genRandomCharSpecial()

build test code <br/>
% gcc  test_random_char.c <br/>

run test code <br/>
Usage: ./a.out [mode] <br/>
ex) <br/>
./a.out <br/>

display as below <br/>
 mode 1: mix lowercase upercase degit <br/>
JGMNPegUgr <br/>
VFHA5CIrPe <br/>

### gen_random_number.cpp
generate random number vusing mt19937 <br/>

build  coode <br/>
% g++  gen_random_number.cpp <br/>

run test code <br/>
Usage: ./a.out [min] [max] <br/>
ex) <br/>
./a.out <br/>

display as below <br/>
 random: 0 -> 999 <br/>
738 <br/>
461 <br/>


### random_string.hpp
generate random string with rand.h <br/>

- genRandomStringMix()
- genRandomStringLower()
- genRandomStringUpper()
- genRandomStringDegit()

build test code <br/>
% g++  test_random_string.cpp <br/>

run test code <br/>
Usage: ./a.out [mode] <br/>
ex) <br/>
./a.out <br/>

display as below <br/>
mode 1: mix lowercase upercase degit <br/>
M5ltjQQxhg <br/>
jLhG7zOWe0 <br/>


### mkpasswd.cpp
generate password <br/>
resemble like LINUX mkpasswd <br/>
- https://linux.die.net/man/1/mkpasswd

build  code <br/>
require tclap <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/tclap <br/>

% g++  mkpasswd.cpp -DDEBUG `pkg-config --cflags --libs tclap` 

run test code <br/>
% ./a.out <br/>


display as below <br/>
len pass: 9 <br/>
min lower: 2 <br/>
min upper: 2 <br/>
min degit: 2 <br/>
min special: 1 <br/>
len lower: 4 <br/>
rBS5mi/n <br/>


### Reference
- https://en.cppreference.com/w/cpp/header/random
- https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm
