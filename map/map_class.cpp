/**
 * map sample
 * 2020-03-01 K.OHWADA
 */

// example : class (struct) as key
// define operator "<" in the class
// reference : https://qiita.com/sukakako/items/4f60a64eb9e7b5ffcf16

#include <iostream>
#include <map>      


/**
 *  struct KeyData
 */
    struct KeyData
    {
        std::string name;
        int id;

     // constractor
        KeyData()
            : name()
            , id(0)
         {
            // nop
         }

    // constractor
        KeyData
        (
            std::string name_,
            int id_
        )
            : name(name_)
            , id(id_)
        {
            // nop
        }


    // comparison operator "<"
        bool operator<(const KeyData& value) const
        {

                if (name < value.name) {
                    return true;
                }

             if (name == value.name) {
                 if (id < value.id) {
                    return true;
                }
            }

            return false;
        }

    };


/**
 *  keydata2str
 */
std::string keydata2str(KeyData kd)
{
    std::string str = "[ " 
        + kd.name + ", "
        + std::to_string( kd.id ) + " ]";

    return str;
}


/**
 *  main
 */
int main(int argc, char *argv[])
{

     std::map<KeyData, KeyData> mp;

    KeyData kd1("red",     1);
     KeyData kd2("green",   2);
    KeyData kd3("blue",     3);
    KeyData kd11("apple",     11);
     KeyData kd22("grass",   22);
    KeyData kd33("sky",     33);

    mp[kd1] = kd11;
    mp[kd2] = kd22;
    mp[kd3] = kd33;

    for (auto &x : mp)
    { 
        std::cout << keydata2str(x.first)<< " => " 
        << keydata2str(x.second) << std::endl;
    }

// [ blue, 3 ] => [ sky, 33 ]
// [ green, 2 ] => [ grass, 22 ]
// [ red, 1 ] => [ apple, 11 ]

    return 0;
}
