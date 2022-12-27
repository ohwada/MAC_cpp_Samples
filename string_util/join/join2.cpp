/**
 * join2.cpp
 * 2022-06-01 K.OHWADA
 */

// using std::accumulate
// https://www.techiedelight.com/ja/implode-a-vector-of-strings-into-a-comma-separated-string-in-cpp/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cassert>


/**
 * join
 */
std::string join(std::vector<std::string> const &strings, std::string glue)
{
	if (strings.empty()) {
		return std::string();
	}

	return std::accumulate(strings.begin() + 1, strings.end(), strings[0],
		[&glue](std::string x, std::string y) {
			return x + glue + y;
		}
	);
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


