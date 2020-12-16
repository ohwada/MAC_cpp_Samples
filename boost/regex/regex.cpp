/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// string matching by regular expression 

// reference : http://freepg.fc2web.com/cpp/topic_boost_regex_001.html


#include <iostream>
#include <string>
#include <boost/regex.hpp>

 using namespace std;


/**
 * main
 */
int main(void)
{

string str("Free Programming For Windows.");
boost::regex reg("Free.+Windows\\.");

bool ret = boost::regex_match(str, reg);

cout << "string: "<< str << endl;

cout << "regex_match: " << reg << endl;

if (ret) {
	cout << "===> Matched." << endl;
} else {
	cout << "===> Not matched." << endl;
}

    return EXIT_SUCCESS;
}


// string: Free Programming For Windows.
// regex_match: Free.+Windows\.
// ===> Matched.

