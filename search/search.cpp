/**
 * search sample
 * 2020-03-01 K.OHWADA
 */

// searches for the first occurrence of the sequence of elements 
// reference : https://en.cppreference.com/w/cpp/algorithm/search


#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>

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
 *  list2str
 */
string list2str(list<int> ls)
{

    string str;
    for( auto v: ls ){
            str +=  to_string(v) + ", ";
    }   
    
    return str;
}


/**
 *  main
 */
int main(void) 
{

  vector<int> vec = { 1, 2, 3, 1, 2, 3 };
    list<int> ls;

    dump(vec);

   string line;
    int num1;
    int num2;

while(1)
{

        cout << endl;
        cout << "Please enter teo numbers separated by a space" << endl;
        cout << ">"; // prompt

        // input from keyboard
        getline(cin, line);

        if(line.empty()){
                break;
        }

        int ret = sscanf(line.c_str(), "%d %d", &num1, &num2);
        if(ret != 2){
            cout << "invalid" << endl;
            continue;
        }

        ls.clear();
        ls.push_back(num1); 
        ls.push_back(num2); 

    vector<int>::iterator it = search(vec.begin(), vec.end(), ls.begin(), ls.end());

    if (it == vec.end()) {
            string in = list2str(ls);
            cout << "not found: ( " << in << " )" <<endl;
    } else {
            int pos = distance(vec.begin(), it) ;
            int val1 = vec[pos];
            int val2 = vec[pos+1];
            cout << "found: ( " << val1 << ", " << val2 << " ) at " << pos << endl;
    }

} // while

// 1, 2, 3, 1, 2, 3, 
// please enter first number
// >

    return 0;
}