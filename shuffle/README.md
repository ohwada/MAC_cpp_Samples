shaffle
===============

C++ Sample <br/>
shaffle  vector / string <br/>


### random_shuffle_vector.cpp
random shufle int vector <br/>
Note: <br/>
 std::random shufle <br/>
 deprecated in C++14 <br/>
 removed in C++17 <br/>

build  code <br/>
% g++  random_shuffle_vector.cpp  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
after:  <br/>
6, 0, 3, 5, 7, 8, 4, 1, 2, 9, <br/>


### shuffle_vector.cpp
shufle int vector with mt19937 <br/>

build  code <br/>
% g++  shuffle_vector.cpp  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
after: <br/>
0, 2, 3, 8, 7, 9, 6, 4, 1, 5,  <br/>


### shuffle_string.cpp
// shufle char in stringwith mt19937 <br/>

build  code <br/>
% g++  shuffle_string.cpp  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
after: 5641390278 <br/>


### shuffle.h
shufle char in string with C random <br/>

build  code <br/>
% gcc  test_shuffle.c  <br/>

run test code <br/>
% ./a.out <br/>

display as below <br/>
 after: 0458163792 <br/>

### Reference
- https://en.cppreference.com/w/cpp/algorithm/random_shuffle

