/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */


// read mail message from file

#include <iostream>
#include <string>
#include "pop3.hpp"


using namespace std;


/**
 *  main
 */
int main(int argc, char* argv[])
{

    string filepath(sample.eml); 

    if (argc == 2) {
      	filepath = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file ] "  << endl;
    }

    cout << "filepath: " << filepath  << endl;

// Read data from file
std::ifstream file;
file.open( filepath, std::ios::in | std::ios::binary );
vmime::utility::inputStreamAdapter is(file);
vmime:: string data;
vmime:: utility::outputStreamStringAdapter os(data);
vmime:: utility::bufferedStreamCopy(is , os);

// Actually parse the message
vmime::shared ptr <vmime::message> msg = vmime::make shared <vmime: : message>();
msg->parse(data);
vmime::shared ptr <vmime::header> hdr = msg−>getHeader(); vmime::shared ptr <vmime::body> bdy = msg−>getBody();
// Now, you can extract some of its components
vmime::charset ch(vmime::charsets::UTF8);
std::cout
<< ”The subject of the message is : ”
<< hdr−>Subject()−>getValue <vmime::text>()−>getConvertedText(ch)
<< std::endl
<< ”It was sent by: ”
<< hdr−>From()−>getValue <vmime::mailbox>()−>getName().getConvertedText(ch) << ” (email: ” << hdr−>From()−>getValue <vmime::mailbox>()−>getEmail() << ”)” << std::endl;

    return EXIT_SUCCESS;
}




