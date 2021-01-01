system
===============

system sample <br/>


### src
C++ sample <br/>
- test_executable_path.cpp <br/>
get executable path for macOS <br/>

### c_src
C sample <br/>
- test_mac_executable_path.c <br/>
get executable path for macOS <br/>
- test_get_home_directory.c <br/>
get home directory <br/>
- get_hostname.c <br/>
get hostname <br/>


### executable_path.hpp
get the path of the main executable for macOS  <br/>

- replaceString()
- getExecutablePath()
- getExecutablePathDir()


build code <br/>
% g++  test_executable_path.cpp <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> executable path: /Users/taro/hoge/ 


### home_directory.h
 get home directory <br/>

- getEnvHome(void);
- getPwDir(void);
- getHomeDir(void);

build code <br/>
% gcc  test_get_home_directory.c <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> env home: /Users/hoge 
> pw dir: /Users/hoge 
> home dir: /Users/hoge

### Reference
- https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dyld.3.html

