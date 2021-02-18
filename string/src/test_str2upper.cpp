/**
 * c++ string sample
 * 2020-03-01 K.OHWADA
 */

// test for string_upper.hpp


#include<iostream>
#include<string>

#include "string_upper.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

    int mode = 1; // upper

    if(argc == 2){
            mode = atoi(argv[1]);
    } else {
            cout <<  "Usage: " << argv[0] << " [mode]" << endl;
    }


    string msg;
    if(mode == 1){
        msg =  (char *)"please enter the lowercase alphabets";
    } else if(mode == 2){
        msg =  (char *)"please enter the Uppercase alphabets";
    }else{

        cout << "mode must be 1 or 2 : mode = %d  " << endl;
        return EXIT_FAILURE;
    }


    string line;
    string str;

    while(1)
    {

        cout << msg << endl;

        cout << ">"; // prompt

        // input from keyboard
        getline(cin, line);

        // qiut when only return key
        if(line.empty()){
            break;
        }

        string str;
        if(mode == 1){
            str2upper(line, str);
        } else if(mode == 2){
            str2lower(line, str);
        }

        cout << str << endl;

    } // while

    cout << "quit"<< endl;

    return EXIT_SUCCESS;
}

