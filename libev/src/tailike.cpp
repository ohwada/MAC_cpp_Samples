// https://qiita.com/janus_wel/items/51bbd7517ab237a0b65c
/*
 * tailike.cpp
 *  tail -f with libev
 *
 *      g++ -std=c++11 -Wall -Wextra -pedantic -lev tailike.cpp
 *
 *  written by janus_wel<janus.wel.3@gmail.com>
 *
 *  These codes are licensed under the MIT license
 *      http://opensource.org/licenses/MIT
 * */

#include <fcntl.h>  // open
#include <string.h> // strerror
#include <unistd.h> // read

#include <ev++.h>

#include <array>
#include <iostream>
#include <stdexcept>
#include <string>

constexpr std::size_t BUFFER_SIZE = 4096;

class file_descriptor_t {
    private:
        int file_descriptor_;

    public:
        explicit file_descriptor_t(const char* const file_name)
            : file_descriptor_(open(file_name, O_RDONLY)) {
            if (file_descriptor_ == -1) {
                throw std::runtime_error(strerror(errno));
            }
        }
        explicit file_descriptor_t(const std::string& file_name)
            : file_descriptor_t(file_name.c_str()) { }

        ~file_descriptor_t() noexcept {
            close(file_descriptor_);
        }

        inline int raw() const noexcept {
            return file_descriptor_;
        }
        inline operator int() const noexcept {
            return this->raw();
        }
};

class callback_t {
    public:
        typedef std::array<char, BUFFER_SIZE> buffer_t;

    private:
        buffer_t buffer_;
        file_descriptor_t file_descriptor_;

    public:
        callback_t(const char* file_path)
            : file_descriptor_(file_path) { }

        void read(ev::stat& w, int) {
            if (!w.attr.st_nlink) {
                return;
            }

            const auto read_bytes = ::read(file_descriptor_, buffer_.data(), buffer_.size() - 1);
            if (read_bytes == -1) {
                // error occured when read
                return;
            }
            if (read_bytes == 0) {
                // fd is closed?
                return;
            }
            buffer_[read_bytes] = '\0';
            std::cout << buffer_.data() << std::flush;
        }
};

int main(const int argc, const char* const argv[]) {
    if (argc < 2) {
        std::cerr
            << "specify file to tail"
            << std::endl;
    }
    const char* const file_path = argv[1];

    try {
        callback_t callback(file_path);
        ev::default_loop loop;

        ev::stat watcher(loop);
        watcher.set<callback_t, &callback_t::read>(&callback);
        watcher.set(file_path, 0);
        watcher.start();

        loop.run(0);

        return 0;
    }
    catch (const std::runtime_error& e) {
        std::cerr
            << e.what()
            << std::endl;
        return 1;
    }
}
