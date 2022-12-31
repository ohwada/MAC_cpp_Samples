/**
 *  shared_ptr.cpp
 * 2022-06-01 K.OHWADA
 */

// https://www.boost.org/doc/libs/1_81_0/libs/smart_ptr/doc/html/smart_ptr.html#shared_ptr

#include <boost/shared_ptr.hpp>
#include <iostream>

using  namespace std;


/**
 *  main
 */
int main()
{
    boost::shared_ptr<int> p1( new int(5) );

    cout << *p1 << endl;

   boost::shared_ptr<int> p2 = p1;

    cout << *p2 << endl;

    return 0;
}

// 5
// 5
