/**
 * poco_log.cpp
 * 2022-06-01 K.OHWADA
 */

// logging
// reference : https://codezine.jp/article/detail/1901?p=2

#include "Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/Message.h"

/**
 * main
 */
int main(int argc, char** argv)
{
  Poco::Logger& consoleLogger = Poco::Logger::create( "ConsoleLogger",
                                new Poco::ConsoleChannel, Poco::Message::PRIO_INFORMATION );

    consoleLogger.error( "Error" );

	return 0;
}
