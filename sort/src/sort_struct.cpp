/**
 * sort_struct.cpp
 * 2020-03-01 K.OHWADA
 */

// sort struct with two member variables
// reference : https://minus9d.hatenablog.com/entry/20130501/1367415668

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


/**
 *  struct Hoge
 */
struct Hoge {
    int num;
    string str;

     // constractor
        Hoge()
            : num(0)
            , str()
         {
            // nop
         }

    // constractor
        Hoge
        (
            int num_ ,
            string str_
        )
            : num(num_)
            , str(str_)
        {
            // nop
        }


/**
 *  operator "<"
 */

// Note:
// dont forget the last const, 
// compile error as below
//invalid operands to binary expression ('const Hoge' and //'const Hoge')
//bool operator()(const _T1& __x, const _T1& __y) const {return __x < __y;}

// sort small to large
// compare with num,
// if they are the same, 
// compare with str
    bool operator<( const Hoge& h )  const {
        return ( num == h.num ? str < h.str : num < h.num );
    }
};


/**
 *  hoge2str
 */
string hoge2str(Hoge h)
{
    string ret = "[  num: " + to_string(h.num)
        + " ; str: " + h.str + " ]";
    return ret;
}


/**
 *  dump
 */
void dump( vector<Hoge> vec)
{
    for(auto x: vec)
    {
        cout << hoge2str(x) << endl;
    }
}


/**
 *  main
 */
int main (int argc, char *argv[])
{

    vector<Hoge> vec;

    vec.push_back ( Hoge( 30, "ccc" ) );
    vec.push_back ( Hoge( 20, "ddd" ) );
    vec.push_back ( Hoge( 10, "eee" ) );
    vec.push_back ( Hoge( 30, "bbb" ) );
    vec.push_back ( Hoge( 30, "aaa" ) );

    cout << "before sort" << std::endl;
    dump (vec);

    sort(vec.begin(), vec.end());

    cout << "\n after sort" << std::endl;
    dump (vec);

// before sort
// [  num: 30 ; str: ccc ]
// [  num: 20 ; str: ddd ]
// [  num: 10 ; str: eee ]
// [  num: 30 ; str: bbb ]
// [  num: 30 ; str: aaa ]
//
// after sort
// [  num: 10 ; str: eee ]
// [  num: 20 ; str: ddd ]
// [  num: 30 ; str: aaa ]
// [  num: 30 ; str: bbb ]
// [  num: 30 ; str: ccc ]

    return 0;
}

