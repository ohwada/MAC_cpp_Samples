/**
 * aes_length.cpp
 * 2022-06-01 K.OHWADA
 */

// dumps the minimum, maximum, and default key lengths used by AES.
// referenxce :https://cryptopp.com/wiki/Advanced_Encryption_Standard

#include <iostream>
#include "aes.h"

using namespace std;

/**
 * main
 */
int main()
{
cout << "key length: " << CryptoPP::AES::DEFAULT_KEYLENGTH << endl;
cout << "key length (min): " << CryptoPP::AES::MIN_KEYLENGTH << endl;
cout << "key length (max): " << CryptoPP::AES::MAX_KEYLENGTH << endl;
cout << "block size: " << CryptoPP::AES::BLOCKSIZE << endl;

    return 0;
}

// key length: 16
// key length (min): 16
// key length (max): 32
// block size: 16
