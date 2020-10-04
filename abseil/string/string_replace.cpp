/**
 * abseil sample
 * 2020-07-01 K.OHWADA
 */

// replace substring in string


#include <iostream>
#include <string>
#include "absl/strings/str_replace.h"
#include "absl/strings/str_cat.h"

using namespace std;


/**
 * main
 */
int main(void) 
{

    absl::string_view text(
       "$who bought $count #Noun. Thanks $who!" );

    std::string s = absl::StrReplaceAll(
       text,
       {{"$count", absl::StrCat(5)},
        {"$who", "Bob"},
        {"#Noun", "Apples"}});
//   // EXPECT_EQ("Bob bought 5 Apples. Thanks Bob!", s);

        cout << text << endl;
        cout << s << endl;

    return 0;
}


// $who bought $count #Noun. Thanks $who!
// Bob bought 5 Apples. Thanks Bob!

