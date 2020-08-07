/**
 * C++ sample
 * 2020-03-01 K.OHWADA
 */

// test for random_number.hpp
// generate random int vector  
 
#include<iostream>
#include "random_number.hpp"


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{

    const int  NUM = 10;

    int  min = 0;
    int  range = 999;

    if(argc == 3){
            min = atoi(argv[1]);
            range = atoi(argv[2]);
    } else {
            cout <<  "Usage: " << argv[0] << " [min] [range]" << endl;
    }

    vector<int> vec = gen_random_vector(NUM,  min, range);

    cout << "random: " << min << " -> " << range << endl;

    for(int i=0; i<vec.size(); i++)
    {
        cout << vec[i] << endl;
    }

    return EXIT_SUCCESS;
}

