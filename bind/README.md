bind
===============

C++ Sample <br/>
bind is the function template bind generates a forwarding call wrapper <br/>
bind function <br/>

### examples
- bind1.c <br/>
bind function <br/>
 - bind2.c <br/>
bind the arguments <br/>
- bind3.c <br/>
bind with changing the order of arguments with placeholders <br/>
- ref1.c <br/>
 bind function called by reference <br/>
- member1.c <br/>
 bind a member function of a class <br/>


### build test code <br/>
% g++  bind1.cpp  -std=c++11 <br/>

### run test code <br/>
% ./a.out <br/>

display as below <br/>
void f1() <br/>
void f2(int) 123 <br/>
void f3(int, int) 467 789 <br/>

### Reference
- https://en.cppreference.com/w/cpp/utility/functional/bind


