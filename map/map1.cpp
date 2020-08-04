/**
 * map sample
 * 2020-03-01 K.OHWADA
 */

// example : int as key

#include <iostream>
#include <map>
 

/**
 *  main
 */
int main(int argc, char *argv[])
{
        std::map<int,int> mp;
 
    for(int i=0; i<10; i++){
        mp[i] = 111 * i;
    }
 
        for (auto& x: mp) {
                std::cout << x.first << " => " << x.second << std::endl;
        }
 
        return 0;
}