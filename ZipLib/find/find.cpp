/**
 *  find.cpp
 * 2022-06-01 K.OHWADA
 */

// Finding files in a ZIP archive
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_79/main.cpp

#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "ZipFile.h"
#include "ZipArchive.h"

#include "file_util.hpp"


/**
 *   find_in_archive
 */
std::vector<std::string> find_in_archive(
   std::string const & archivepath,
   std::string pattern)
{
   std::vector<std::string> results;

   if ( existsFile(archivepath) )
   {
      try
      {
         auto archive = ZipFile::Open(archivepath);

         for (size_t i = 0; i < archive->GetEntriesCount(); ++i)
         {
            auto entry = archive->GetEntry(i);
            if (entry)
            {
               if (!entry->IsDirectory())
               {
                  auto name = entry->GetName();
                  if (std::regex_match(name, std::regex{ pattern.data() }))
                  {
                     results.push_back(entry->GetFullName());
                  }
               }
            }
         }
      }
      catch (std::exception const & ex)
      {
         std::cout << ex.what() << std::endl;
      }
   }

   return results;
}

using namespace std;


/**
 *  main
 */
int main()
{
   const string ARCHIVEPATH("sample.zip");
   
   const string PATTERN( R"(^.*\.jpg$)" );
 
     cout << "find " << PATTERN << " in " << ARCHIVEPATH << endl;

    auto list = find_in_archive(ARCHIVEPATH, PATTERN);

   for (auto const & name : list )
   {
      cout << name << endl;
   }

    return 0;
}


// find ^.*\.jpg$ in sample.zip
// einstein/albert einstein.jpg
// einstein/einstein_nobel.jpg
// hawking/Stephen_Hawking.StarChild.jpg
// newton/Isaac_Newton.jpg

