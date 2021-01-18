/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// test for mail_json.hpp and getGmailParam()

// g++ test_json_mail.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include "../pop3/json_mail.hpp"

using namespace std;


/**
 *  main
 */
int main(void)
{

    cout << "Gmail" << endl;
    MailParam  p1 = getGmailParam();
    printMailParam( p1 );

    cout << "Ocn" << endl;
    MailParam  p2 = getOcnMailParam();
    printMailParam( p2 );

    cout << "Ubuntu" << endl;
    MailParam  p3 = getUbuntuMailParam();
    printMailParam( p3 );

    return EXIT_SUCCESS;
}


// smtp_url: smtp://smtp.gmail.com:587
// pop_url: pop3s://pop.gmail.com:995
// imap_url: imaps://imap.gmail.com:993
// user: user@gmail.com
// passwd: 123456789
// to: user@gmail.com
// from: user@gmail.com
