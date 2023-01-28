## 2022-10-01 K.OHWADA
# Echo client program
# https://docs.python.org/ja/3.6/library/socket.html#example

import socket
import time

HOST = 'localhost'    # The remote host
PORT = 50007              # The same port as used by the server

RECV_MAX_LEN = 1024
FOR_RANGE = 10
SLEEP = 1 # 1 sec
FORMAT="{:03d}"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))
    for i in range(FOR_RANGE):
        msg=FORMAT.format(i)
        sock.sendall( msg.encode() )
        rcv_data = sock.recv(RECV_MAX_LEN)
        data = rcv_data.decode()
        print('r: ', data )
        time.sleep(SLEEP)
print('close')
