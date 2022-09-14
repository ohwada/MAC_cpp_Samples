/*
 *  toupper.cpp
 * 2022-06-01 K.OHWADA 
*/

#include <iostream>
#include <cctype>
#include "split.hpp"

using namespace std;


/*
 * main
*/
int main()
{

    string text("hello world goodby japan");
    char delim = ' '; 

    cout << text << endl;

    auto data = split(text, delim);

    for(auto str: data){
	    string word = str;
	    word[0] = toupper(word[0]);
	    cout << " " << word;
    } 
    cout << endl;

	return 0;
}

// Hello World Goodby Japan

