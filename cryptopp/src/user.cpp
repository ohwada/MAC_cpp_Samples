/**
 * user.cpp
 * 2022-06-01 K.OHWADA
 */

// Validating user credentials  with SHA hash
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter11/problem_91/main.cpp

#include <iostream>
#include <string>
#include <string>
#include <iomanip>
#include <vector>

#include "sha.h"
#include "hex.h"


/**
 * struct user
 */
struct user
{
   int id;
   std::string username;
   std::string password;
   std::string firstname;
   std::string lastname;
};


/**
 *  get_hash
 */
std::string get_hash(std::string password)
{
   CryptoPP::SHA512 sha;
   CryptoPP::byte digest[CryptoPP::SHA512::DIGESTSIZE];

   sha.CalculateDigest(
      digest,
      reinterpret_cast<CryptoPP::byte const*>(password.data()),
      password.length());

   CryptoPP::HexEncoder encoder;
   std::string result;

   encoder.Attach(new CryptoPP::StringSink(result));
   encoder.Put(digest, sizeof(digest));
   encoder.MessageEnd();

   return result;
}

using namespace std;


/**
 * main
 */
int main()
{

const string USER1("scarface");
const string PASSWD1("1234");
const string USER2("neo");
const string PASSWD2("5678");
const string USER3("godfather");
const string PASSWD3("9876");

const string HASH1 = get_hash(PASSWD1);
const string HASH2 = get_hash(PASSWD2);
const string HASH3 = get_hash(PASSWD3);

cout << USER1 << " : " << PASSWD1 << endl;
cout << USER2 << " : " << PASSWD2 << endl;
cout << USER3 << " : " << PASSWD3 << endl;

   vector<user> users
   {
      {
         101, USER1, HASH1,
         "Tony", "Montana"
      },
      {
         202, USER2, HASH2,
         "Thomas", "Anderson"
      },
      {
         303, USER3, HASH3,
         "Vito", "Corleone"
      }
   };


   string username, password;
   cout << "Username: ";
   cin >> username;

   cout << "Password: ";
   cin >> password;

   auto hash = get_hash(password);

   auto pos = std::find_if(
      std::begin(users), std::end(users),
      [username, hash](user const & u) {
      return u.username == username &&
         u.password == hash; });

   if (pos != std::end(users))
      cout << "Login successful!" << endl;
   else
      cout << "Invalid username or password" << endl;

    return 0;
}

// Username: scarface
// Password: 1234
// Login successful!

