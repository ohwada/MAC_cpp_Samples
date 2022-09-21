/**
 *  messenger.cpp
 * 2022-06-01 K.OHWADA
 */

//  register callbacks with as many arguments as needed
// https://qiita.com/kurun_pan/items/f2edd3b834dcaeaa8b2f
#include <iostream>
#include <memory>

using MessengerOnSuccess = std::function<void(void)>;
using MessengerOnError = std::function<void(const std::string& message)>;


/**
 *  class Messenger
 */
class Messenger {
 public:
  Messenger() = default;
  ~Messenger() = default;

  void setHandler(MessengerOnSuccess on_success, MessengerOnError on_error) {
    on_success_ = on_success;
    on_error_ = on_error;
  }

  void sendMessage(const std::string& message) {
    if (message.size() == 0) {
      if (on_error_)
        on_error_("error message");
      return ;
    }


    if (on_success_)
      on_success_();
  }

 private:
  MessengerOnSuccess on_success_;
  MessengerOnError on_error_;
};


/**
 *  main
 */
int main() {
  auto messenger = std::make_unique<Messenger>();

  messenger->setHandler(
    []() {
      std::cout << "call OnCuccess()" << std::endl;
    },
    [](const std::string& message) {
      std::cout << "call OnError(): " << message << std::endl;
    }
  );

  messenger->sendMessage("Send message");
  messenger->sendMessage("");

  return 0;
}
