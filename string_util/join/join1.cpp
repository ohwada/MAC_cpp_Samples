/**
 * join1.cpp
 * 2022-06-01 K.OHWADA
 */


//using std::copy std::stringstream
// https://www.techiedelight.com/ja/implode-a-vector-of-strings-into-a-comma-separated-string-in-cpp/
// https://marycore.jp/prog/cpp/vector-join/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cassert>


/**
 * join
 */
std::string join(std::vector<std::string> const &strings, std::string glue)
{
	std::stringstream ss;
	std::copy(strings.begin(), strings.end(),
		std::ostream_iterator<std::string>(ss, glue.c_str()));
	std::string str = ss.str();

// remove trailing delimiter
str.erase(str.size() - glue.size());
return str;
}


/**
 *  dump_vec
 */
void dump_vec( std::vector<std::string> vec, std::string delmita )
{
    for(auto v: vec){
        std::cout << v << delmita;
    }
    std::cout << std::endl;
}

using namespace std;


/**
 * main
 */
int main()
{
	vector<string> strings = {"A", "B", "C", "D"};

    string expect("A, B, C, D");

	string glue = ", ";

string delmita = " | ";

    cout << "vector" << endl;
	 dump_vec(strings, delmita );

    cout << endl;
	cout << "join: |"<< glue << "| " << endl;

	auto str = join(strings, glue);

    cout << "string" << endl;
	cout << str << endl;

    assert(str == expect );

    cout << "successful" << endl;

	return 0;
}


// vector
// A | B | C | D | 
// join: |, | 
// string
// A, B, C, D
// successful
