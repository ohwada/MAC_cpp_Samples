#pragma once
/**
 *  zip_util.h
 * 2022-06-01 K.OHWADA
 */

// Compressing and decompressing files to/from a ZIP archive with a password
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter10/problem_81/main.cpp

// TODO  
// unzipping the compressed file is empty


#include <iostream>
#include <string>
#include <string_view>
#include <fstream>

#include "ZipFile.h"
#include "utils/stream_utils.h"

#include <filesystem>

namespace fs = std::filesystem;


// prototype
void compress(
   fs::path const & source,
   fs::path const & archive,
   std::string_view password,
   std::function<void(std::string_view)> reporter);
void decompress(
   fs::path const & destination,
   fs::path const & archive,
   std::string_view password,
   std::function<void(std::string_view)> reporter);
void ensure_directory_exists(fs::path const & dir);


/**
 *  compress
 */
void compress(
   fs::path const & source,
   fs::path const & archive,
   std::string_view password,
   std::function<void(std::string_view)> reporter)
{
   if (fs::is_regular_file(source))
   {
      if (reporter) reporter("Compressing " + source.string());
      ZipFile::AddEncryptedFile(
         archive.string(),
         source.string(),
         source.filename().string(),
         password.data(),
         LzmaMethod::Create());
   }
   else
   {
      for (auto const & p : fs::recursive_directory_iterator(source))
      {
         if (reporter) reporter("Compressing " + p.path().string());

         if (fs::is_directory(p))
         {
            auto zipArchive = ZipFile::Open(archive.string());
            auto entry = zipArchive->CreateEntry(p.path().string());
            entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
            ZipFile::SaveAndClose(zipArchive, archive.string());
         }
         else if (fs::is_regular_file(p))
         {
            ZipFile::AddEncryptedFile(
               archive.string(),
               p.path().string(),
               p.path().filename().string(),
               password.data(),
               LzmaMethod::Create());
         }
      }
   }
}


/**
 *  ensure_directory_exists
 */
void ensure_directory_exists(fs::path const & dir)
{
   if (!fs::exists(dir))
   {
#ifdef USE_BOOST_FILESYSTEM
      boost::system::error_code err;
#else
      std::error_code err;
#endif
      fs::create_directories(dir, err);
   }
}


/**
 *  decompress
 */
void decompress(
   fs::path const & destination,
   fs::path const & archive,
   std::string_view password,
   std::function<void(std::string_view)> reporter)
{
   ensure_directory_exists(destination);

   auto zipArchive = ZipFile::Open(archive.string());

   for (size_t i = 0; i < zipArchive->GetEntriesCount(); ++i)
   {
      auto entry = zipArchive->GetEntry(i);
      if (entry)
      {
         auto filepath = destination / fs::path{ entry->GetFullName() }.relative_path();
         if (reporter) reporter("Creating " + filepath.string());

         if (entry->IsPasswordProtected())
            entry->SetPassword(password.data());

         if (entry->IsDirectory())
         {
            ensure_directory_exists(filepath);
         }
         else
         {
            ensure_directory_exists(filepath.parent_path());

            std::ofstream destFile;
            destFile.open(
               filepath.string().c_str(),
               std::ios::binary | std::ios::trunc);

            if (!destFile.is_open())
            {
               if (reporter)
                  reporter("Cannot create destination file!");
            }

            auto dataStream = entry->GetDecompressionStream();
            if (dataStream)
            {
               utils::stream::copy(*dataStream, destFile);
            }
         }
      }
   }
}
