/**
 * sha1.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://nukesaq88.hatenablog.com/entry/2013/04/19/183424
// https://www.boost.org/doc/libs/1_67_0/boost/uuid/detail/sha1.hpp

#include <iostream>
#include <sstream>
#include <cassert>
#include <boost/uuid/detail/sha1.hpp>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>


typedef boost::array<boost::uint8_t,20> hash_data_t;


/**
 * get_sha1_hash
 */
hash_data_t
get_sha1_hash( const void *data, const std::size_t byte_count )
{
  boost::uuids::detail::sha1 sha1;
  sha1.process_bytes( data, byte_count );
  unsigned int digest[5];
  sha1.get_digest( digest );
  const boost::uint8_t *p_digest = reinterpret_cast<const boost::uint8_t *>( digest );
  hash_data_t hash_data;
  for( int i = 0; i < 5; ++i )
  {
    hash_data[ i * 4 ]     = p_digest[ i * 4 + 3 ];
    hash_data[ i * 4 + 1 ] = p_digest[ i * 4 + 2 ];
    hash_data[ i * 4 + 2 ] = p_digest[ i * 4 + 1 ];
    hash_data[ i * 4 + 3 ] = p_digest[ i * 4 ];
  }
  return hash_data;
}


/**
 * hash_to_string
 */
std::string hash_to_string( hash_data_t hash)
{
    std::stringstream ss;
    ss << std::hex;

    hash_data_t::const_iterator itr = hash.begin();
    const hash_data_t::const_iterator end_itr = hash.end();
    for( ; itr != end_itr; ++itr )
    {
        ss << ( (*itr  & 0xf0 ) >> 4 )
              << (*itr  & 0x0f );
    } // for
  
    return ss.str();
}


 using namespace std;


/**
 * main
 */
int main()
{

    string text("foobar");

    string expect("8843d7f92416211de9ebb963ff4ce28125932878");

    hash_data_t hash = get_sha1_hash( text.c_str(), text.length() );

    string str_hash = hash_to_string(hash);

    cout << str_hash << endl;

    assert(str_hash == expect );

    cout << "successful" << endl;

  return 0;
}

