/**
 *  show_zip.cpp
 * 2022-06-01 K.OHWADA
 */

#include <iostream>
#include <string>
#include "ZipFile.h"
#include "ZipArchive.h"


using namespace std;


/**
 *  main
 */
int main()
{

std::string path("sample.zip");

try
      {
         auto archive = ZipFile::Open(path);

         for (size_t i = 0; i < archive->GetEntriesCount(); ++i)
         {
                auto entry = archive->GetEntry(i);
                auto name = entry->GetName();
                std::cout <<  name << std::endl;

         } // for

      }
      catch (std::exception const & ex)
      {
         std::cout << ex.what() << std::endl;
      }
  

    return 0;
}

// sample1.txt
// sample2.txt
// sample3.txt