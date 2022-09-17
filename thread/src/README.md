thread: src
===============

C++ Sample 
run two threads 

std::thread 
Threads allow multiple functions to execute concurrently. 


### multi threads
- multi_threads.cpp 
communicate between threads via global variables 
- mutex1.cpp <
exclusive access guard in function 
- mutex2.cpp 
 exclusive access guard in class methed 
- condition_variable.cpp 
communicate between threads via condition variable 

build code 
% g++  multi_thread.cpp -std=c++11 

run code 
% ./a.out 
> A) send to B 
> B) recieve from A 

