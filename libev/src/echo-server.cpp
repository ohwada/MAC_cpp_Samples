// https://qiita.com/janus_wel/items/51bbd7517ab237a0b65c

/*
 * echo-server.cpp
 *  echo server with libev
 *
 *      g++ -std=c++11 -Wall -Wextra -pedantic -lev timer.cpp
 *
 *      telnet localhost 40713
 *
 *  written by janus_wel<janus.wel.3@gmail.com>
 *
 *  These codes are licensed under the MIT license
 *      http://opensource.org/licenses/MIT
 * */

#include <ev++.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>


/**
 * constant
 */
constexpr unsigned int BUFFER_SIZE = 4096;
constexpr unsigned short int SERVER_PORT = 40713;
constexpr int NUMOF_BACKLOG = 16;
constexpr int PROTOCOL = 0;

template<typename T> constexpr inline T pointer_cast(void* const p) noexcept {
    return static_cast<T>(p);
}
template<typename T> constexpr inline T pointer_cast(const void* const p) noexcept {
    return static_cast<T>(p);
}


/**
 * socket_t
 */
class socket_t {
    private:
        const sa_family_t family_;
        const int socket_;

    private:
        static constexpr int ERROR_CODE = -1;

    public:
        socket_t(const sa_family_t family, const int type, const int protocol)
            : family_(family),
            socket_(socket(family, type, protocol)) {
            if (socket_ == socket_t::ERROR_CODE) {
                throw std::runtime_error(strerror(errno));
            }
        }

        ~socket_t() noexcept {
            close(socket_);
        }

        inline int raw() const noexcept {
            return socket_;
        }
        inline operator int() const noexcept {
            return this->raw();
        }

        void bind(const uint16_t port) {
            sockaddr_in socket_address;
            socket_address.sin_family = family_;
            socket_address.sin_addr.s_addr = INADDR_ANY;
            socket_address.sin_port = htons(port);
            std::cout << "listen: " << port << std::endl;

            const auto result = ::bind(
                    socket_,
                    pointer_cast<sockaddr*>(&socket_address),
                    sizeof(socket_address));

            if (result == socket_t::ERROR_CODE) {
                throw std::runtime_error(strerror(errno));
            }
        }

        void listen(const int backlog) {
            const auto result = ::listen(socket_, backlog);
            if (result == socket_t::ERROR_CODE) {
                throw std::runtime_error(strerror(errno));
            }
        }
};


/**
 * class connection_t
 */
class connection_t;

typedef std::map<int, std::unique_ptr<connection_t>> connections_t;
connections_t connections;

class connection_t {
    private:
        unsigned int id_;
        int descriptor_;

        std::array<char, BUFFER_SIZE> buffer;
        ev::io read_watcher;
        ev::io write_watcher;

        ssize_t received_bytes;

    public:
        connection_t(const unsigned int id, const int descriptor)
            : id_(id), descriptor_(descriptor) {
            read_watcher.set<connection_t, &connection_t::read>(this);
            read_watcher.set(descriptor, ev::READ);

            write_watcher.set<connection_t, &connection_t::write>(this);
            write_watcher.set(descriptor, ev::WRITE);
        }

        void start() noexcept {
            read_watcher.start();
        }

        void close() noexcept {
            ::close(this->descriptor_);
            connections.erase(connections.find(this->id_));

            std::cout
                << connections.size() << " connections active"
                << std::endl;
        }

        void read(ev::io& w, int) {
            std::cout
                << "read()"
                << std::endl;

            ssize_t result = recv(w.fd, buffer.data(), buffer.size(), 0);

            std::cout
                << std::setw(4) << " " << result << " bytes received"
                << std::endl;

            if (result == -1) {
                if (errno == EAGAIN) {
                    return;
                }
                throw std::runtime_error(strerror(errno));
            }

            if (result == 0) {
                std::cout
                    << std::setw(4) << " " << "disconnected by peer"
                    << std::endl;

                w.stop();
                this->close();

                return;
            }

            received_bytes += result;
            //w.stop();
            write_watcher.start();
        }

        void write(ev::io& w, int) {
            std::cout
                << "write()"
                << std::endl;

            ssize_t sent_bytes = 0;
            while (sent_bytes < received_bytes) {
                ssize_t result = send(
                        w.fd,
                        &buffer[sent_bytes],
                        received_bytes - sent_bytes,
                        0);

                std::cout
                    << std::setw(4) << " " << result << " bytes sent"
                    << std::endl;

                if (result == -1) {
                    if (errno == EAGAIN) {
                        return;
                    }
                    throw std::runtime_error(strerror(errno));
                }

                sent_bytes += result;
            }

            received_bytes = 0;
            w.stop();

            //this->close();
        }
};


/**
 * class host_t 
 */
class host_t {
    private:
        std::string hostname_;
        std::string ip_address_;

    private:
        static constexpr int SUCCESS_CODE = 0;

    public:
        const char* hostname() const noexcept {
            return hostname_.c_str();
        }
        const char* ip_address() const noexcept {
            return ip_address_.c_str();
        }

    public:
        explicit host_t(const char* hostname, const sa_family_t family) {
            addrinfo* address_info;
            addrinfo hints;
            hints.ai_family = family;

            const auto result = getaddrinfo(hostname, nullptr, &hints, &address_info);
            if (result != host_t::SUCCESS_CODE) {
                throw std::runtime_error(gai_strerror(result));
            }

            hostname_ = address_info->ai_canonname;
            ip_address_ = inet_ntoa(pointer_cast<sockaddr_in*>(address_info->ai_addr)->sin_addr);

            freeaddrinfo(address_info);
        }

        explicit host_t(const sockaddr_in& socket_address) {
            std::array<char, NI_MAXHOST> buffer;

            const auto result = getnameinfo(
                    pointer_cast<const sockaddr*>(&socket_address), sizeof(socket_address),
                    buffer.data(), buffer.size(),
                    nullptr, 0,
                    NI_NAMEREQD);
            if (result != host_t::SUCCESS_CODE) {
                throw std::runtime_error(gai_strerror(result));
            }

            hostname_ = buffer.data();
            ip_address_ = inet_ntoa(socket_address.sin_addr);
        }
};


/**
class callback_t
 */
class callback_t {
    private:
        unsigned int count_;

    public:
        callback_t() : count_(0) { }

        void operator() (ev::io& w, int) {
            sockaddr_in peer_socket_address;
            socklen_t peer_socket_address_length = sizeof(peer_socket_address);
            const auto descriptor = accept(
                    w.fd,
                    pointer_cast<sockaddr*>(&peer_socket_address),
                    &peer_socket_address_length);
            if (descriptor == -1) {
                throw std::runtime_error(strerror(errno));
            }

            host_t host(peer_socket_address);
            std::cout
                << host.hostname() << " " << host.ip_address()
                << std::endl;

            const auto id = ++count_;
            connections[id] = connections_t::mapped_type(new connection_t(id, descriptor));;

            connections[id]->start();

            std::cout
                << connections.size() << " connections active"
                << std::endl;
        }
};


/**
 * main
 */
int main(const int, const char* const []) {
    socket_t socket(AF_INET, SOCK_STREAM, PROTOCOL);
    socket.bind(SERVER_PORT);
    socket.listen(NUMOF_BACKLOG);

    ev::default_loop loop;
    ev::io watcher(loop);
    callback_t callback;
    watcher.set(&callback);
    watcher.set(socket, ev::READ);
    watcher.start();

    loop.run(0);

    return 0;
}
