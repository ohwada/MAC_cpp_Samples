/**
 * input sample
 * 2020-03-01 K.OHWADA
 */

//  reads int number characters from standard input using getline()
// https://en.cppreference.com/w/cpp/string/basic_string/getline

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;


/**
 *  main
 */
int main(void)
{

    string line;
    int num;

    cout << "quit when enter 'return' only " << endl;

while(1)
{
    cout << "enter number" << endl;
    cout << ">"; // prompt

    getline(cin, line);

    if(line.empty()){
        break;
    }

    int ret = sscanf(line.c_str(), "%d", &num);
    if(ret != 1){
        cout << "invalid" << endl;
        continue;
    }

    cout << "input: " << line << endl;

} // while

    return EXIT_SUCCESS;
}
