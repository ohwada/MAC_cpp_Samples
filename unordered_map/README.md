unordered_map
===============

C++ Sample <br/>
unordered map with string key or class /vector / enum <br/>
		
Unordered map is an associative container that contains key-value pairs with unique keys <br/

### examples
- unordered_string.cpp <br/>
string as key <br/>
-  unordered_class.cpp <br/>
class as key <br/>
- unordered_vector.cpp <br/>
vector as key <br/>
- unordered_enum.cpp <br/>
enum as key <br/>

### build test code <br/>
% g++  unordered_string.cpp  -std=c++11 <br/>

run test code <br/>
./a.out <br/>

display as below <br/>
// blue => sky <br/> 
// green => grass <br/>
// red => apple <br/>

### unordered_enum.cpp 
enum as key <br/>

build test code <br/>
% g++  unordered_enum.cpp  -std=c++14 <br/>

Note: <br/>
enabe c++14 compile option <br/>
becuase support enum with hash since c++14 <br/>
https://cpprefjp.github.io/reference/functional/hash.html <br/>

run test code <br/>
./a.out <br/>

display as below <br/>
Type Saturn = \> [ Saturn, 5 ] <br/>
Type Jupiter = //\> [ Jupiter, 4 ] <br/>


### Reference
- https://en.cppreference.com/w/cpp/container/unordered_map <br/>

