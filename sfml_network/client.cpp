/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

// send the input data to the server
// and display the received data
// reference : https://www.sfml-dev.org/tutorials/2.5/network-socket.php

// TODO: quit with ESC key

#include<iostream>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include "sfml_status.hpp"
#include "host.h"

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

    const sf::IpAddress IPADDR = sf::IpAddress::LocalHost;
    const string STR_IPADDR  = IPADDR.toString();

    sf::Socket::Status status;

    sf::TcpSocket socket;

    // connect server
    status = socket.connect(IPADDR , PORT);
    if (status != sf::Socket::Done)
    {
        cout << "connect Faild: " << STR_IPADDR << " : "<< PORT << endl;
        printStatus(status);
        return  EXIT_FAILURE;
    }

    cout << "connect: " << STR_IPADDR << " : "<< PORT << endl;

  
    sf::Packet packet_send;
    sf::Packet packet_recv;
    string line;
    string str_recv;

    while(1)
    {
       cout << endl;
        cout << "please enter the alphabets" << endl;
        cout << ">"; // prompt

        // input from keyboard
        getline(cin, line);

    // qiut when only return key
    // TODO: quit with ESC key
        if(line.empty()){
            break;
        }

        packet_send.clear();
        packet_send << line;

        // send packet
        status = socket.send(packet_send);
        if (status != sf::Socket::Done)
        {
            cout << "send Faild: "<< endl;
            printStatus(status);
            break;
        }

        cout << "send: " << line  << endl;

        // recieve packet
        status = socket.receive(packet_recv);
        if (status != sf::Socket::Done)
        {
            cout << "receive Faild: "<< endl;
            printStatus(status);
            break;
        }

        if (packet_recv >> str_recv)
        {
            cout << "recv: " << str_recv << endl;
        }else {
            cout << "error: cannot read packet " << endl;
            break;
        }

    } // while

    cout << "quit"<< endl;

    return EXIT_SUCCESS;
}
