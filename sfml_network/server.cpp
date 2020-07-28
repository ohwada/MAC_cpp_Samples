/**
 * sfml sample
 * 2020-03-01 K.OHWADA
 */

 // convert the string sent from the client to uppercase
//  and send it back
// rference : https://www.sfml-dev.org/tutorials/2.5/network-socket.php

// TODO: quit with ESC key

#include<iostream>
#include <algorithm>
#include <cctype>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include "sfml_status.hpp"
#include "host.h"

using namespace std;


/**
 * toUpper
 */
char toUpper(char c) {
    char ret;
    if(isalpha(c)) {
        ret = toupper(c);
    } else {
        ret = c;
    }
    return ret;
}



/**
 * main
 */
int main(int argc, char **argv)
{

    sf::Socket::Status status;
    sf::TcpListener listener;

    // bind the listener to a port
    status = listener.listen(PORT);
    if (status != sf::Socket::Done)
    {
        cout << "listen faild: " << PORT << endl;
        printStatus(status);
        return  EXIT_FAILURE;
    }

  
   // wait connet
    cout << "waiting for connection port: " << PORT << endl;

    sf::IpAddress clientAddress;
    sf::TcpSocket client;

while(1)
{
    // you can connect from the client as many times as you want 
    cout << endl;
    cout << "please run client program" << endl;

// TODO: quit with ESC key
    cout << "or quit with ctrl-c" << endl;

    // accept a new connection
    status = listener.accept(client) ;
    if(status != sf::Socket::Done)
    {
        cout << "accept failed" << endl;
        printStatus(status);
        return  EXIT_FAILURE;
    }

    // connected
    sf::IpAddress client_addr = client.getRemoteAddress ();
 
    unsigned short client_port = 	client.getRemotePort ();
 
    cout << "connected from: " <<  client_addr << " : " <<  client_port << endl;

    sf::Packet packet_recv;
    sf::Packet packet_send;
    string str_recv;
    string str_send;

    while(1)
    {
        // recieve packet
        status = client.receive(packet_recv);
        if (status == sf::Socket::Disconnected) {
            printStatus(status);
            break;
        } else if (status != sf::Socket::Done) {
            printStatus(status);
            return  EXIT_FAILURE;
        }

        if (packet_recv >> str_recv)
        {
            cout << "recv: " << str_recv << endl;
        } else {
            cout << "error: cannot read packet " << endl;
            return  EXIT_FAILURE;
        }

        str_send.resize(str_recv.size());

        // toUpper
        std::transform(str_recv.begin(), str_recv.end(), str_send.begin(), toUpper );

        packet_send.clear();
        packet_send << str_send;

        // send packet
        status = client.send(packet_send);
        if (status != sf::Socket::Done)
        {
            cout << "send Faild: "<< endl;
            printStatus(status);
            return  EXIT_FAILURE;
        }

        cout << "send: " << str_send << endl;
        cout << endl;

    } // while

    } // while

    return EXIT_SUCCESS;
}
