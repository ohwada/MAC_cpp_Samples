shaffle drc cpp
===============

C++ Sample <br/>
shaffle  vector / string <br/>


### random_shuffle_vector.cpp
random shufle int vector <br/>
Note: <br/>
 std::random shufle <br/>
 deprecated in C++14 <br/>
 removed in C++17 <br/>

Build and Run  file <br/>
% g++  random_shuffle_vector.cpp -o random  <br/>
% ./random <br/>

display as below <br/>
after:  <br/>
6, 0, 3, 5, 7, 8, 4, 1, 2, 9, <br/>


### shuffle_vector.cpp
shufle int vector with mt19937 <br/>

Build and Run file <br/>
% g++  shuffle_vector.cpp -o mt <br/>
% ./mt <br/>

display as below <br/>
after: <br/>
0, 2, 3, 8, 7, 9, 6, 4, 1, 5,  <br/>


### shuffle_string.cpp
// shufle char in stringwith mt19937 <br/>

Build  and Run file <br/>
% g++  shuffle_string.cpp -o string <br/>
% ./string <br/>

display as below <br/>
after: 5641390278 <br/>


### Reference
- https://en.cppreference.com/w/cpp/algorithm/random_shuffle
