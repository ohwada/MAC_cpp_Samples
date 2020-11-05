/**
 * libcurl sample
 * 2020-07-01 K.OHWADA
 */

// test for getGmailParam
// g++ curlsmtp/test_mail_json.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`

#include <iostream>
#include "curlsmtp_util.hpp"

using namespace std;


/**
 *  main
 */
int main(void)
{

    cout << "Gmail" << endl;
    MailParam  p1 = getGmailParam();
    printMailParam( p1 );

    cout << "Ubuntu" << endl;
    MailParam  p2 = getUbuntuMailParam();
    printMailParam( p2 );

  return 0;
}


// UbuntuMailParam
// smtp_url: smtp://ubuntu:25
// smtp_server: ubuntu
// smtp_port: 25
// user: taro
// passwd: 123456789
// to: taro@ubuntu
// from: hoge@example.org

