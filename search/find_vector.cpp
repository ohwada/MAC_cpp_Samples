/**
 * search sample
 * 2020-03-01 K.OHWADA
 */

// find first matched element in int vector 
// reference : https://en.cppreference.com/w/cpp/algorithm/find

// g++ find_vector.cpp -std=c++11

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


/**
 *  dump
 */
void dump(vector<int> vec)
{

    for(auto v: vec){
            cout << v << ", ";
    }   
    cout << endl;

}


/**
 *  main
 */
int main(void) 
{

  vector<int> vec = { 5, 3, 1, 4, 2 };

    dump(vec);

   string line;

    while(1)
    {
        cout << endl;
        cout << "please enter number" << endl;
        cout << ">"; // prompt

        // input from keyboard
        getline(cin, line);

        if(line.empty()){
                break;
        }
    
        int num = atoi( line.c_str() );

        auto result = find(vec.begin(), vec.end(), num);

        if (result == vec.end()) {
                cout << "not found: " << num << endl;
        } else {
                int val = *result;
                int pos = std::distance( vec.begin(), result );
                cout << "found: " << val << " at " << pos << endl;
        }

    } // while


    return 0;
}

