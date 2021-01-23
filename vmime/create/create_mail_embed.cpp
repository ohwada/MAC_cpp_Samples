/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create mail with HTML embedded image

//  g++ create/create_mail_embed.cpp -std=c++11 `pkg-config --cflags --libs vmime`


// Document
// https://ken-ohwada.hatenadiary.org/entry/2021/01/23/092143


// This sample program demonstrate the use of the messageBuilder component
// to build a complex message (HTML content, plain text and embedded image)
// reference : https://github.com/kisli/vmime/blob/master/examples/example3.cpp


#include <iostream>
#include "create.hpp"
#include "executable_path.hpp"



/**
 *  buildCustomMessage
 */
vmime::shared_ptr <vmime::message> 
buildCustomMessage( std::string subject, std::string mail_from, std::string mail_to, string fullpath, std::string &error )
{


    if(  !existsFile( fullpath) ) {
        error = "not found: " +  fullpath;
         return vmime::null;
    }


// build body 
	const std::string body = 
	std::string( "This is a test e-mail." )
     + CRLF
	+ std::string ("This mail has HTML and embedded image." )
     + CRLF
	+ std::string( "This mail was sent using ")
    + MAILER  + CRLF;

	cout << body << endl;


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
		// HTML text part also includes an inline image (embedded into the message).
		vmime::htmlTextPart& textPart =
			*vmime::dynamicCast <vmime::htmlTextPart>(mb.getTextPart());

		// -- embed an image (the returned "CID" (content identifier) is used to reference
		// -- the image into HTML content).
		vmime::shared_ptr <vmime::utility::fileSystemFactory> fs = 
			vmime::platform::getHandler()->getFileSystemFactory();

	vmime::shared_ptr <vmime::utility::file> imageFile =
			fs->create( fs->stringToPath( fullpath ) );

		vmime::shared_ptr <vmime::utility::fileReader> fileReader =
			imageFile->getFileReader();

		vmime::shared_ptr <vmime::contentHandler> imageCts =
			vmime::make_shared <vmime::streamContentHandler>(
				fileReader->getInputStream(),
				imageFile->getLength()
			);

	vmime::mediaType media_type;
	getMediaTypeFromFullpath( fullpath, media_type);

		vmime::shared_ptr <const vmime::htmlTextPart::embeddedObject> obj =
			textPart.addObject(
				imageCts, media_type );

// html message
	string html = string( "This is the <b>HTML</b> text. <br/><br/>" )
	+ string( "this mail has <b>embed image</b>. <br/><br/>" )
	+ string("<img src=\"" ) 
	+ obj->getReferenceId() 
	+ string( "\"/>" );

	cout << html << endl;

		// text message
		textPart.setText( 
			vmime::make_shared <vmime::stringContentHandler>(
			html )
		);

		textPart.setPlainText(
			vmime::make_shared <vmime::stringContentHandler>(
				body )
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
int main(int argc, char **argv)
{

	const	std::string  SUBJECT = "create embed";

	string exe_path = getExecutablePathDir(argv[0] );
	cout << "ExecutablePathDir: " << exe_path << endl;

	string filepath( "data/uparrow256.jpg" );

    if (argc == 2) {
      	filepath = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " [file ] "  << endl;
    }

	string fullpath = exe_path + filepath;


	std::string error;
    vmime::shared_ptr <vmime::message> msg = 
	buildCustomMessage(  SUBJECT, FROM, TO, fullpath, error );

    if(!msg){
        cerr << error << endl;
         return EXIT_FAILURE;
    }

	saveMessage( msg ) ;

	return EXIT_SUCCESS;
}
