/**
 * enc_dec.cpp
 * 2022-06-01 K.OHWADA
 */

// Encrypting and decrypting files 
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter11/problem_93/main.cpp


#include <iostream>
#include <string>

#include "sha.h"
#include "hex.h"
#include "files.h"
#include "default.h"

#include "file_util.hpp"


/**
 * encrypt_file
 */
void encrypt_file(
   std::string const & sourcefile,
   std::string const & destfile,
   std::string password)
{
   CryptoPP::FileSource source(
      sourcefile.c_str(),
      true,
      new CryptoPP::DefaultEncryptorWithMAC(
      (CryptoPP::byte*)password.data(), password.size(),
         new CryptoPP::FileSink(
            destfile.c_str())
      )
   );
}


/**
 *  decrypt_file
 */
void decrypt_file(
   std::string const & sourcefile,
   std::string const & destfile,
   std::string password)
{
   CryptoPP::FileSource source(
      sourcefile.c_str(),
      true,
      new CryptoPP::DefaultDecryptorWithMAC(
      (CryptoPP::byte*)password.data(), password.size(),
         new CryptoPP::FileSink(
            destfile.c_str())
      )
   );
}

using namespace std;


/**
 * main
 */
int main()
{
const string SRC("sample.txt"); 
const string ENC("sample.txt.enc");
const string DEC("sample.txt.dec");
const string PASSWD("abcd1234");

   encrypt_file(SRC, ENC,  PASSWD);

cout << "created: "<< ENC << endl;

   decrypt_file(ENC, DEC,  PASSWD);

cout << "created: "<< DEC << endl;


    bool ret = cmpFiles(SRC, DEC);
    if(ret){
        cout << "successful" << endl;
    } else {
      cout << "unmatch" << endl;
    }

    return 0;
}


// created: sample.txt.enc
// created: sample.txt.dec
// successful
