/**
 * input sample
 * 2020-03-01 K.OHWADA
 */

// input string from std::cin
// https://en.cppreference.com/w/cpp/io/cin

#include <iostream>
#include <string>

using namespace std;


/**
 *  main
 */
int main(void)
{

    string line;

    cout << "quit when enter 'q' " << endl;

while(1)
{
    cout << "enter string" << endl;
    cout << ">"; // prompt

    cin >> line;

// TODO: 
// exit when return key
    if (line == "q"){
        break;
    }

    cout << "input: " << line << endl;

} // while

    return EXIT_SUCCESS;
}
