/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create mail with attaced file

//  g++ create/create_mail_attach.cpp -std=c++11 `pkg-config --cflags --libs vmime`

// original : https://github.com/kisli/vmime/blob/master/examples/example2.cpp

// This sample program demonstrate the use of the messageBuilder component
// to build a simple message with an attachment.


#include <iostream>
#include "create.hpp"
#include "executable_path.hpp"


using namespace std;


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, string fullpath, std::string &ret_error ) 
{

// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has one attachments." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;


	// build message
    std::string error;
	auto ret = buildMessageFile( subject,  body, mail_from, mail_to, fullpath, error ); 

    if(!ret){
        ret_error = error;
        return vmime::null;
    }

    return ret;
}



/**
 *  main
 */
int main(int argc, char *argv[])
{
	 const	string  SUBJECT = "create attach";

	string exe_path = getExecutablePathDir( argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath( "data/baboon.png" );



    if (argc == 2) {
      	filepath = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file ] "  << endl;
    }

	string fullpath = exe_path + filepath;

    cout << " fullpath: " <<  fullpath << endl;

    std::string error;
    vmime::shared_ptr <vmime::message> msg = buildCustomMessage(  SUBJECT, FROM, TO, fullpath, error );

    if(!msg){
        cerr << error << endl;
         return EXIT_FAILURE;
    }

    saveMessage( msg ) ;
   
    return EXIT_SUCCESS;
}

