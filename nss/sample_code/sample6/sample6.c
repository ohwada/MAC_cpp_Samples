//  gcc sample6.c `pkg-config --cflags --libs nss` 

// https://developer.mozilla.org/en-US/docs/Mozilla/Projects/NSS/nss_sample_code/NSS_Sample_Code_sample6

/* Example code to illustrate generation of a secret symmetric key ring
 * that PERSISTS in the NSS database. The symmetric keys can then be used
 * without ever exposing them in the clear.
 *
 * To encrypt, you need the id of the key to use.
 * To decrypt, you need the ciphertext and the id of the key that was used
 * to encrypt
 *
 * Before running this example, create the NSS database
 *     certutil -N -d .
 * (enter "test" when prompted for password)
 */

#include <prerror.h>
#include "nss.h"
#include "pk11pub.h"

/* the key id can be any sequence of bytes. this example happens to use an
 * integer */
void genkey(int id);

/* this callback is responsible for returning the password to the NSS
 * key database. for example purposes, this function hardcodes the password.
 * In a real app, this function should obtain the password using secure means
 * such as prompting an operator, or retrieving it over a secure communication
 * channel
 */
char *passwdcb(PK11SlotInfo *info, PRBool retry, void *arg);


int main(int argc, char **argv)
{
  SECStatus rv;

  /* Initialize NSS */
  PK11_SetPasswordFunc(passwdcb);

  /* The NSS db must be initialized read-write since we'll be creating
   * keys in it. Once keys are generated, it can be opened without read-write
   * subsequently (NSS_Init).
   */
  rv = NSS_InitReadWrite(".");
  if (rv != SECSuccess)
  {
    fprintf(stderr, "NSS initialization failed (err %d)\n",
            PR_GetError());
    exit(1);
  }

  /* generate a key with id 1. should succeed on first run on a fresh db,
   * should fail on successive runs because key with that id already exists */
  genkey(1);

  /* generate a key with id 2. should succeed on first run on a fresh db,
   * should fail on successive runs because key with that id already exists */
  genkey(2);

  /* generate a key with id 1 - this will fail because key with that id
   * already exists */
  genkey(1);
}


void genkey(int id)
{
  PK11SlotInfo*  slot = NULL;
  PK11SymKey*    key = NULL;
  SECItem        keyiditem;
  int            keyid[1];
  CK_MECHANISM_TYPE cipherMech;

  /* using CKM_AES_CBC_PAD mechanism for example */
  cipherMech = CKM_AES_CBC_PAD;

   slot = PK11_GetInternalKeySlot();
  /* slot = PK11_GetBestSlot(cipherMech, NULL); didn't work.
   * Error code: token is read-only. ??
   */
  if (slot == NULL)
  {
    fprintf(stderr, "Unable to find security device (err %d)\n",
            PR_GetError());
    return;
  }

  keyid[0] = id;
  keyiditem.type = siBuffer;
  keyiditem.data = (void *)keyid;
  keyiditem.len = sizeof(keyid[0]);

  /* Note: keysize must be 0 for fixed key-length algorithms like DES.
   *       Since we're using AES in this example, we're specifying
   *       one of the valid keysizes (16, 24, 32)
   */
  key = PK11_TokenKeyGen(slot, cipherMech, 0, 32 /*keysize*/,
                         &keyiditem, PR_TRUE, 0);
  if (key == NULL)
  {
    fprintf(stderr, "PK11_TokenKeyGen failed (err %d)\n",
            PR_GetError());
    PK11_FreeSlot(slot);
    return;
  }

  fprintf(stderr, "key length of generated key is %d\n",
          PK11_GetKeyLength(key));

  fprintf(stderr, "mechanism of key is %lu (asked for %lu)\n",
          PK11_GetMechanism(key), cipherMech );

  PK11_FreeSymKey(key);


  key = PK11_FindFixedKey(slot, cipherMech, &keyiditem, 0);
  if (key == NULL)
  {
    fprintf(stderr, "PK11_FindFixedKey failed (err %d)\n",
            PR_GetError());
    PK11_FreeSlot(slot);
    return;
  }

  fprintf(stderr, "Found key!\n");
  fprintf(stderr, "key length of generated key is %d\n",
          PK11_GetKeyLength(key));

  fprintf(stderr, "mechanism of key is %lu (asked for %lu)\n",
          PK11_GetMechanism(key), cipherMech );

  PK11_FreeSymKey(key);

  PK11_FreeSlot(slot);
}

char *passwdcb(PK11SlotInfo *info, PRBool retry, void *arg)
{
  if (!retry)
    return PL_strdup("test");
  else
    return NULL;
}


// key length of generated key is 32
// mechanism of key is 4229 (asked for 4229)
// Found key!

