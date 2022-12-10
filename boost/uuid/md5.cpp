/**
 * md5.cpp
 * 2022-06-01 K.OHWADA
 */


// reference : https://stackoverflow.com/questions/55070320/how-to-calculate-md5-of-a-file-using-boost

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;


/**
 * gen_md5
 */
void gen_md5(std::string str, md5::digest_type &digest)
{
        md5 hash;
        hash.process_bytes(str.data(), str.size());
        hash.get_digest(digest);
}


/**
 * toString
 */
std::string toString(const md5::digest_type &digest)
{
    const auto intDigest = reinterpret_cast<const int*>(&digest);
    std::string result;
    boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type)/sizeof(int)), std::back_inserter(result));
    return result;
}

 using namespace std;


/**
 * main
 */
int main ()
{
    string str("foobar");

    string expect("3858F62230AC3C915F300C664312C63F");

    md5::digest_type digest;

    gen_md5(str, digest);

    auto str_md5 = toString(digest);

    cout << "md5(" << str << ") = " << str_md5 << endl;
    
    assert(str_md5 == expect);

    cout << "successful" << endl;

    return 0;
}
