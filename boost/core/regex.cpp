/**
 *  regex.cpp
 * 2022-06-01 K.OHWADA
 */


// http://freepg.fc2web.com/cpp/topic_boost_regex_001.html

#include <iostream>
#include <boost/regex.hpp>

 using namespace std;


/**
 *  main
 */
int main()
{

{
    string str("Free Programming For Windows.");
    boost::regex reg("Free.+Windows\\.");

    if (boost::regex_match(str, reg)) {
	    cout << "===> Matched." << endl;
    } else {
	    cout << "===> Not matched." << endl;
    }
}

{
    string str("Free Programming For Windows.");
    boost::regex reg("P\\w+");
    string str2 = regex_replace(str, reg, "Software");
    cout << str2 << endl;
}

    return 0;
}

