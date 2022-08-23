/**
 * sign.cpp
 * 2022-06-01 K.OHWADA
 */

// File signing  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter11/problem_94/main.cp

#include <iostream>
#include <string>
#include <assert.h>

#include "rsa.h"
#include "aes.h"
#include "hex.h"
#include "files.h"
#include "osrng.h"


/**
 * encode
 */
void encode(
  std::string const & filepath,
   CryptoPP::BufferedTransformation const & bt)
{
   CryptoPP::FileSink file(filepath.c_str());

   bt.CopyTo(file);
   file.MessageEnd();
}


/**
 * encode_private_key
 */
void encode_private_key(
  std::string const & filepath,
   CryptoPP::RSA::PrivateKey const & key)
{
   CryptoPP::ByteQueue queue;
   key.DEREncodePrivateKey(queue);

   encode(filepath, queue);
}


/**
 * encode_public_key
 */
void encode_public_key(
  std::string const & filepath,
   CryptoPP::RSA::PublicKey const & key)
{
   CryptoPP::ByteQueue queue;
   key.DEREncodePublicKey(queue);

   encode(filepath, queue);
}


/**
 * decode
 */
void decode(
  std::string const & filepath,
   CryptoPP::BufferedTransformation& bt)
{
   CryptoPP::FileSource file(filepath.c_str(), true);

   file.TransferTo(bt);
   bt.MessageEnd();
}


/**
 * decode_private_key
 */
void decode_private_key(
  std::string const & filepath,
   CryptoPP::RSA::PrivateKey& key)
{
   CryptoPP::ByteQueue queue;

   decode(filepath, queue);
   key.BERDecodePrivateKey(queue, false, queue.MaxRetrievable());
}


/**
 * decode_public_key
 */
void decode_public_key(
  std::string const & filepath,
   CryptoPP::RSA::PublicKey& key)
{
   CryptoPP::ByteQueue queue;

   decode(filepath, queue);
   key.BERDecodePublicKey(queue, false, queue.MaxRetrievable());
}


/**
 *  rsa_sign_file
 */
void rsa_sign_file(
  std::string const & filepath,
  std::string const & privateKeyPath,
  std::string const & signaturePath,
   CryptoPP::RandomNumberGenerator& rng)
{
   CryptoPP::RSA::PrivateKey privateKey;
   decode_private_key(privateKeyPath, privateKey);

   CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

   CryptoPP::FileSource fileSource(
      filepath.c_str(),
      true,
      new CryptoPP::SignerFilter(
         rng,
         signer,
         new CryptoPP::FileSink(
            signaturePath.c_str())));
}


/**
 * rsa_verify_file
 */
bool rsa_verify_file(
  std::string const & filepath,
  std::string const & publicKeyPath,
  std::string const & signaturePath)
{
   CryptoPP::RSA::PublicKey publicKey;
   decode_public_key(publicKeyPath.c_str(), publicKey);

   CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

   CryptoPP::FileSource signatureFile(
      signaturePath.c_str(),
      true);

   if (signatureFile.MaxRetrievable() != verifier.SignatureLength())
      return false;

   CryptoPP::SecByteBlock signature(verifier.SignatureLength());
   signatureFile.Get(signature, signature.size());

   auto* verifierFilter = new CryptoPP::SignatureVerificationFilter(verifier);
   verifierFilter->Put(signature, verifier.SignatureLength());

   CryptoPP::FileSource fileSource(
      filepath.c_str(),
      true,
      verifierFilter);

   return verifierFilter->GetLastResult();
}


/**
 * generate_keys
 */
void generate_keys(
  std::string const & privateKeyPath,
  std::string const & publicKeyPath,
   CryptoPP::RandomNumberGenerator& rng)
{
   try
   {
      CryptoPP::RSA::PrivateKey rsaPrivate;
      rsaPrivate.GenerateRandomWithKeySize(rng, 3072);

      CryptoPP::RSA::PublicKey rsaPublic(rsaPrivate);

      encode_private_key(privateKeyPath, rsaPrivate);
      encode_public_key(publicKeyPath, rsaPublic);
   }
   catch (CryptoPP::Exception const & e)
   {
      std::cerr << e.what() << std::endl;
   }
}

using namespace std;


/**
 * main
 */
int main()
{
    const string FILE("sample.txt");

    const string SIGN("sample.sign");

    const string PUBLIC("rsa-public.key");

     const string PRIVATE("rsa-private.key");

         CryptoPP::AutoSeededRandomPool rng;

   generate_keys(
      PRIVATE,
      PUBLIC,
      rng);

cout << "created: " << PRIVATE << endl;
cout << "created: " << PUBLIC << endl;

   rsa_sign_file(
       FILE,
      PRIVATE,
      SIGN,
      rng);

cout << "created: " <<  SIGN << endl;

   auto success = rsa_verify_file(
       FILE,
      PUBLIC,
      SIGN);

   assert(success);

    cout << "successful" << endl;

    return 0;
}

// created: rsa-private.key
// created: rsa-public.key
// created: sample.sign
// successful
