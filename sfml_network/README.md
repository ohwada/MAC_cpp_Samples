sfml network
===============

sfml sample <br/>
tcp server and client <br/>


## install sfml
% brew install sfml <br/>
https://formulae.brew.sh/formula/sfml <br/>

## server.cpp
start the server <br/>
wait for connection from client <br/>

build code  <br/>  <br/>
% g++ server.cpp -o server  `pkg-config --cflags --libs sfml-network`  <br/>

run code <br/>
% ./server <br/>

display as below <br/>
waiting for connection port: 9876 <br/>
please run client program <br/>
or quit with ctrl-c <br/>

## client.cpp
connect to the server <br/>
send and receive data <br/>

build code  <br/>
% g++ client.cpp -o client  `pkg-config --cflags --libs sfml-network`  <br/>

run code  <br/>
% ./client <br/>

display as below <br/>
connect: 127.0.0.1 : 9876 <br/>
please enter the alphabets <br/>
\> <br/>


### Reference <br/>
- https://riptutorial.com/sfml
- https://www.sfml-dev.org/tutorials/2.5/network-socket.php

