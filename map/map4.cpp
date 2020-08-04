/**
 * map sample
 * 2020-03-01 K.OHWADA
 */

// example : check the existence of the key with find

#include <iostream>
#include <map>
 

/**
 *  main
 */
int main(int argc, char *argv[])
{
        std::map<int,int> mp;
 

// generate only even keys
    for(int i=0; i<10; i+=2){
        mp[i] = 111 * i;
    }
 
    for(int i=0; i<10; i++){
            std::cout << i << " => " ;
        if (mp.find(i) == mp.end() ) {
            std::cout <<  "not found" << std::endl;
        } else {
            std::cout <<  mp[i] << std::endl;
        }
    }

    return 0;
}