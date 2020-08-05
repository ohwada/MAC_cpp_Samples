/**
 * unordered_map sample
 * 2020-03-01 K.OHWADA
 */

// example : vector as key
// require hasher

// reference : http://vivi.dyndns.org/tech/cpp/unordered_map.html


#include <iostream>
#include <unordered_map>
#include <vector>


/**
 *  class HashVI
 * hasher
 * calculate the hash value of a vector
 */
class HashVI {
public:
    size_t operator()(const std::vector<int> &x) const {
        const int C = 997;      // prime number
        size_t t = 0;
        for (int i = 0; i != x.size(); ++i) {
            t = t * C + x[i];
        }
        return t;
    }
};


/**
 *  vec2str
 */
std::string vec2str(std::vector<int> vec)
{
    std::string str = "[ ";
    for ( auto& x : vec) {
        str += std::to_string(x) + ", ";
    }
    str += "]";
    return str;
}


/**
 *  main
 */
int main(int argc, char *argv[])
{

// 3rd aurgment is hasher
    std::unordered_map<std::vector<int>, std::vector<int>, HashVI> mp;        

    std::vector<int> vec1 {1, 2, 3}; 
    std::vector<int> vec2 { 2, 3, 4}; 
    std::vector<int> vec3 { 3, 4, 5}; 
    std::vector<int> vec11 {11, 12, 13}; 
    std::vector<int> vec22 { 22, 23, 24}; 
    std::vector<int> vec33 { 33, 34, 35}; 
  
    mp[vec1] = vec11;
    mp[vec2] = vec22;
    mp[vec3] = vec33;

    for (auto& x: mp) {
        std::string first = vec2str(x.first);
        std::string second = vec2str(x.second);
        std::cout << first <<  " => "  << second << std::endl;
    }

// [ 3, 4, 5, ] => [ 33, 34, 35, ]
// [ 2, 3, 4, ] => [ 22, 23, 24, ]
// [ 1, 2, 3, ] => [ 11, 12, 13, ]

    return 0;
}