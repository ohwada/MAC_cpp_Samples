/**
 * vector_to_char_array.cpp
 * 2020-03-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include <vector>
 #include <cassert>


/**
 * dump_vec
 */
void dump_vec(std::string name, std::vector<char> vec)
{
    std::cout << name << ": ";
    for(auto v: vec) {
        std::cout << v << ", ";
    } // for
    std::cout << std::endl;
}

/**
 * dump_char_array
 */
void dump_char_array(char* data, size_t size)
{
    for(int i=0; i<size; i++){
        std::cout << data[i] << ", ";
    }
    std::cout << std::endl;
}


using namespace std;


/**
 * main
 */
int main()
{
    vector<char> vec1 = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };

    dump_vec("vec1", vec1);

    char* data = vec1.data();
    size_t data_size = vec1.size();

    cout << "array: ";
    dump_char_array(data, data_size);

  vector<char> vec2;

    for(int i=0; i<data_size; i++){
        vec2.push_back( data[i] );
    } // for

    dump_vec("vec2", vec2);

    assert(vec1 == vec2);

    cout << "successful" << std::endl;

    return 0;
}

