/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// create mail with ISO2022JP encoding
 
// g++ create_mail_iso2022jp.cpp -std=c++11 `pkg-config --cflags --libs vmime`  

#include <iostream>
#include "create.hpp"
#include "vmime_charset.hpp"

using namespace std;


/** 
 * buildCustomMessage
  */
vmime::shared_ptr <vmime::message> buildCustomMessage(std::string mail_from, std::string mail_to ) 
{

    const std::string  SUBJECT = u8"create iso2022jp テスト";


// build body 
	const std::string body_utf8 = 
	std::string( u8"これはテストメールです。" )
     + CRLF
	+ std::string( u8"このメールの文字コードは ISO-2022-JP です。" )
     + CRLF
	 + std::string( u8"このメールは下記の Mailer を使って送信されました。" )
     + CRLF
	 + std::string( "Mailer: " )
    +  MAILER  + CRLF;


// iso2022jp
    string subject_iso2022;
    from_utf8(SUBJECT, subject_iso2022, CHARSET_ISO2022JP );

    string body_iso2022;
    from_utf8(body_utf8, body_iso2022,  CHARSET_ISO2022JP );


// build message 
    return buildMessageCharset( subject_iso2022, body_iso2022,  mail_from, mail_to,  CHARSET_ISO2022JP ) ;

}


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
