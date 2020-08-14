/**
 * random sample
 * 2020-03-01 K.OHWADA
 */

// generate password with random_string.hpp
// resemble like LINUX mkpasswd
// reference : https://linux.die.net/man/1/mkpasswd
// command line paser using tclap

#include<iostream>
#include <random>
#include <tclap/CmdLine.h>
#include "random_string.hpp"
 
using namespace std;


#ifdef DEBUG
    const bool FLAG_DEBUG = true;
#else
    const bool FLAG_DEBUG = false;
#endif


/**
 * main
 */
int main(int argc, char *argv[])
{

	int len_passwd = 0;
	int min_lower = 0;
	int min_upper = 0;
	int min_digit = 0;
	int min_special = 0;

	try {  

	TCLAP::CmdLine cmd("mkpasswd", ' ', "0.1");

// mkpasspwd command line option
// https://linux.die.net/man/1/mkpasswd
// this program not support -p -2 -v
	TCLAP::ValueArg<int> lArg("l", "length", "he length of the password", false, 9, "int");
	TCLAP::ValueArg<int> uArg("C", "upper", "the minimum number of uppercase alphabetic characters", false, 2, "int");
	TCLAP::ValueArg<int> cArg("c", "lower", "the minimum number of lowercase alphabetic characters", false, 2, "int");
	 TCLAP::ValueArg<int> dArg("d", "digit", "the minimum number of digits", false, 2, "int");
	TCLAP::ValueArg<int> sArg("s", "special", "the minimum number of special characters", false, 1, "int");

	cmd.add( lArg );
	cmd.add( cArg );
	cmd.add( uArg );
	cmd.add( dArg );
	cmd.add( sArg );

	cmd.parse( argc, argv );

	len_passwd = lArg.getValue();
	min_lower = cArg.getValue();
	min_upper = uArg.getValue();
	min_digit = dArg.getValue();
	min_special = sArg.getValue();
	
	} 
    catch (TCLAP::ArgException &e) 
	{ 
        if(FLAG_DEBUG) {
            cerr << "error: " << e.error() << " for arg " << e.argId() << endl; 
        }
    }

    int sum =  min_lower + min_upper + min_digit + min_special;

    char FORMAT [] = "impossible to generate" 
    " %d-character password"
    " with %d numbers,"
    " %d lowercase letters,"
    " %d uppercase letters"
    " and %d special characters. \n";

    if ( sum > len_passwd) {
        printf( FORMAT,  
        len_passwd, 
        min_digit,
        min_lower, 
        min_upper,
        min_special );
                return EXIT_FAILURE;
    }

    int len_mix = len_passwd - sum;

    if(FLAG_DEBUG) {
        cout << "len pass: " << len_passwd << endl;
        cout << "min lower: " << min_lower << endl;
        cout << "min upper: " << min_upper << endl;
        cout << "min digit: " << min_digit << endl;
        cout << "min special: " << min_special << endl;
    cout << "len mix: " << len_mix << endl;
       cout << endl; // line feed
    }

    string passwd = genPasswd(min_lower, min_upper, min_digit, min_special )
    + genRandomStringMix(len_mix);

      random_device rd;
    mt19937 mt(rd());

  shuffle(passwd.begin(), passwd.end(), mt);

    cout << passwd << endl;

    return EXIT_SUCCESS;
}

