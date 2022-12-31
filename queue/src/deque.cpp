/**
 * deque.cpp
 * 2022-06-01 K.OHWADA
 */

// https://en.cppreference.com/w/cpp/container/deque

#include <iostream>
#include <deque>
 

using  namespace std;


/**
 * main
 */
int main()
{
    // Create a deque containing integers
    std::deque<int> d = {7, 5, 16, 8};
 
    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);
 
    // Iterate and print values of deque
    for(int n : d){
        cout << n << ' ';
    }
    cout << endl;

    return 0;
}

