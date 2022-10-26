/**
 *  now.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/pocoproject/poco/blob/devel/Foundation/samples/DateTime/src/DateTime.cpp
//

#include <iostream>
#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"


using namespace std;
using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::DateTimeParser;


/**
 *  main
 */
int main(int argc, char** argv)
{
	LocalDateTime now;
	string str = DateTimeFormatter::format(now, DateTimeFormat::ISO8601_FORMAT);

	cout << str << endl;

	return 0;
}
