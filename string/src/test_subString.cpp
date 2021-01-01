/**
 * c++ sample
 * 2020-03-01 K.OHWADA
 */

// test for string_sub.hpp

#include <iostream>
#include "string_sub.hpp"

using namespace std;


/**
 *  main
 */
int main(void)
{

    string begin1 = "#b%";
    string end1 = "$e&";

    string sample1 = "abc" 
    +begin1
    + "123456789"
    + end1
    + "xyz" ;

    string begin2 = "#b?";
    string end2 = "$e!";

    string sample2 = begin2
    + "abcdefgh"
    + end2 ;

    cout << "sample1:"<< endl;
    cout << sample1 << endl;
    cout << "begin:"<< begin1 << endl;
    cout << "end:"<< end1 << endl;

    string substr1;
    string head1;
    string tail1;

    bool ret1 = subString(sample1, begin1, end1, substr1, head1, tail1 );
 
    if(ret1){
        cout << "success"<< endl;
    }

   cout << "substr: '"<< substr1 << "'" << endl;
    cout << "head: '"<< head1 << "'" << endl;
    cout << "tail: '"<< tail1 << "'" << endl;

    cout << endl;
   cout << "sample2:"<< endl;
    cout << sample2 << endl;
    cout << "begin:"<< begin2 << endl;
    cout << "end:"<< end2 << endl;

    string substr2;
    string head2;
    string tail2;

    bool ret2 = subString(sample2, begin2, end2, substr2, head2, tail2 );


    if(ret2){
        cout << "success"<< endl;
    }

   cout << "substr: '"<< substr2 << "'" << endl;
    cout << "head: '"<< head2 << "'" << endl;
    cout << "tail: '"<< tail2 << "'" << endl;

    string begin3 = "@b@";

    cout << endl;
   cout << "sample3: case fail"<< endl;
    cout << sample2 << endl;
    cout << "begin:"<< begin3 << endl;
    cout << "end:"<< end2 << endl;

    string substr3;
    string head3;
    string tail3;

    bool ret3 = subString(sample2, begin3, end2, substr3, head3, tail3 );

    if(!ret3){
        cout << "failed"<< endl;
    }


   cout << "substr: '"<< substr3 << "'" << endl;
    cout << "head: '"<< head3 << "'" << endl;
    cout << "tail: '"<< tail3 << "'" << endl;

    return 0;
}

// sample1:
// abc#b%123456789$e&xyz
// begin:#b%
// end:$e&
// substr: '123456789'
// head: 'abc'
// tail: 'xyz'
