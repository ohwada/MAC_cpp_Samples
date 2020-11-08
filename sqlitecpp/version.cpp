/**
 * sqlitecpp sample
 * 2020-07-01 K.OHWADA
 */


// display version
// g++ version.cpp -std=c++11  `pkg-config --cflags --libs sqlitecpp` 


#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <sqlite3.h>

using namespace std;


/**
 * main
 */
int main(void)
{

    cout << "SQLITECPP_VERSION: " << SQLITECPP_VERSION << endl;

    cout << "sqlite3_libversion: " << sqlite3_libversion() << endl;

    return EXIT_SUCCESS;
}


// SQLITECPP_VERSION: 3.01.01
// sqlite3_libversion: 3.33.0


