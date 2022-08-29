/**
 * image.cpp
 * 2022-06-01 K.OHWADA
 */

// Creating a PDF from a collection of images  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_78/main.cpp

#include <iostream>
#include <string_view>

#include "PDFWriter/PDFWriter.h"
#include "PDFWriter/PDFPage.h"
#include "PDFWriter/PageContentContext.h"
#include "PDFWriter/PDFFormXObject.h"

#ifdef USE_BOOST_FILESYSTEM
#  include <boost/filesystem/path.hpp>
#  include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;
#else
#  include <filesystem>
#  ifdef FILESYSTEM_EXPERIMENTAL
namespace fs = std::experimental::filesystem;
#  else
namespace fs = std::filesystem;
#  endif
#endif


/**
 * get_images
 */
std::vector<std::string> get_images(fs::path const & dirpath)
{
   std::vector<std::string> paths;

   for (auto const & p : fs::directory_iterator(dirpath))
   {
      if (p.path().extension() == ".jpg")
         paths.push_back(p.path().string());
   }

   return paths;
}


/**
 * print_pdf
 */
void print_pdf(
   fs::path const & pdfpath,
   fs::path const & dirpath)
{
   const int height = 842;
   const int width = 595;
   const int margin = 20;

   auto image_paths = get_images(dirpath);

   PDFWriter pdf;
   pdf.StartPDF(pdfpath.string(), ePDFVersion13);

   PDFPage* page = nullptr;
   PageContentContext* context = nullptr;

   auto top = height - margin;
   for (size_t i = 0; i < image_paths.size(); ++i)
   {
      auto dims = pdf.GetImageDimensions(image_paths[i]);

      if (i == 0 || top - dims.second < margin)
      {
         if (page != nullptr)
         {
            pdf.EndPageContentContext(context);
            pdf.WritePageAndRelease(page);
         }

         page = new PDFPage();
         page->SetMediaBox(PDFRectangle(0, 0, width, height));
         context = pdf.StartPageContentContext(page);

         top = height - margin;
      }

      context->DrawImage(margin, top - dims.second, image_paths[i]);

      top -= dims.second + margin;
   }

   if (page != nullptr)
   {
      pdf.EndPageContentContext(context);
      pdf.WritePageAndRelease(page);
   }

   pdf.EndPDF();
}


/**
 * main
 */
int main()
{
    const std::string FILE("einstein.pdf");

   print_pdf(FILE, "images");

std::cout << "created: " << FILE << std::endl;

    return 0;
}

> created einstein.pdf

