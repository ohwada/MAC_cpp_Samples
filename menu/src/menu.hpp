#pragma once
/**
 * menu sample
 * 2020-07-01 K.OHWADA
 */

// menu function



#include <iostream>
#include <string>
#include <vector>



// prototype
int printMenu( std::vector<std::string> list,  int empty, bool is_top = true );
bool getEnterYn(std::string msg);
bool hitEnterKey(void);
bool checkNumber(int num, int min, int max);


/**
 *   printMenu
 */
int printMenu( std::vector<std::string> list, int empty, bool is_top )
{

    int size = list.size();

    if(is_top){
        std::cout << std::endl;
    }

    std::cout << "0 quit "  <<  std::endl;
    for(int i=0; i<size; i++)
    {
        std::cout << (i+1) << " " << list[i] << std::endl;
    } // for

    std::cout << " [ 0 - " <<  size << "] ";

    std::string line;
    int choice =0;
    std::getline(std::cin, line);
    if( line.empty() ){
        choice = empty;
    } else {
        choice = std::stoi(line);
    }
    return choice;
}


/**
 *  getEnterYn
 */
bool getEnterYn(std::string msg)
{
	std::cout << msg << " [Y/n] ";
	std::cout.flush();

	std::string answer;
	getline(std::cin, answer);

	if ( answer.empty() || (answer[0] == 'Y' ) || ( answer[0] == 'y') ) {
			return true;
	}

	return false;
}


/**
 *  hitEnterKey
 */
bool hitEnterKey(void)
{

	std::cout << std::endl;
	std::cout << "Please hit Enter key " << std::endl;
	std::cout << std::endl;

	std::string line;
	getline(std::cin, line);

	if( line.empty() ) {
		return true;
	}

	return false;
}


/**
 *  checkNumber
 */
bool checkNumber(int num, int min, int max)
{
	if ((num >= min) && (num <=  max)) {
		return true;
	}

	return false;
}

