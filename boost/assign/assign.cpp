/**
 * assign.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ assign.cpp -std=c++11
// reference : https://nekko1119.hatenablog.com/entry/20121111/1352642977

#include <boost/assign.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;


/**
 * main
 */
int main()
{
	using namespace boost::assign;

		vector<int> vec;

// assignment
	{
		vec += 1, 2, 3, 4;

		list<int> l;
		l += 1, 2, 3, 4;

		map<string, int> m;
		insert(m)("aaa", 1)("bbb", 2)("ccc", 3);
	}

// initialization
	{
		vector<int> v = list_of(1)(2)(3)(4);

		list<char> l = list_of('a')('b')('c');

		map<string, double> m = map_list_of("abc", 0.0)("def", 1.0)("ghi", 2.0);
	}

// print
	for(auto v: vec){
		cout << v << ", ";
	}
	cout << endl;

	return 0;
}

// 1, 2, 3, 4, 

