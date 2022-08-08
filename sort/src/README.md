sort: src
===============

C++ Samples 

### Samples
- sort_vector.cpp 
- sort_struct.cpp
- sort_string.cp  


build code <br/>
% g++  sort_vector.cpp -std=c++11 <br/>

run  code <br/>
% ./a.out <br/>

display as below <br/>
before sort <br/>
3 <br/>
4 <br/>
5 <br/>
1 <br/>
2 <br/>
sort less <br/>
1 <br/>
2 <br/>
3 <br/>
4 <br/>
5 <br/>

### sort_struct.cpp
sort struct with two member variables <br/>

build code <br/>
% g++  sort_struct.cpp  -std=c++11 <br/>

run code <br/>
% ./a.out <br/>

display as below  <br/>
after sort <br/>
 [  num: 10 ; str: eee ] <br/>
 [  num: 20 ; str: ddd ] <br/>
 [  num: 30 ; str: aaa ] <br/>


### sort_string.cp
sort char in string <br/>

build code <br/>
% g++  sort_string.cpp  -std=c++11 <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
please enter the random alphabets <br/>
\> <br/>

when enter "asdf <br/>
 sort small to large <br/>
adfs <br/>
 sort large to small <br/>
sfda <br/>


### qsort.cp
sorts the array in ascending order using qsort() <br/>

build code <br/>
% gcc  qsort.c   <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
brfore:  <br/>
 4,  2,  3,  6,  3,  2,  1,  3,  7,  5,  <br/>
after:  <br/>
 1,  2,  2,  3,  3,  3,  4,  5,  6,  7,  <br/>


### Reference
- https://en.cppreference.com/w/cpp/algorithm/sort
- https://en.cppreference.com/w/c/algorithm/qsort

