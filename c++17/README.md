c++17
===============


### Whats New in C++17

Reference:    
- https://en.cppreference.com/w/cpp/17  
- https://qiita.com/Reputeless/items/db7dda0096f3ae91d450  


### Samples:  

- clamp.cpp  
 std::clamp  
https://en.cppreference.com/w/cpp/algorithm/clamp  

- tuple.cpp
std::tuple  
https://en.cppreference.com/w/cpp/utility/tuple  

- random_sample.cpp  
 std::sample  
https://en.cppreference.com/w/cpp/algorithm/sample  

 - optional.cpp
 std::optional  
https://en.cppreference.com/w/cpp/utility/optional  


- emplace_back.cpp  
std::vector<T,Allocator>::emplace_back  
https://en.cppreference.com/w/cpp/container/vector/emplace_back  

- insert_or_assign.cpp
std::map::insert_or_assign  
https://doc.bccnsoft.com/docs/cppreference2015/en/cpp/container/map/insert_or_assign.html

- size.cpp  
std::size  
https://en.cppreference.com/w/cpp/iterator/size

- gcd.cpp  
std::gcd  
https://en.cppreference.com/w/cpp/numeric/gcd  

- not_fn.cpp  
std::not_fn  
https://en.cppreference.com/w/cpp/utility/functional/not_fn  

- hypot.cpp  
std::hypot  
https://en.cppreference.com/w/cpp/numeric/math/hypot

- merge.cpp  
 std::unordered_set::merge  
https://en.cppreference.com/w/cpp/container/unordered_set  

-invoke.cpp  
std::invoke  
https://en.cppreference.com/w/cpp/utility/functional/invoke  

### Build and Run:  
% make clamp  
or  
g++ clamp.cpp -o clamp -std=c++17 

% ./clamp   
> 50  
> 0  
> 100  


 ### boyer_moore.cpp  
 std::boyer_moore_searcher  
https://en.cppreference.com/w/cpp/utility/functional/boyer_moore_searcher  

Note:
use /usr/local/bin/g++-11  
because error with /usr/bin/g++  



