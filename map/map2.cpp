/**
 * map sample
 * 2020-03-01 K.OHWADA
 */

// exsample : get value from key

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
 
    for(int i=1; i<10; i++){
        std::cout << i << " => " <<  mp[i] << std::endl;
    }
 
       return 0;

}