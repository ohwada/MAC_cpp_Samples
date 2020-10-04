abseil
===============

abseil Sample <br/>

Synchronization <br/>
This library includes abstractions and primitives for managing tasks across different threads. <br/>


### sample code
- synchro_mutex.cpp <br/>
exclusive access guard with mutex <br/>
- synchro_mutexlock.cpp <br/>
exclusive access guard with MutexLock <br/>


build code<br/>
g++ synchro_mutex.cpp `pkg-config --cflags --libs abseil_synchronization` <br/>

run code <br/>
./a.out <br/>

display as below <br/>
> main start: 0
> countup: 0x70000c454000 : 1
> countup: 0x70000c4d7000 : 2
> main end: 2

### Reference <br/>
- https://abseil.io/docs/cpp/guides/
- https://github.com/abseil/abseil-cpp

