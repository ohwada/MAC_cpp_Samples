//  gcc sample5.c `pkg-config --cflags --libs nss` 


// https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_sample5

/* Example code to illustrate PKI crypto ops (encrypt with public key,
 * decrypt with private key)
 *
 * No NSS db needed. The Public Key & Private Key to use are
 * sourced from a base64-encoded DER SubjectPublicKeyInfo structure,
 * and a base64-encoded DER PrivateKeyInfo structure.
 *
 * There is no attempt to link the public & private key together
 *
 * This example does not do any padding. It simply encrypts/decrypts a block
 * of length equal to modulus length of the public/private key.
 */

#include <prerror.h>
#include <cert.h>
#include "nss.h"
#include "pk11pub.h"
#include "keyhi.h"
#include "nss/base64.h"

#define BASE64_ENCODED_SUBJECTPUBLICKEYINFO "MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAL3F6TIc3JEYsugo+a2fPU3W+Epv/FeIX21DC86WYnpFtW4srFtz2oNUzyLUzDHZdb+k//8dcT3IAOzUUi3R2eMCAwEAAQ=="

#define BASE64_ENCODED_PRIVATEKEYINFO "MIIBVQIBADANBgkqhkiG9w0BAQEFAASCAT8wggE7AgEAAkEAvcXpMhzckRiy6Cj5rZ89Tdb4Sm/8V4hfbUMLzpZiekW1biysW3Pag1TPItTMMdl1v6T//x1xPcgA7NRSLdHZ4wIDAQABAkEAjh8+4qncwcmGivnM6ytbpQT+k/jEOeXG2bQhjojvnXN3FazGCEFXvpuIBcJVfaIJS9YBCMOzzrAtO0+k2hWnOQIhAOC4NVbo8FQhZS4yXM1M86kMl47FA9ui//OUfbhlAdw1AiEA2DBmIXnsboKB+OHver69p0gNeWlvcJc9bjDVfdLVsLcCIQCPtV3vGYJv2vdwxqZQaHC+YB4gIGAqOqBCbmjD3lyFLQIgA+VTYdUNoqwtZWvE4gRf7IzK2V5CCNhg3gR5RGwxN58CIGCcafoRrUKsM66ISg0ITI04G9V/w+wMx91wjEEB+QBz"


int main(int argc, char **argv)
{
  SECStatus          rv;
  CERTCertificate   *cert = NULL;
  SECKEYPublicKey   *pubkey = NULL;
  CERTSubjectPublicKeyInfo *spki = NULL;
  SECKEYPrivateKey  *pvtkey = NULL;
  int                modulus_len, i, outlen;
  char              *buf1 = NULL;
  char              *buf2 = NULL;
  char              *pubkstr = BASE64_ENCODED_SUBJECTPUBLICKEYINFO;
  char              *pvtkstr = BASE64_ENCODED_PRIVATEKEYINFO;
  SECItem            der;
  SECItem            nickname;
  PK11SlotInfo      *slot = NULL;

  /* Initialize NSS
   * You need to explicitly authenticate to the internal token if you use
   * NSS_Init insteadf of NSS_NoDB_Init
   * Invoke this after getting the internal token handle
   *      PK11_Authenticate(slot, PR_FALSE, NULL);
   */
  rv = NSS_NoDB_Init(".");
  if (rv != SECSuccess)
  {
    fprintf(stderr, "NSS initialization failed (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  /* get internal slot */
  slot = PK11_GetInternalKeySlot();
  if (slot == NULL)
  {
    fprintf(stderr, "Couldn't find slot (err %d)\n", PR_GetError());
    goto cleanup;
  }

  rv = ATOB_ConvertAsciiToItem(&der, pubkstr);
  if (rv!= SECSuccess)
  {
    fprintf(stderr, "ATOB_ConvertAsciiToItem failed %d\n", PR_GetError());
    goto cleanup;
  }
  spki = SECKEY_DecodeDERSubjectPublicKeyInfo(&der);
  SECITEM_FreeItem(&der, PR_FALSE);
  pubkey = SECKEY_ExtractPublicKey(spki);

  if (pubkey == NULL)
  {
    fprintf(stderr, "Couldn't extract public key (err %d)\n", PR_GetError());
    goto cleanup;
  }

  modulus_len = SECKEY_PublicKeyStrength(pubkey);
  fprintf(stderr, "Public Key Modulus %d bytes\n", modulus_len);
  buf1 = (char *)malloc(modulus_len);
  buf2 = (char *)malloc(modulus_len);

  /* initialize buf1 */
  for (i=0;i<modulus_len;i++)
  {
    buf1[i]= (i %26) + 'A';
  }
  buf1[modulus_len-1] = '\0';
  fprintf(stderr, "Buffer being encrypted = \n%s\n", buf1);

  /* encrypt buf1, result will be in buf2 */
  rv = PK11_PubEncryptRaw(pubkey,  (unsigned char *)buf2, (unsigned char *)buf1, modulus_len, NULL);
  if (rv != SECSuccess)
  {
    fprintf(stderr, "Encrypt with Public Key failed (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  nickname.type = siBuffer;
  nickname.data = (unsigned char *)"pvtkeynickname";
  nickname.len = strlen("pvtkeynickname");
  rv = ATOB_ConvertAsciiToItem(&der, pvtkstr);
  if (rv!= SECSuccess)
  {
    fprintf(stderr, "ATOB_ConvertAsciiToItem failed %d\n", PR_GetError());
    goto cleanup;
  }

  /* KU_ALL includes a lot of different key usages, KU_DATA_ENCIPHERMENT
   * is enough for just RSA encryption.
   * publicValue arg (4th) can be NULL for RSA key - I think it is even
   * ignored
   */
  PK11_ImportDERPrivateKeyInfoAndReturnKey(slot, &der, NULL,
                                           NULL, PR_FALSE, PR_TRUE,
                                           KU_ALL, &pvtkey, NULL);
  SECITEM_FreeItem(&der, PR_FALSE);

  if (pvtkey == NULL)
  {
    fprintf(stderr, "Couldn't extract private key (err %d)\n", PR_GetError());
    goto cleanup;
  }

  /* clear buf1 */
  for (i=0;i<modulus_len;i++)
  {
    buf1[i]= '\0';
  }

  /* decrypt buf2, result will be in buf1 */
  rv = PK11_PubDecryptRaw(pvtkey, (unsigned char *)buf1, (unsigned int *)&outlen, modulus_len,  (unsigned char *)buf2,
                          modulus_len);
  if (rv != SECSuccess)
  {
    fprintf(stderr, "Decrypt with Private Key failed (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  fprintf(stderr, "Result of decryption, outlen = %d\n", outlen);
  fprintf(stderr, "Result of decryption, buf = \n%s\n", buf1);

cleanup:
  if (cert)
    CERT_DestroyCertificate(cert);
  if (pubkey)
    SECKEY_DestroyPublicKey(pubkey);
  if (pvtkey)
    SECKEY_DestroyPrivateKey(pvtkey);
  if (spki)
    SECKEY_DestroySubjectPublicKeyInfo(spki);
  if (slot)
    PK11_FreeSlot(slot);
  if (buf1)
    free(buf1);
  if (buf2)
    free(buf2);
  exit(1);
}


// Public Key Modulus 64 bytes
// Buffer being encrypted = 
//ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJK
// Result of decryption, outlen = 64
// Result of decryption, buf = 
// ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJK


