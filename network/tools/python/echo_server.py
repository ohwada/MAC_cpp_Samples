## 2022-10-01 K.OHWADA
# Echo server program
# https://docs.python.org/ja/3.6/library/socket.html#example

import socket

# Symbolic name meaning all available interfaces
HOST = "localhost"
# Arbitrary non-privileged port                 
PORT = 50007

RECV_MAX_LEN = 1024
LISTEN_BACKLOG = 1

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.bind((HOST, PORT))
    sock.listen(LISTEN_BACKLOG)
    print("listen: ", PORT)

    conn, addr = sock.accept()
    with conn:
        print('Connected by', addr)
        while True:
            rcv_data = conn.recv(RECV_MAX_LEN)
            data = rcv_data.decode().rstrip()
            print( "r: ", data)
            if not rcv_data: break
            conn.sendall(rcv_data)
print('close')
