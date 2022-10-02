/**
 * test_zip_util.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ test_zip_util.cpp -std=c++11

#include <iostream>
#include <string>
#include <cassert>
#include "zip_util.hpp"


using namespace std;


/**
 *  main
 */
int main() 
{

	const string FILEPATH("test/aaa/bbb/sample.txt");

	cout << FILEPATH << endl;

    auto list = get_parent_list(FILEPATH);

    for(auto str: list){
	    cout << str << endl;
    }

    assert( list.size() == 3 );
    assert( list[0] == "test" );
    assert( list[1] == "test/aaa" );

    assert( is_zip_dir("test/") );
    assert( is_zip_dir("test.txt") == false );

    return 0;
}


