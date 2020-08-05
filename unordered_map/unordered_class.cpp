/**
 * unordered_map sample
 * 2020-03-01 K.OHWADA
 */

// example : class as key
// reqire hasher

// reference : https://suzulang.com/cpp-unordered_map-my-type/

#include <string>
#include <iostream>
#include <unordered_map>
#include <stdio.h>


/**
 *  hash_combine
 *  Integrate hash values 
​​ * function that can be used universally
 * seed : in: existing hash value out: original hash value combined with hash value created from v
 * v :  value to create a new hash value
 */
template<typename T>
void hash_combine(size_t & seed, T const& v) {
    // Hash generation for basic types is provided by standard library
  std::hash<T> primitive_type_hash;

 // Combine the generated hashes. 
// this code refers to boost
  seed ^= primitive_type_hash(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


/**
 *  MyClass
 */
class MyClass {
    public:
        std::string m_v_str;
        int m_v_int;
        double m_v_double;
        std::string toString(void);
};


/**
 *  operator
 *  comparison "==" operator
 */
bool operator==(const MyClass& v1, const MyClass& v2) {

  return
    v1.m_v_str == v2.m_v_str &&
    v1.m_v_int == v2.m_v_int &&
    v1.m_v_double == v2.m_v_double; // not good to compare double with "=="
}


/**
 *  struct hash<MyClass>
 *  hasher for MyClass
 */
// The standard library provides a struct hash<> template for function objects that hash data
  // This can be used as it is because it is specialized for the basic type from the beginning (used in hash_combine above)
  // In case of selfmade class, 
// specialize myself and define operator().
template<>
  struct std::hash<MyClass> {
  public:
    size_t operator()(const MyClass& data)const {

//// Hash each class member value and combine them into one hash value
      std::size_t seed = 0;
      hash_combine(seed, data.m_v_str);
      hash_combine(seed, data.m_v_int);
      hash_combine(seed, data.m_v_double);

      return seed;

    }
};


/**
 *  double2str
 */
std::string double2str(double val)
{
    char buf[100];
    snprintf(buf, sizeof(buf),  "%.1f", val);
    std::string str = buf;
    return str;
}


/**
 *  toString
 */
std::string MyClass::toString(void)
{
    std::string str = "[ " + m_v_str + ", "
    + std::to_string(m_v_int) + ", "
    + double2str(m_v_double) + " ]";
    return str;
}



/**
 *  main
 */
int main(int argc, char *argv[])
{
  std::unordered_map<MyClass, MyClass> map;

MyClass my1( { "red"   , 1 , 1.0e0 } );
MyClass my2(  { "green" , 2 , 2.0e0 });
MyClass my3(  { "blue" , 3, 3.0e0 });
MyClass my11( { "apple"   , 11 , 11.0e0 } );
MyClass my22(  { "grass" , 22 , 22.0e0 });
MyClass my33(  { "sky" , 33 , 33.0e0 });

  map[ my1 ] = my11;
  map[ my2 ] = my22;
  map[ my3 ] = my33;

  for (auto&x : map) {
        auto first = x.first;
        auto second = x.second;
        std::cout << first.toString() << " => "
        << second.toString() << std::endl;
  }

// [ blue, 3, 3.0 ] => [ sky, 33, 33.0 ]
/// [ green, 2, 2.0 ] => [ grass, 22, 22.0 ]
// [ red, 1, 1.0 ] => [ apple, 11, 11.0 ]

  return 0;
}
 
