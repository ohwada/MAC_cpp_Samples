/**
 * menu sample
 * 2020-07-01 K.OHWADA
 */


// test for printMenu

#include <iostream>
#include "menu.hpp"

using namespace std;


/**
 * main
 */
int main(void)
{

    std::vector<std::string> list = 
    {string("foo"), string("bar"), string("fiz")};

    size_t size = list.size();
    int empty = -1;

while(1)
{
    cout << endl;
    int choice = printMenu( list, empty );
    cout << "choice: " << choice << endl;
    if(choice == empty){
        cout << "empty " << endl;
    } else if(choice == 0){
        bool ret1 = getEnterYn("quit?");
        if(ret1){
            cout << "goodby " << endl;
            break;
        }
    }

    bool ret2 = checkNumber( choice, 0, size);
    if(!ret2){
        cout << "out of range: " << choice << endl;
    }

    int index = choice - 1;
    if ((index >=0 )&&(index < size)) {
        auto item = list[index];
        cout << "item: " << item << endl;
    }

} // while

    bool ret3 = hitEnterKey();
    if(ret3){
        cout << "hitEnterKey" << endl;
    }

    return EXIT_SUCCESS;
}


// 0 quit 
// 1 foo
// 2 bar
//3 fiz
// [ 0 - 3] 

