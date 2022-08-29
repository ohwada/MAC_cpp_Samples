/**
 * simple.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ simple.cpp -std=c++11  `pkg-config --cflags --libs pdfwriter`

// create one page PDF: 100X100 cyan square
// reference : https://github.com/galkahana/PDF-Writer/wiki/Adding-Content-to-PDF-Pages


#include <PDFWriter/PDFWriter.h>
#include <PDFWriter/PDFPage.h>
#include <PDFWriter/PageContentContext.h>


/**
 * main
 */
int main()
{
std::string FILE("test.pdf");

PDFWriter pdfWriter;
pdfWriter.StartPDF(FILE,ePDFVersion13);
PDFPage* page = new PDFPage();
// A4 Size
page->SetMediaBox(PDFRectangle(0, 0, 595, 842));
PageContentContext* contentContext = pdfWriter.StartPageContentContext(page); 
contentContext->q();
// cyan
contentContext->k(100,0,0,0);
// 100X100 square
contentContext->re(100,500,100,100);
contentContext->f();
contentContext->Q();
pdfWriter.EndPageContentContext(contentContext);
pdfWriter.WritePageAndRelease(page); 
pdfWriter.EndPDF();

std::cout << "created: "<< FILE << std::endl;
return 0;
}

// created test.pdf
