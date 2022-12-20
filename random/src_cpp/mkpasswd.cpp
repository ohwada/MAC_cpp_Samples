/**
 * mkpasswd.cpp
 * 2022-06-01 K.OHWADA
 */


// generate password with random_string.hpp
// like LINUX mkpasswd
// https://docs.oracle.com/cd/E36784_01/html/E36870/mkpasswd-1.html
// source: https://raw.githubusercontent.com/aeruder/expect/master/example/mkpasswd

// command line paser using tclap
// https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getopt.3.html

// Difference from Linux mkpasswd
//
// on Linux mkpasswd
// if You specify the command option as shown below
// You get a warning
// % mkpasswd -d 10
// impossible to generate 9-character password with 10 // numbers, 2 lowercase letters, 2 uppercase letters and 1 special characters.
//
// in this program
// adjust password length
// and generate long passwords


#include<iostream>
#include <random>
#include <tclap/CmdLine.h>
#include "passwd.hpp"
 

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

// mkpasswd command options
// https://docs.oracle.com/cd/E36784_01/html/E36870/mkpasswd-1.html
// l : passwd length default: 9
// d : digit default : 2
// c : lower: default 2
// C : upper default : 2
// s : speclal default: 1

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

    int min_mix =  len_passwd - min_lower - min_upper - min_digit -  min_special;
	if(min_mix < 0){
		min_mix = 0;
	}

    if(FLAG_DEBUG) {
		cout << "l : " << len_passwd << endl;
		cout << "d: " << min_digit << endl;
		cout << "c:" << min_lower<< endl;
		cout << "C: " << min_upper << endl;
		cout << "s: " << min_special << endl;
	}

    string passwd = genPasswd(min_lower, min_upper, min_digit, min_special, min_mix);

   if(FLAG_DEBUG) {
    	cout << passwd << endl;
	}

	string text = shuffle(passwd);

	cout << text << endl;

	return EXIT_SUCCESS;
}

