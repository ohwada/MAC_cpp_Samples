/**
 * map sample
 * 2020-03-01 K.OHWADA
 */

// example : 
// when get value from an element that does not exist

// Note:
// performing an insertion if such key does not already exist.
// https://en.cppreference.com/w/cpp/container/map/operator_at

#include <iostream>
#include <map>
 

/**
 *  main
 */
int main(int argc, char *argv[])
{

        std::map<int,int> mp;
 
// access an element that does not exist
    for (int i=0; i<10; i++) {
        std::cout << mp[i] << std::endl;	
    }
 
    for (auto& x:mp) {
                std::cout << x.first << " => " << x.second << std::endl;
    }
    
    return 0;
}