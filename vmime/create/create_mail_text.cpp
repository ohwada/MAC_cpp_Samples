/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create plain text mail

// g++ create_mail_text.cpp -std=c++11 `pkg-config --cflags --libs vmime`   

// original : https://github.com/kisli/vmime/blob/master/examples/example1.cpp

// This sample program demonstrate the use of the messageBuilder component
// to build a simple message.

#include <iostream>
#include "create.hpp"

using namespace std;



/**
 *  main
 */
int main(void) 
{
    const	std::string  SUBJECT("create test");

    std::string body = getDefaultBody();
    vmime::shared_ptr <vmime::message> msg = buildMessage( SUBJECT, body, FROM, TO) ;

    printMessage( msg ) ;

    saveMessage( msg ) ;

    return EXIT_SUCCESS;
}

