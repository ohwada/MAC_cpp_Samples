/**
 * cpp-httplib sample
 * 2020-07-01 K.OHWADA
 */

// HTTP post server

// original : https://github.com/yhirose/cpp-httplib/blob/master/example/upload.cc

//
//  upload.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//


#include <iostream>
#include <fstream>
#include "httplib.h"


using namespace httplib;
using namespace std;


/**
 * input form
 */
const char *html = R"(
<form id="formElem">
  <input type="file" name="image_file" accept="image/*">
  <input type="file" name="text_file" accept="text/*">
  <input type="submit">
</form>
<script>
  formElem.onsubmit = async (e) => {
    e.preventDefault();
    let res = await fetch('/post', {
      method: 'POST',
      body: new FormData(formElem)
    });
    console.log(await res.text());
  };
</script>
)";
// input form


/**
 * main
 */
int main(void) 
{

    const char *HOST = "localhost";

    const int PORT = 8080;

  Server svr;

// get root : return input form
  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_content(html, "text/html");
  });

// post
  svr.Post("/post", [](const Request &req, Response &res) {
    auto image_file = req.get_file_value("image_file");
    auto text_file = req.get_file_value("text_file");

    auto image_filename = mage_file.filename;
    auto text_filename = text_file.filename;

    cout << "image file length: " << image_file.content.length() << endl
         << "image file name: " << image_file.filename << endl
         << "text file length: " << text_file.content.length() << endl
         << "text file name: " << text_file.filename << endl;

    {
        ofstream ofs1(image_file.filename, ios::binary);
        ofs1 << image_file.content;
        cout << "saved to :" << text_filename << endl;
    }

    {
        ofstream ofs2( text_filename );
        ofs2 << text_file.content;
        cout << "saved to :" << text_filename << endl;
    }

    res.set_content("done", "text/plain");
  });

  svr.listen(HOST, PORT);

   return EXIT_SUCCESS;
}
