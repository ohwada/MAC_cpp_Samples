thread
===============

C++ Sample <br/>
run two threads <br/>

std::thread <br/>
Threads allow multiple functions to execute concurrently. <br/>


### multi threads
- multi_threads.cpp <br/>
communicate between threads via global variables <br/>
- mutex1.cpp <br/>
exclusive access guard in function <br/>
- mutex2.cpp <br/>
 exclusive access guard in class methed <br/>
- condition_variable.cpp <br/>
communicate between threads via condition variable <br/>

build code <br/>
% g++  multi_thread.cpp -std=c++11 <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
A) send to B <br/>
B) recieve from A <br/>


### tiny_race.c
detects data races with ThreadSanitizer <br/>

build code <br/>
% gcc -fsanitize=thread -g -O1 tiny_race.c <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
SUMMARY: ThreadSanitizer: data race tiny_race.c:20 in threadB <br/>


### Reference
- https://en.cppreference.com/w/cpp/thread/thread
- https://en.cppreference.com/w/cpp/thread/lock_guard
- https://clang.llvm.org/docs/ThreadSanitizer.html


