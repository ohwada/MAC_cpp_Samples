/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */


#include<string>
#include <SFML/Network.hpp>


// prototype
std::string getStrStatus(sf::Socket::Status status);
void printStatus(sf::Socket::Status status);


/**
 * getStrStatus
 */
std::string getStrStatus(sf::Socket::Status status)
{
    std::string str = "unkown status";
    switch(status)
    {
        case sf::Socket::Done:
            str = "The socket has sent / received the data.";
            break;
       case sf::Socket::Partial :
            str = "The socket sent a part of the data.";
            break;
        case sf::Socket::NotReady  :
            str = "The socket is not ready to send";
            break;
        case sf::Socket::Disconnected :
            str = "The TCP socket has been disconnected";
            break;
        case sf::Socket::Error :
            str = "An unexpected error happened";
            break;
    }
    return str;
}


/**
 * printStatus
 */
void printStatus(sf::Socket::Status status)
{
    std::cout << getStrStatus(status) << std::endl;
}