/**
 * imap.cpp
 * 2022-06-01 K.OHWADA
 */


// Fetching emails using IMAP  
// original: https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter12/problem_98/main.cpp

#include <iostream>
#include <string>

#include "curl_easy.h"
#include "curl_exception.h"

#include "json_mail.hpp"


/**
 * class imap_connection
 */
class imap_connection
{
public:
   imap_connection(
      std::string url,
      unsigned short const port,
      std::string user,
      std::string pass):
      url(url), port(port), user(user), pass(pass)
   {
   }


/**
 * get_folders
 */
   std::string get_folders()
   {
      std::stringstream str;
      try
      {
         curl::curl_ios<std::stringstream> writer(str);

         curl::curl_easy easy(writer);
         easy.add<CURLOPT_URL>(url.data());
         setup_easy(easy);

         easy.perform();
      }
      catch (curl::curl_easy_exception const & error)
      {
         auto errors = error.get_traceback();
         error.print_traceback();
      }

      return str.str();
   }


/**
 * examine_folder
 */
   std::string examine_folder(std::string folder)
   {
      std::stringstream str;
      try
      {
         curl::curl_ios<std::stringstream> writer(str);

         curl::curl_easy easy(writer);
         easy.add<CURLOPT_URL>(url.data());
         easy.add<CURLOPT_CUSTOMREQUEST>((std::string("EXAMINE ") + folder.data()).c_str());
         setup_easy(easy);

         easy.perform();
      }
      catch (curl::curl_easy_exception const & error)
      {
         auto errors = error.get_traceback();
         error.print_traceback();
      }

      return str.str();
   }


/**
 * fetch_unread_uids
 */
   std::vector<unsigned int> fetch_unread_uids(std::string folder)
   {
      std::stringstream str;

      try
      {
         curl::curl_ios<std::stringstream> writer(str);

         curl::curl_easy easy(writer);
         easy.add<CURLOPT_URL>((url.data() + std::string("/") + folder.data() + std::string("/")).c_str());
         easy.add<CURLOPT_CUSTOMREQUEST>("SEARCH UNSEEN");
         setup_easy(easy);

         easy.perform();
      }
      catch (curl::curl_easy_exception const & error)
      {
         auto errors = error.get_traceback();
         error.print_traceback();
      }

      std::vector<unsigned int> uids;
      str.seekg(8, std::ios::beg);
      unsigned int uid;
      while (str >> uid)
         uids.push_back(uid);

      return uids;
   }


/**
 * fetch_email
 */
   std::string fetch_email(std::string folder, unsigned int uid)
   {
      std::stringstream str;

      try
      {
         curl::curl_ios<std::stringstream> writer(str);

         curl::curl_easy easy(writer);
         easy.add<CURLOPT_URL>((url.data() + std::string("/") + folder.data() + std::string("/;UID=") + std::to_string(uid)).c_str());
         setup_easy(easy);

         easy.perform();
      }
      catch (curl::curl_easy_exception error)
      {
         auto errors = error.get_traceback();
         error.print_traceback();
      }

      return str.str();
   }

private:
   void setup_easy(curl::curl_easy& easy)
   {
      easy.add<CURLOPT_PORT>(port);
      easy.add<CURLOPT_USERNAME>(user.c_str());
      easy.add<CURLOPT_PASSWORD>(pass.c_str());
      easy.add<CURLOPT_USE_SSL>(CURLUSESSL_ALL);
      easy.add<CURLOPT_SSL_VERIFYPEER>(0L);
      easy.add<CURLOPT_SSL_VERIFYHOST>(0L);
      easy.add<CURLOPT_USERAGENT>("libcurl-agent/1.0");
   }

private:
   std::string    url;
   unsigned short port;
   std::string    user;
   std::string    pass;
};

using namespace std;


/**
 * main
 */
int main()
{
 const unsigned short PORT = 993;
const string INBOX("inbox");

    struct MailParam  p = getUbuntuMailParam();
    printMailParam( p );

const string URL = p.imap_url;
const string USER = p.user;
const string PASSWD = p.passwd;

   imap_connection imap(
    URL, PORT, USER, PASSWD );

   auto folders = imap.get_folders();
   cout << folders << endl;

   auto info = imap.examine_folder(INBOX);
   cout << info << endl;

   auto uids = imap.fetch_unread_uids(INBOX);

   cout << "unread: " << uids.size() << endl;

   if (!uids.empty())
   {
      auto email = imap.fetch_email( INBOX, uids.back());
      cout << email << endl;
   }

   return 0;
}


// unread: 1
// ERROR: Remote file not found ::::: FUNCTION: perform
