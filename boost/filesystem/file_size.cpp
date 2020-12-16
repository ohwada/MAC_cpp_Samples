/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// file_size
// reporting the size of a file

// https://www.boost.org/doc/libs/1_74_0/libs/filesystem/doc/tutorial.html

//  filesystem tut1.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>


 using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    string file("file_size.cpp");

  if (argc == 2) {
    file = argv[1];
} else {
    cout << "Usage: " <<  argv[0] << " [filepath] " << endl;
  }

    int size = boost::filesystem::file_size(file);

    cout << file << " : " << size << endl;

        return EXIT_SUCCESS;
}


// file_size.cpp : 890

