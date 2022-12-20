/**
 * random_string.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>


const  std::string CHARS( 
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

const int MIN = 0;
const int MAX = CHARS.size() -1;

boost::random::uniform_int_distribution<> dist(MIN, MAX);

boost::random::random_device seed_gen;
boost::random::mt19937 gen(seed_gen);


/**
 * getRandomChar
 */
char getRandomChar()
{
    int index = dist(gen);
    char c =  CHARS[index];
    return c;
}


/**
 * genRandomString
 */
std::string genRandomString(int length) 
{
    std::string text(length, '.');
    std::generate_n(text.begin(), length,  getRandomChar );
    return text;
}

 using namespace std;

/**
 * main
 */
int main()
{

    const int LEN = 10;
    const int COUNT = 10;
  
    for (int i = 0; i < COUNT; ++i) {
        auto str = genRandomString(LEN); 
        cout << str << endl;
    }

    return 0;
}


// y5M1kqUsCx
// Bi9IG8csOv
// AYuAVv6Y5t

