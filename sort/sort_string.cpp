/**
 * sort sample
 * 2020-03-01 K.OHWADA
 */

// sort char in string
// reference ; https://note.com/kazusasan/n/n55e2a11bc64a

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 *  main
 */
int main (int argc, char *argv[])

{
   string line;

    cout << endl;
     cout << "please enter the random alphabets" << endl;
    cout << ">"; // prompt

        // input from keyboard
   cin >> line;

    string line2 = line;

  cout << "\n sort small to large" << endl;

   sort(line.begin(), line.end());

   cout << line << endl;
   
  cout << "\n sort large to small" << endl;

    sort(line2.begin(), line2.end(), greater<char>() );

   cout << line2 << endl;

   return 0;
}
