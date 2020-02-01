/**
 * C++ Sample
 * 2020-01-01 K.OHWADA
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

 
/**
 * main
 */
int main(int argc, char** argv)
{ 

    string LF = "\n";

    if(argc < 3) {
        cout << "Usage:  " << argv[0] <<   " <Input filename> <Output filename>"  << endl;
        return 1;
    }

    // specify filename from commandline 
    string input = argv[1];
    string output = argv[2];

    ifstream fin;
    ofstream fout; 

    // open input file
    fin.open(input, ios::in); 
    if (fin.fail()){ 
        cerr << "open input file failed: " << input << endl;
        return 1;
    }                         

    // read text  by one line
    vector<string> lines;
    string line;
    while( getline(fin, line) ){
        lines.push_back(line);
    }

    // show text
    cout <<  input << endl  << endl;
    std::string data;
    for(auto itr = lines.begin(); itr != lines.end(); ++itr) {
        std::string str = *itr;
        data += str + LF;
        std::cout << str << std::endl;
    }

    // open input file
    fout.open(output, ios::out); 
    if (fout.fail()){ 
        cerr << "open output file failed: " << output << endl;
        return 1;
    } 

    // write to output file
    fout<< data;
    fout.close();

    cout << "write to: " << output << endl;

    return 0;
}
