/**
 *  logger.cpp
 * 2022-06-01 K.OHWADA
 */

// original ; https://github.com/pocoproject/poco/blob/devel/Foundation/samples/Logger/src/Logger.cpp
// reference : https://codezine.jp/article/detail/1901?p=2

// Logger.cpp
// This class demonstrates the Logger, PatternFormatter, FormattingChannel,
// ConsoleChannel and FileChannel classes.

#include "Poco/Logger.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"


using namespace std;
using Poco::Logger;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;


/**
 *  main
 */
int main(int argc, char** argv)
{
	string file("log/sample.log");

	// set up two channel chains - one to the
	// console and the other one to a log file.
	FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("[%O] %s: %p: %t"));
	pFCConsole->setChannel(new ConsoleChannel);
	pFCConsole->open();

// log file
	FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
	pFCFile->setChannel(new FileChannel(file));
	pFCFile->open();

	// create two Logger objects - one for
	// each channel chain.
	Logger& consoleLogger = Logger::create("ConsoleLogger", pFCConsole, Message::PRIO_INFORMATION);
	Logger& fileLogger    = Logger::create("FileLogger", pFCFile, Message::PRIO_WARNING);

	// log some messages
	consoleLogger.error("An error message");
	fileLogger.error("An error message");

	consoleLogger.warning("A warning message");
	fileLogger.error("A warning message");

	consoleLogger.information("An information message");
	fileLogger.information("An information message");

	poco_information(consoleLogger, "Another informational message");
	poco_warning_f2(consoleLogger, "A warning message with arguments: %d, %d", 1, 2);

	Logger::get("ConsoleLogger").error("Another error message");

	return 0;
}
