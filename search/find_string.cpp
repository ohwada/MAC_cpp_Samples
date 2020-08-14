/**
 * search sample
 * 2020-03-01 K.OHWADA
 */

		
// find the first substring equal to the given character sequence. 
// https://en.cppreference.com/w/cpp/string/basic_string/find

#include <iostream>
#include <string>

using namespace std;


/**
 *  main
 */
int main(void)
{
    const string sample("This is a string");
  
    cout << sample << endl;

   string line;

    while(1)
    {
        cout << endl;
        cout << "please enter string" << endl;
        cout << ">"; // prompt

        // input from keyboard
        getline(cin, line);

        if(line.empty()){
                break;
        }

        string::size_type pos = sample.find(line);

    if (pos == string::npos) {
        cout << "not found: " << line << endl;
    } else {
        string sub = sample.substr(pos, line.size());
        cout << "found: " << sub << " at " << pos << endl;
    }

}  // while

// 7
// 29

    return EXIT_SUCCESS;
}

