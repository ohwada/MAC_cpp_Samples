 /**
 * test_cmpFiles.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ test_cmpFiles.cpp 

#include <iostream>
#include "file_util.hpp"

using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

    string file1("data/sample1.txt");
    string file2("data/sample2.txt");
    string file3("data/sample3.txt");

	if( argc == 3 ) {
	    file1 = argv[1];
	    file2 = argv[2];
    } else {
		    cout << "Usage "<< argv[0 ] << " <file1> <file2> " 
			<< endl;
	}

    cout << file1 << endl;
    cout << file2 << endl;

bool ret1 = cmpFiles(file1, file2);

  cout << boolalpha << ret1 << endl;

bool ret2 = cmpFiles(file1, file3);

  cout << boolalpha << ret2 << endl;

    return 0;
}


