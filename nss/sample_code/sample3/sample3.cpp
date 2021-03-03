//  g++ sample3.cpp `pkg-config --cflags --libs nss` 

// https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_sample3

/*
 * Demonstration program for hashing and MACs
 */

#include <iostream>
#include "pk11pub.h"
#include "nss.h"

static void
printDigest(unsigned char *digest, unsigned int len)
{
  int i;

  std::cout << "length: " << len << std::endl;
  for(i = 0;i < len;i++) printf("%02x ", digest[i]);
  std::cout << std::endl;
}

/*
 * main
 */
int
main(int argc, const char *argv[])
{
  int status = 0;
  PK11SlotInfo *slot = 0;
  PK11SymKey *key = 0;
  PK11Context *context = 0;
  unsigned char data[80];
  unsigned char digest[20]; /*Is there a way to tell how large the output is?*/
  unsigned int len;
  SECStatus s;

  /* Initialize NSS
   * If your application code has already initialized NSS, you can skip it
   * here.
   * This code uses the simplest of the Init functions, which does not
   * require a NSS database to exist
   */
  NSS_NoDB_Init(".");

  /* Get a slot to use for the crypto operations */
  slot = PK11_GetInternalKeySlot();
  if (!slot)
  {
    std::cout << "GetInternalKeySlot failed" << std::endl;
    status = 1;
    goto done;
  }

  /*
   *  Part 1 - Simple hashing
   */
  std::cout << "Part 1 -- Simple hashing" << std::endl;

  /* Initialize data */
  memset(data, 0xbc, sizeof data);

  /* Create a context for hashing (digesting) */
  context = PK11_CreateDigestContext(SEC_OID_MD5);
  if (!context) { std::cout << "CreateDigestContext failed" << std::endl; goto done; }

  s = PK11_DigestBegin(context);
  if (s != SECSuccess) { std::cout << "DigestBegin failed" << std::endl; goto done; }

  s = PK11_DigestOp(context, data, sizeof data);
  if (s != SECSuccess) { std::cout << "DigestUpdate failed" << std::endl; goto done; }

  s = PK11_DigestFinal(context, digest, &len, sizeof digest);
  if (s != SECSuccess) { std::cout << "DigestFinal failed" << std::endl; goto done; }

  /* Print digest */
  printDigest(digest, len);

  PK11_DestroyContext(context, PR_TRUE);
  context = 0;

  /*
   *  Part 2 - Hashing with included secret key
   */
  std::cout << "Part 2 -- Hashing with included secret key" << std::endl;

  /* Initialize data */
  memset(data, 0xbc, sizeof data);

  /* Create a Key */
  key = PK11_KeyGen(slot, CKM_GENERIC_SECRET_KEY_GEN, 0, 128, 0);
  if (!key) { std::cout << "Create key failed" << std::endl; goto done; }

  std::cout << (void *)key << std::endl;

  /* Create parameters for crypto context */
  /* NOTE: params must be provided, but may be empty */
  SECItem noParams;
  noParams.type = siBuffer;
  noParams.data = 0;
  noParams.len = 0;

  /* Create context using the same slot as the key */
//  context = PK11_CreateDigestContext(SEC_OID_MD5);
  context = PK11_CreateContextBySymKey(CKM_MD5, CKA_DIGEST, key, &noParams);
  if (!context) { std::cout << "CreateDigestContext failed" << std::endl; goto done; }

  s = PK11_DigestBegin(context);
  if (s != SECSuccess) { std::cout << "DigestBegin failed" << std::endl; goto done; }

  s = PK11_DigestKey(context, key);
  if (s != SECSuccess) { std::cout << "DigestKey failed" << std::endl; goto done; }

  s = PK11_DigestOp(context, data, sizeof data);
  if (s != SECSuccess) { std::cout << "DigestUpdate failed" << std::endl; goto done; }

  s = PK11_DigestFinal(context, digest, &len, sizeof digest);
  if (s != SECSuccess) { std::cout << "DigestFinal failed" << std::endl; goto done; }

  /* Print digest */
  printDigest(digest, len);

  PK11_DestroyContext(context, PR_TRUE);
  context = 0;

  /*
   *  Part 3 - MAC (with secret key)
   */
  std::cout << "Part 3 -- MAC (with secret key)" << std::endl;

  /* Initialize data */
  memset(data, 0xbc, sizeof data);

  context = PK11_CreateContextBySymKey(CKM_MD5_HMAC, CKA_SIGN, key, &noParams);
  if (!context) { std::cout << "CreateContextBySymKey failed" << std::endl; goto done; }

  s = PK11_DigestBegin(context);
  if (s != SECSuccess) { std::cout << "DigestBegin failed" << std::endl; goto done; }

  s = PK11_DigestOp(context, data, sizeof data);
  if (s != SECSuccess) { std::cout << "DigestOp failed" << std::endl; goto done; }

  s = PK11_DigestFinal(context, digest, &len, sizeof digest);
  if (s != SECSuccess) { std::cout << "DigestFinal failed" << std::endl; goto done; }

  /* Print digest */
  printDigest(digest, len);

  PK11_DestroyContext(context, PR_TRUE);
  context = 0;

done:
  if (context) PK11_DestroyContext(context, PR_TRUE);  /* freeit ?? */
  if (key) PK11_FreeSymKey(key);
  if (slot) PK11_FreeSlot(slot);

  return status;
}


// Part 1 -- Simple hashing
// length: 16
// 74 63 9a 51 ba 5c 5a c8 37 a6 30 11 a5 1d cb d5 
// Part 2 -- Hashing with included secret key
0x7f95f1c132a0
// length: 16
// d2 d0 5b 90 3f e2 54 92 35 f8 7b c7 38 14 85 fb 
// Part 3 -- MAC (with secret key)
// length: 16
// f4 8d 91 08 2c 08 c7 7d 62 e1 be d3 61 5c e8 55

