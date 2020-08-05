/**
 * unordered_map sample
 * 2020-03-01 K.OHWADA
 */

// example : string as key

#include <iostream>
#include <unordered_map> 


/**
 *  main
 */
int main(int argc, char *argv[])
{

    std::unordered_map<std::string, std::string> mp;
    
    mp["red"] = "apple";
    mp["green"] = "grass";
    mp["blue"] = "sky";

    for (auto& x: mp) {
            std::cout << x.first << " => " << x.second << std::endl;
    }

// blue => sky
// green => grass
// red => apple

    return 0;
}