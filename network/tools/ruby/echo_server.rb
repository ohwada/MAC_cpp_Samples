## 2022-10-01 K.OHWADA
# echo_server.rb
# Messages to be sent and received 
# are separated by newline code

# https://ruby-doc.org/stdlib-2.1.0/libdoc/socket/rdoc/Socket.html


require 'socket'

PORT = 2000

server = TCPServer.new PORT

printf("listen: %d \n", PORT)

RECV_LENGTH = 100
SEND_FLAGS = 0
SLEEP = 5 # 5 sec
LIMIT_NO_RECV = 10

cnt_no_recv = 0

loop do
    client = server.accept
    addr = client.getpeername
    printf("client: ");
    p Socket.unpack_sockaddr_in(addr)
  while buffer = client.recv(RECV_LENGTH)
        if (buffer.empty?)
# assume that the communication has ended.
# close the socket
# if nothing is received for a certain period of time
            sleep(SLEEP)
            cnt_no_recv += 1
            # printf("  cnt_no_recv: %d \n",   cnt_no_recv)
            if (cnt_no_recv > LIMIT_NO_RECV)
                printf("no recv data \n")
                break
            end # if
        else
            cnt_no_recv += 0
            printf("r: %s \n", buffer.strip)
# echo back
            client.send(buffer, SEND_FLAGS)
        end # if
  end  # while
    printf("close socket \n")
    client.close
    printf("wait new client \n")
end  # loop

