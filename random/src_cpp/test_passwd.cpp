/**
 * test_passwd.cpp
 * 2022-06-01 K.OHWADA
 */

// generate password with passwd.hpp

#include<iostream>
#include "passwd.hpp"
 

using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{
	const int len_lower = 2;
	const int len_upper = 2;
	const int len_digit = 2;
	const int len_special = 1;
	const int len_mix = 2;

    string passwd = genPasswd(len_lower, len_upper, len_digit, len_special, len_mix );

    cout << passwd << endl;

	string text = shuffle(passwd);

    cout << text << endl;

    return EXIT_SUCCESS;
}

