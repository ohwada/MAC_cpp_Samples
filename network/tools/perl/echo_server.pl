#!/usr/local/bin/perl -w
## 2022-10-01 K.OHWADA

# echo_server.pl
# Messages to be sent and received 
# are separated by newline code
# http://x68000.q-e-d.net/~68user/net/echo-2.html

# $Id: echo-server.pl,v 1.2 2002/02/17 11:07:27 68user Exp $


# remove the trailing newline code
sub rtrim {
	my $val = shift;
	$val =~ s/\s*$//;
	return $val;
}

use Socket;

my $port = 5000;

# genarate socket
socket(CLIENT_WAITING, PF_INET, SOCK_STREAM, 0)
     or die "cannot generate socket $!";

# Socket option setting
setsockopt(CLIENT_WAITING, SOL_SOCKET, SO_REUSEADDR, 1)
     or die "setsockopt failed $!";

# assign an address (name) to socket
bind(CLIENT_WAITING, pack_sockaddr_in($port, INADDR_ANY))
     or die "bind failed $!";

# listen port
listen(CLIENT_WAITING, SOMAXCONN)
     or die "listen: $!";

print "listen $port \n";

# by using while(1), prepare for the next connection even if one connection ends
while (1){
    $paddr = accept(CLIENT, CLIENT_WAITING);

# get host name, IP address and client port number
    ($client_port, $client_iaddr) = unpack_sockaddr_in($paddr);

    $client_hostname = gethostbyaddr($client_iaddr, AF_INET);

    $client_ip = inet_ntoa($client_iaddr);

    print "connect: $client_hostname ($client_ip) port $client_port\n";


# don't buffer for clients
# https://perlzemi.com/blog/20080812121854.html
    select(CLIENT); $|=1; select(STDOUT);

    while (my $rcv_data = <CLIENT>){
        my $data = rtrim($rcv_data);
        print "r: $data \n";
#send back a message to the client
        print CLIENT $rcv_data;
    } # while
    close(CLIENT);

    print "Connection lost. Still watching port $port. \n";
}
 # while ---

