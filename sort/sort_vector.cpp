/**
 * c++ sample
 * 2020-03-01 K.OHWADA
 */

// sort int vector using std::sort
// reference ; https://kaworu.jpn.org/cpp/std::sort

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
 

/**
 *  dump
 */
void dump(vector<int> vec)
{

    for(auto x: vec){
            cout << x << endl;
    }
}
 

/**
 *  main
 */
int main (int argc, char *argv[])
{
        vector<int> vec;
 
        vec.push_back ( 3 );
        vec.push_back ( 4 );
        vec.push_back ( 5 );
        vec.push_back ( 1 );
        vec.push_back ( 2 );
 
        vector<int> vec2 = vec;

        cout << "before sort" << std::endl;
        dump (vec);
 
  cout << "\n sort small to large" << endl;

        std::sort(vec.begin(), vec.end() );
 
        dump (vec);

        cout << "\n sort large to small" << endl;

        std::sort(vec2.begin(), vec2.end(), std::greater<int>() );
  
        dump (vec2);

        return 0;
}