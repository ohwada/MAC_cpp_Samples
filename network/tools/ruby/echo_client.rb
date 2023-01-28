## 2022-10-01 K.OHWADA
# echo_client.rb
# Messages to be sent and received 
# are separated by newline code

# https://ruby-doc.org/stdlib-2.1.0/libdoc/socket/rdoc/Socket.html

require 'socket'

PORT = 2000

sock = TCPSocket.new 'localhost', PORT

SEND_FLAGS = 0
RECV_LENGTH = 100
SLEEP = 1 # 1 sec

for num in 1..10 do
     msg = sprintf("%03d", num)
    sock.send(msg, SEND_FLAGS)
    if line = sock.recv(RECV_LENGTH)
        printf("r: %s \n", line)
    end
    sleep(SLEEP)
end
printf("close socket \n")
sock.close

