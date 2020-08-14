/**
 * input sample
 * 2020-03-01 K.OHWADA
 */


// input int number from std::cin
// reference : https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
// https://en.cppreference.com/w/cpp/io/basic_istream/ignore

#include <iostream>

using namespace std;

int main(void)
{

    int num;

    cout << "quit when enter '0' " << endl;

while(1)
{

    cout << "Please enter number" << endl;
    cout << ">"; // prompt

    cin >> num;

    if(cin.good()==0){
        cout << "invalid char \n" << endl;
        cin.clear();
         cin.ignore(); 
        continue;
    }

// TODO: 
// exit when return key
    if (num == 0){
        break;
    }

    cout << "input: " << num << endl;

} // while

    return EXIT_SUCCESS;
}
