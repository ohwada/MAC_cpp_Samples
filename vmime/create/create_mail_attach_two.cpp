/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create mail with Two attaced files 

//  g++ create/create_mail_attach_two.cpp -std=c++11 `pkg-config --cflags --libs vmime`

#include <iostream>
#include "create.hpp"
#include "executable_path.hpp"


// prototype
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, std::string fullpath1, std::string fullpath2, std::string &error );
	vmime::shared_ptr <vmime::fileAttachment> createFileAttachment( std::string fullpath );

using namespace std;



/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, std::string fullpath1, std::string fullpath2, std::string &error ) 
{


// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has two attachments." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;

    std::cout << body << std::endl;

	// build message
std::string error1;
vmime::shared_ptr <vmime::fileAttachment>  att1 = createFileAttachment( fullpath1, error1 );

if(att1){
   std:: cout << fullpath1 << std::endl;
} else {
    error = error1;
    return vmime::null;
}

std::string error2;
vmime::shared_ptr <vmime::fileAttachment>  att2 = createFileAttachment( fullpath2, error2 );

if(att2){
   std:: cout << fullpath2 << std::endl;
} else {
    error = error2;
    return vmime::null;
}

	// build message
	vmime::messageBuilder mb = getMessageBuilder( mail_from,  mail_to );


// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

	// Adding an attachment
	mb.attach(att1);
	mb.attach(att2);


	// construct
	vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() -> UserAgent() -> setValue( MAILER );

    return msg;
}




/**
 *  main
 */
int main(int argc, char **argv)
{
	 const	string  SUBJECT = "create attach 2";


	string exe_path = getExecutablePathDir(argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath1 = "data/uparrow256.jpg";
	string filepath2 = "data/text_ascii.txt";


    if(argc == 3) {
      	filepath1 = argv[1];
      	filepath2 = argv[2];
    } else {
        cout << "Usage: " << argv[0] << " [file1] [file2] "  << endl;
    }


	string fullpath1 = exe_path + filepath1;
	string fullpath2 = exe_path + filepath2;


    std::string error;
    vmime::shared_ptr <vmime::message> msg = buildCustomMessage(  SUBJECT, FROM, TO, fullpath1,  fullpath2, error );

    if(!msg){
        cerr << error << endl;
         return EXIT_FAILURE;
    }


    saveMessage( msg ) ;


    return EXIT_SUCCESS;
}
