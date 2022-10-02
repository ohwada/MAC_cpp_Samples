/**
 * file_write.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <fstream>

using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{
    string file("out.txt");

    if(argc == 2) {
      	file = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file] " << endl;
    }

    cout << file << endl;

    std::ofstream fout(file); 

    string text("this is sample");

    fout << text;

    fout.close();

    return 0;
}
