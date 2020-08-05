/**
 * unordered_map sample
 * 2020-03-01 K.OHWADA
 */

// example : enum as key

// Note:
// enable comple option c++14
// becuase support enum with hash since c++14 <br/>
// https://cpprefjp.github.io/reference/functional/hash.html 

// reference : https://www.it-swarm.dev/ja/c%2B%2B/enum%E3%82%AF%E3%83%A9%E3%82%B9%E3%82%92unorderedmap%E3%82%AD%E3%83%BC%E3%81%A8%E3%81%97%E3%81%A6%E4%BD%BF%E7%94%A8%E3%81%A7%E3%81%8D%E3%81%BE%E3%81%9B%E3%82%93/1042035085/

#include <iostream>
#include <unordered_map>


/**
 *  class Planet
 */
class Planet {
    public:
        std::string m_v_str;
        int m_v_int;
        std::string toString(void);
};


/**
 *  toString
 */
std::string Planet::toString(void)
{
    std::string str = "[ " + m_v_str + ", "
    + std::to_string(m_v_int) + " ]" ;
    return str;
}


/**
 *   enum class Type
 */
enum class Type {
    Mercury,
    Venus,
    Mars,
    Jupiter,
    Saturn
};


/**
 *   type2str
 */
std::string  type2str(Type type)
{
    std::string str;
    switch(type)
    {
        case Type::Mercury:
            str = "Type Mercury";
            break;
        case Type::Venus:
            str = "Type Venus";
            break;
        case Type::Mars:
            str = "Type Mars";
            break;
        case Type::Jupiter:
            str = "Type Jupiter";
            break;
        case Type::Saturn:
            str = "Type Saturn";
            break;
    }
    return str;
}


/**
 *  main
 */
int main(int argc, char *argv[])
{

    std::unordered_map<Type, Planet> mp;

    Planet mercury( {"Mercury", 1} );
    Planet venus ( {"Venus", 2} );
    Planet mars( {"Mars", 3} );
    Planet jupiter( {"Jupiter", 4} );
    Planet saturn( {"Saturn", 5} );

    mp[Type::Mercury] = mercury;
    mp[Type::Venus] = venus;
    mp[Type::Mars] = mars;
    mp[Type::Jupiter] = jupiter;
    mp[Type::Saturn] = saturn;

    for (auto& x: mp) {
            auto second = x.second;
            std::cout << type2str(x.first) << " => " <<  second.toString() << std::endl;
    }

// Type Saturn => [ Saturn, 5 ]
// Type Jupiter => [ Jupiter, 4 ]
// Type Mars => [ Mars, 3 ]
// Type Venus => [ Venus, 2 ]
// Type Mercury => [ Mercury, 1 ]

    return 0;
}
