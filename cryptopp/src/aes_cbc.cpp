/**
 * aes_cbc.cpp
 * 2022-06-01 K.OHWADA
 */

// how to operate AES in CBC mode using a pipeline. 
// the key is declared on the stack using a SecByteBlock to ensure the sensitive material is zeroized. 
// reference : https://cryptopp.com/wiki/Advanced_Encryption_Standard

#include <iostream>
#include <string>
#include <cassert>

#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"


using namespace CryptoPP;


/**
 * main
 */
int main(int argc, char* argv[])
{

    AutoSeededRandomPool prng;
    HexEncoder encoder(new FileSink(std::cout));

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    SecByteBlock iv(AES::BLOCKSIZE);

    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::string plain = "CBC Mode Test";
    std::string cipher, recovered;

    std::cout << "plain text: " << plain << std::endl;

 
    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource s(plain, true, 
            new StreamTransformationFilter(e,
                new StringSink(cipher)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "key: ";
    encoder.Put(key, key.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "iv: ";
    encoder.Put(iv, iv.size());
    encoder.MessageEnd();
    std::cout << std::endl;

    std::cout << "cipher text: ";
    encoder.Put((const byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();
    std::cout << std::endl;
    
    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        StringSource s(cipher, true, 
            new StreamTransformationFilter(d,
                new StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        std::cout << "recovered text: " << recovered << std::endl;
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    assert(recovered == plain);

    std::cout << "successful" << std::endl;

    return 0;
}

// plain text: CBC Mode Test
// key: 8DE53D0A5683D5AE5C9637A79A7909FC
// iv: ACA64D0060F08036663B55D18331523D
// cipher text: 75C1F903E8D35F6573E392681F743C4E
// recovered text: CBC Mode Test