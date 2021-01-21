/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create mail with HTML read from file

// g++ create_mail_html_file.cpp -std=c++11 `pkg-config --cflags --libs vmime`   

// reference : https://github.com/kisli/vmime/blob/master/examples/example3.cpp


#include <iostream>
#include "create.hpp"
#include "executable_path.hpp"


// prototype
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, std::string filepath,  std::string &error );


/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, std::string filepath,  std::string &error )
{

    if(  !existsFile( filepath) ) {
        error = "not found: " +  filepath;
         return vmime::null;
    }


	std::string html;
	bool ret = readTextFile( filepath,  html );
	if(!ret){
		error = "can not read: " + filepath;
		return vmime::null;
	}

	std::string body = "";

// plain message
	std::string plain = std::string("this is a test mail ")
	+ CRLF
	+ std::string( "this mail has html" )
	+ CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  
	+ CRLF;

	std::cout << plain << std::endl;


	// build message
	vmime::messageBuilder mb = 
	getMessageBuilder( mail_from, mail_to );

// subject
	mb.setSubject(vmime::text(subject));

 // TextPart
	mb.getTextPart()->setText(
	vmime::make_shared <vmime::stringContentHandler>(
	body) );

// Set the content-type to "text/html"
		mb.constructTextPart(
			vmime::mediaType(
				vmime::mediaTypes::TEXT,
				vmime::mediaTypes::TEXT_HTML
			)
		);

		// Fill in the text part: the message is available in two formats: HTML and plain text.
		vmime::htmlTextPart& textPart =
			*vmime::dynamicCast <vmime::htmlTextPart>(mb.getTextPart());

		// text message
		textPart.setText( 
			vmime::make_shared <vmime::stringContentHandler>(
			html )
		);

		textPart.setPlainText(
			vmime::make_shared <vmime::stringContentHandler>(
				plain )
		);

	// construct
	vmime::shared_ptr <vmime::message> msg = mb.construct();

// option header
	msg->getHeader() -> UserAgent() -> setValue( MAILER );

    return msg;
}


using namespace std;


/**
 *  main
 */
int main(int argc, char *argv[])
{

	const std::string  SUBJECT = "create html file";

	string exe_path = getExecutablePathDir( argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath( "data/vmime.html" );



    if (argc == 2) {
      	filepath = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file ] "  << endl;
    }

	string fullpath = exe_path + filepath;

    cout << " fullpath: " <<  fullpath << endl;

	std::string error;
    vmime::shared_ptr <vmime::message> msg = 
	buildCustomMessage(  SUBJECT, FROM, TO, fullpath, error );
	if (msg) {
		saveMessage( msg ) ;
	} else {
        cerr << error << endl;
         return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
