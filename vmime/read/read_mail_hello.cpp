/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail from file
// read simple email like hello.eml

// reference : Vmime book
// listing 5.1 Parsing a message from a file
// https://ken-ohwada.hatenadiary.org/entry/2020/12/30/160715

// g++ read/read_mail_hello.cpp -std=c++11 `pkg-config --cflags --libs vmime_json`

#include <iostream>
#include <fstream>
#include "vmime/vmime.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

    string filepath("samples/hello.eml");

    if (argc == 2) {
      	filepath = argv[1];
    } else {
     cout << "Usage: " << argv[0] << " [file ] "  << endl;
    }

      cout << "filepath: " << filepath  << endl;

// Read data from file
std::ifstream file;
file.open(filepath, std::ios::in | std::ios::binary);
vmime::utility::inputStreamAdapter is(file);
vmime::string data;
vmime::utility::outputStreamStringAdapter os(data);
vmime::utility::bufferedStreamCopy(is , os);

// Actually parse the message
vmime::shared_ptr <vmime::message> msg = vmime::make_shared<vmime::message>();
msg->parse(data);
vmime::shared_ptr <vmime::header> hdr = msg->getHeader();
 vmime::shared_ptr <vmime::body> bdy = msg->getBody();

// Now, you can extract some of its components
vmime::charset ch(vmime::charsets::UTF_8);

std::cout <<  " The subject of the message is : "
<< hdr->Subject()->getValue<vmime::text>()->getConvertedText(ch) << std::endl;

std::cout << " It was sent by: "
<< hdr->From()->getValue<vmime::mailbox>()->getName().getConvertedText(ch)
<<  "( email: " 
<< hdr->From()->getValue<vmime::mailbox>()->getEmail().toString()
<<  " )" << std::endl;

    vmime::utility::outputStreamAdapter	out(std::cout);
    vmime::shared_ptr<const vmime::contentHandler> cts  = bdy->getContents();
    cts->extract(out);


    return EXIT_SUCCESS;
}



// The subject of the message is : Hello from VMime!
 // It was sent by: Vincent( email: vincent@vmime.org )
// A simple message to test VMime



