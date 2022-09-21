/**
 *  interface.cpp
 * 2022-06-01 K.OHWADA
 */


// describe processing in a class that inherits Interface Class
// https://qiita.com/kurun_pan/items/f2edd3b834dcaeaa8b2f
#include <iostream>
#include <memory>


/**
 *  class MessegeHandler
 *  interface class
 */
class MessegeHandler {
 public:
  MessegeHandler() = default;
  virtual ~MessegeHandler() = default;

  void onSuccess() {
    onSuccessInternal();
  }

  void onError(const std::string& message) {
    onErrorInternal(message);
  }

 protected:
  virtual void onSuccessInternal() = 0;
  virtual void onErrorInternal(const std::string& message) = 0;
};

class MessegeHandlerImple : public MessegeHandler {
 public:
  void onSuccessInternal() override {
      std::cout << "call OnCuccess()" << std::endl;
  }

  void onErrorInternal(const std::string& message) override {
      std::cout << "call OnError(): " << message << std::endl;
  }
};


/**
 *  class Messenger
 */
class Messenger {
 public:
  Messenger() = default;
  ~Messenger() = default;

  void setHandler(std::unique_ptr<MessegeHandler> handler) {
    handler_ = std::move(handler);
  }

  void sendMessage(const std::string& message) {
    if (message.size() == 0) {
      if (handler_)
        handler_->onError("error message");
      return ;
    }


    if (handler_)
      handler_->onSuccess();
  }

 private:
  std::unique_ptr<MessegeHandler> handler_;
};


/**
 *  main
 */
int main() {
  auto messenger = std::make_unique<Messenger>();
  auto handler = std::make_unique<MessegeHandlerImple>();

  messenger->setHandler(std::move(handler));

  messenger->sendMessage("Send message");
  messenger->sendMessage("");

  return 0;
}
