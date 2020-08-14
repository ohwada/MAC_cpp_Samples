/**
 * input sample
 * 2020-03-01 K.OHWADA
 */

//  reads characters from standard input using getline()
// https://en.cppreference.com/w/cpp/string/basic_string/getline

#include <iostream>
#include <string>

using namespace std;


/**
 *  main
 */
int main(void)
{

    string line;

    cout << "quit when enter 'return' only " << endl;

while(1)
{

    cout << "enter string" << endl;
    cout << ">"; // prompt

    getline(cin, line);

    if(line.empty()){
        break;
    }

    cout << "input: " << line << endl;

} // while

    return EXIT_SUCCESS;
}
