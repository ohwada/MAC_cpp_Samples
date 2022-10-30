/**
 * test_readMailParam.cpp
 * 2022-06-01 K.OHWADA
 */

// parse mail json file
// test for getGmailParam

// g++ test/test_src_readMailParam.cpp  -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include <string>
#include <cassert>
#include "../oauth2/json_mail.hpp"

using namespace std;


/**
 * main
 */
int main(void) 
{

    struct MailParam p = getGmailParam();
    printMailParam(p);

  assert(p.smtp_url == "smtp://smtp.gmail.com:587");

    cout << "successful" << endl;

	return EXIT_SUCCESS;
}


// smtp_url: smtp://smtp.gmail.com:587 
// smtp_server: smtp.gmail.com 
// smtp_port: 993 
// pop_url: pop3s://pop.gmail.com:995 
// imap_url: imaps://imap.gmail.com:993 
// user: user@gmail.com 
// passwd: password 
// to: user@gmail.com 
// from: user@gmail.com 

