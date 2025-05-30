//  gcc sample4.c `pkg-config --cflags --libs nss` 

// https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_sample4

/* Example code to illustrate PKI crypto ops (encrypt with public key,
 * decrypt with private key)
 *
 * Code assumes that you have set up a NSS database with a certificate
 * and a private key. The db password should be "test" and the cert
 * nickname should be "TestCA"
 * Here is one way of doing it:
 *   # create CA cert db, if -f not provided, prompts for passwd
 *   $ certutil -N -d .
 *   # create CA cert, self-signed, generates key-pair, prompts for key
 *   # type, cert type etc
 *   # answers for prompts: 5,9,n,y,-1,n,5,6,7,9,n
 *   $ certutil -S -s "CN=Test CA, O=BOGUS Inc, L=Mtn View, ST=CA, C=US"  \
 *     -n TestCA -t CTu,CTu,CTu -v 60 -x -d . -1 -2 -5
 *
 * There are many ways to setup a public/private key to use - this
 * example shows one of them.
 *
 * This example does not do any padding. It simply encrypts/decrypts a block
 * of length equal to modulus length of the public/private key.
 */

#include <prerror.h>
#include <cert.h>
#include "nss.h"
#include "pk11pub.h"
#include "keyhi.h"

/* this callback is responsible for returning the password to the NSS
 * key database. for example purposes, this function hardcodes the password.
 * In a real app, this function should obtain the password using secure means
 * such as prompting an operator, or retrieving it over a secure communication
 * channel
 */
char *passwdcb(PK11SlotInfo *info, PRBool retry, void *arg);


int main(int argc, char **argv)
{
  SECStatus          rv;
  CERTCertificate   *cert = NULL;
  SECKEYPublicKey   *pubkey = NULL;
  SECKEYPrivateKey  *pvtkey = NULL;
  int                modulus_len, i, outlen;
  char              *buf1 = NULL;
  char              *buf2 = NULL;

  /* Initialize NSS */
  PK11_SetPasswordFunc(passwdcb);
  rv = NSS_Init(".");
  if (rv != SECSuccess)
  {
    fprintf(stderr, "NSS initialization failed (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  cert = PK11_FindCertFromNickname("TestCA", NULL);
  if (cert == NULL)
  {
    fprintf(stderr, "Couldn't find cert TestCA in NSS db (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  pubkey = CERT_ExtractPublicKey(cert);
  if (pubkey == NULL)
  {
    fprintf(stderr, "Couldn't extract public key from cert TestCA (err %d)\n",
            PR_GetError());
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
  rv = PK11_PubEncryptRaw(pubkey, (unsigned char *)buf2, (unsigned char *)buf1, modulus_len, NULL);
  if (rv != SECSuccess)
  {
    fprintf(stderr, "Encrypt with Public Key failed (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  pvtkey = PK11_FindKeyByAnyCert(cert, NULL);
  if (pvtkey == NULL)
  {
    fprintf(stderr, "Couldn't find private key for cert TestCA (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  /* clear buf1 */
  for (i=0;i<modulus_len;i++)
  {
    buf1[i]= '\0';
  }

  /* decrypt buf2, result will be in buf1 */
  rv = PK11_PubDecryptRaw(pvtkey, (unsigned char *)buf1, (unsigned int *)&outlen, modulus_len, (unsigned char *)buf2,
                          modulus_len);
  if (rv != SECSuccess)
  {
    fprintf(stderr, "Decrypt with Private Key failed (err %d)\n",
            PR_GetError());
    goto cleanup;
  }

  fprintf(stderr, "Result of decryption, outlen = %d\n", outlen);
  fprintf(stderr, "Result of decryption, buf = \n%s\n", buf1);

  exit(0);

cleanup:
  if (cert)
    CERT_DestroyCertificate(cert);
  if (pubkey)
    SECKEY_DestroyPublicKey(pubkey);
  if (pvtkey)
    SECKEY_DestroyPrivateKey(pvtkey);
  if (buf1)
    free(buf1);
  if (buf2)
    free(buf2);
  exit(1);
}

char *passwdcb(PK11SlotInfo *info, PRBool retry, void *arg)
{
  if (!retry)
    return PL_strdup("test");
  else
    return NULL;
}


// Public Key Modulus 256 bytes
// Buffer being encrypted = 
// ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU
// Result of decryption, outlen = 256
// Result of decryption, buf = 
// ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTU

