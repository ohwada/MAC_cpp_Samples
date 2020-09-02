system
===============

C++ Sample <br/>
get the path of the main executable for macOS  <br/>

### executable_path.hpp
- replaceString()
- getExecutablePath()
- getExecutablePathDir()


build code <br/>
% g++  test_executable_path.cpp <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
executable path: /Users/taro/hoge/ <br/>


### system_time.hpp
- getNow();
- formatGmTime()
- formatJstTime()


build code <br/>
% g++  test_system_time.cpp <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
2020-08-29 (Sat) 01:52:03 UTC <br/>
2020-08-29 (土) 10:52:03 JST <br/>


### Reference
- https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html
- https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm


