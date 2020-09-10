gflog
===============

glog sample <br/>
 <br/>

glog : <br/>
Google logging module <br/>
https://github.com/google/glog <br/>

### install glog
% brew install glog <br/>
https://formulae.brew.sh/formula/glog <br/>


### write_log.cpp
write log to file <br/>

build code  <br/>
% g++ write_log.cpp -std=c++11 `pkg-config --cflags --libs libglog` -o write <br/>

run code <br/
% ./write <br/>

display as below <br/>
E0908 10:18:27.237275 248446400 write_log.cpp:27]  <br/>ERROR

created log files on log directory <br/>
- write.ERROR
- write.FATAL
- write.INFO
- write.WARNING
- write.MacBook-Air.local.log.ERROR.20200908-085145.40308
- write.MacBook-Air.local.log.FATAL.20200908-085145.40308
- write.MacBook-Air.local.log.INFO.20200908-085145.40308
- write.MacBook-Air.local.log.WARNING.20200908-085145.40308


### stacktrace.cpp
display stack trace when CRUSH <br/>

build code  <br/>
% g++ stacktrace.cpp -std=c++11 `pkg-config --cflags --libs libglog` -o trace  <br/>

run code <br/
% ./trace <br/>

display as below <br/>
> stack trace: 
>    @     0x7fff6ca515fd _sigtramp
>    @        0x1091a6f37 div_zero()
>    @        0x1091a6f49 func()
>    @        0x1091a6f7c main


### Reference <br/>
- https://github.com/google/glog

