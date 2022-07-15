/**
 * poco_file.cpp
 * 2022-06-01 K.OHWADA
 */

// create directory file
// Poco/File
// https://docs.pocoproject.org/current/Poco.File.html

// reference: https://codezine.jp/article/detail/2205

#include <iostream>
#include <Poco/File.h>
#include <Poco/Exception.h>

int main(int argc, char* argv[])
{
    
   Poco::File dir( "temp" );
    dir.createDirectory();

    Poco::File tmp( "temp/test.txt" );
    tmp . createFile();

    typedef std::vector<Poco::File> fary;
    fary files;

    dir.list( files );

	for ( fary::iterator it = files.begin(); it != files.end(); ++it ) {
        std::cout << (*it).path() << std::endl;
	}

return 0;
}
