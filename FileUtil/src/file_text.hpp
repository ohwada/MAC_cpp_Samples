/**
 * C++ Sample
 * 2020-03-01 K.OHWADA
 */

// read write text file

#include <fstream>
#include <string>
#include <vector> 

// prototype
bool readTextFile( std::string file, std::string &text );
bool readTextFile2Lines( std::string file, std::vector<std::string> &lines );
bool writeTextFile(std::string file, std::string data );


/**
 * readTextFile
 */
bool readTextFile( std::string file, std::string &text )
{
    const std::string LF = "\n";

    std::vector<std::string> lines;
    bool ret = readTextFile2Lines( file, lines );
    if(!ret) {
        return false;
    }

    std::string data;
    for( auto itr = lines.begin(); itr != lines.end();  ++itr ) {
        data +=  std::string( *itr ) + LF;
    }

    text = data;
    return true;
}


/**
 * readTextFile2Lines
 */
bool readTextFile2Lines( std::string file, std::vector<std::string> &lines )
{
    std::ifstream fin;

    // open input file
    fin.open(file, std::ios::in); 
    if (fin.fail()){ 
        return false;
    }                         

    // read text  by one line
    std::string line;
    while( getline(fin, line) ) {
        lines.push_back(line);
    }

    return true;
}


/**
 * writeTextFile
 */
bool writeTextFile(std::string file, std::string data )
{
    std::ofstream fout; 

    // open input file
    fout.open(file, std::ios::out); 
    if (fout.fail()){ 
        return false;
    } 

    // write to output file
    fout<< data;
    fout.close();

    return true;
}

