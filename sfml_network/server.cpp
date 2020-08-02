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
#include "string_upper.hpp"


using namespace std;

// prototype
int procPacket(sf::TcpSocket* socket);

// global
const int CODE_DONE = 0;
const int CODE_DISCONNECTED = 1;
const int CODE_ERROR = 2;


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

while(1)
{
    // you can connect from the client as many times as you want 
    cout << endl;
    cout << "please run client program" << endl;

// TODO: quit with ESC key
    cout << "or quit with ctrl-c" << endl;

    // accept a new connection
    sf::TcpSocket socket;
    status = listener.accept(socket) ;
    if(status != sf::Socket::Done)
    {
        cout << "accept failed" << endl;
        printStatus(status);
        return  EXIT_FAILURE;
    }

    // connected
    sf::IpAddress client_addr = socket.getRemoteAddress ();
 
    unsigned short client_port = 	socket.getRemotePort ();
 
    cout << "connected from: " <<  client_addr << " : " <<  client_port << endl;

        int ret = procPacket(&socket);
        if (ret == CODE_DISCONNECTED) {
                continue;
        } else if (ret == CODE_ERROR) {
                return  EXIT_FAILURE;
        }

    } // while

    return EXIT_SUCCESS;
}


/**
 * procPacket
 *  Note:
 *  copy constructor of 'Socket' is implicitly deleted 
 * because base class 'sf::NonCopyable' has an inaccessible copy
 */
int procPacket(sf::TcpSocket* socket)
{

    sf::Socket::Status status;
    sf::Packet packet_recv;
    sf::Packet packet_send;
    string str_recv;
    string str_send;
    int ret = CODE_DONE;

    while(1)
    {
        // recieve packet
        status = (*socket).receive(packet_recv);
        if (status == sf::Socket::Disconnected) {
            printStatus(status);
            ret = CODE_DISCONNECTED;
            break;
        } else if (status != sf::Socket::Done) {
            printStatus(status);
            ret = CODE_ERROR;
            break;
        }

        if (packet_recv >> str_recv)
        {
            cout << "recv: " << str_recv << endl;
        } else {
            cout << "error: cannot read packet " << endl;
            ret = CODE_ERROR;
            break;
        }


        // create send data
        str_send = str2upper(str_recv);

        packet_send.clear();
        packet_send << str_send;


        // send packet
        status = (*socket).send(packet_send);
        if (status != sf::Socket::Done)
        {
            cout << "send Faild: "<< endl;
            printStatus(status);
            ret = CODE_ERROR;
            break;
        }

        cout << "send: " << str_send << endl;
        cout << endl;

    } // while

    return ret;
}
