/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create mail with UTF8 encoding
 
// g++ create_mail_utf8.cpp -std=c++11 `pkg-config --cflags --libs vmime`  

#include <iostream>
#include "create.hpp"


/** 
 * buildCustomMessage
  */
vmime::shared_ptr <vmime::message> buildCustomMessage(std::string mail_from, std::string mail_to ) 
{

    const vmime::charset CHARSET( vmime::charsets::UTF_8 );

    const string  SUBJECT = u8"create utf8 テスト";


// build body 
	const std::string body = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは UTF-8 です。" )
     + CRLF
	 + std::string( u8"このメールは下記の Mailer を使って送信されました。" )
     + CRLF
	 + std::string( "Mailer: " )
    +  MAILER  + CRLF;

    cout << body << endl;


// build message 
    return buildMessageCharset( SUBJECT, body,  mail_from, mail_to, CHARSET ) ;

}


using namespace std;


/**
 *  main
 */
int main(void)
{

    vmime::shared_ptr <vmime::message> msg = buildCustomMessage( FROM, TO ) ;

    // printMessage( msg ) ;

    saveMessage( msg ) ;

    return EXIT_SUCCESS;
}
