/**
 * file.cpp
 * 2022-06-01 K.OHWADA
 */

// Computing file hashes with SHA1, SHA256, and MD5  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter11/problem_92/main.cp

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "sha.h"
#include "md5.h"
#include "hex.h"
#include "files.h"


/**
 * compute_hash
 */
template <class Hash>
std::string compute_hash(std::string const & filepath)
{
   std::ifstream file(filepath, std::ios::binary);
   if (file.is_open())
   {
      Hash hash;
      CryptoPP::byte digest[Hash::DIGESTSIZE] = { 0 };

      do
      {
         char buffer[4096] = { 0 };
         file.read(buffer, 4096);

         auto extracted = static_cast<size_t>(file.gcount());

         if (extracted > 0)
         {
            hash.Update(
               reinterpret_cast<CryptoPP::byte*>(buffer),
               extracted);
         }
      } while (!file.fail());

      hash.Final(digest);

      CryptoPP::HexEncoder encoder;
      std::string result;

      encoder.Attach(new CryptoPP::StringSink(result));
      encoder.Put(digest, sizeof(digest));
      encoder.MessageEnd();

      return result;
   }

   throw std::runtime_error("Cannot open file!");
}


/**
 * compute_hash_ex
 */
template <class Hash>
std::string compute_hash_ex(std::string const & filepath)
{
   std::string digest;
   Hash hash;

   CryptoPP::FileSource source(
      filepath.c_str(),
      true,
      new CryptoPP::HashFilter(hash,
         new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(digest))));

   return digest;
}

using namespace std;


/**
 * main
 */
int main()
{
   string path;
   cout << "Path: ";
   cin >> path;

   try
   {
      cout << "SHA1: "
         << compute_hash<CryptoPP::SHA1>(path) << endl;

      cout << "SHA256: "
         << compute_hash<CryptoPP::SHA256>(path) << endl;

      cout << "MD5: "
         << compute_hash<CryptoPP::Weak::MD5>(path) << endl;

      cout << "SHA1: "
         << compute_hash_ex<CryptoPP::SHA1>(path) << endl;

      cout << "SHA256: "
         << compute_hash_ex<CryptoPP::SHA256>(path) << endl;

      cout << "MD5: "
         << compute_hash_ex<CryptoPP::Weak::MD5>(path) << endl;
   }
   catch (std::exception const & ex)
   {
      cerr << ex.what() << endl;
   }

    return 0;
}

// Path: file.cpp
// SHA1: 5E04D2818A186475607971AE92DA57D8EE88244F
// SHA256: 59E8A9C9502AC98F83FC6D545F4618CFBC0B4F5256014BEA2FB9F12B280269F4

