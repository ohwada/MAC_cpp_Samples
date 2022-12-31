/**
 *  enable_shared_from_this.cpp

 * 2022-06-01 K.OHWADA
 */

// https://www.boost.org/doc/libs/1_79_0/libs/smart_ptr/doc/html/smart_ptr.html#enable_shared_from_this

#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <cassert>


/**
 *  class Y
 */
class Y: public boost::enable_shared_from_this<Y>
{
public:
    boost::shared_ptr<Y> f()
    {
        return shared_from_this();
    }
};

using  namespace std;


/**
 *  main
 */
int main()
{
    boost::shared_ptr<Y> p(new Y);
    boost::shared_ptr<Y> q = p->f();

    assert(p == q);
    assert(!(p < q || q < p)); // p and q must share ownership

    cout << "successful" << endl;

    return 0;
}
