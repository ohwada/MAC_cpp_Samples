/**
 *  generic.cpp
 * 2022-06-01 K.OHWADA
 */

//  generic implementation
// https://qiita.com/kurun_pan/items/f2edd3b834dcaeaa8b2f
#include <iostream>
#include <memory>


/**
 * class MessegeHandler
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

using MessegeHandlerImpleOnSuccess = std::function<void(void)>;
using MessegeHandlerImpleError = std::function<void(const std::string& message)>;


/**
 * class MessegeHandlerImple
 */
class MessegeHandlerImple : public MessegeHandler {
 public:
  MessegeHandlerImple(MessegeHandlerImpleOnSuccess on_success,
                      MessegeHandlerImpleError on_error)
      : on_success_(on_success), on_error_(on_error) {}
  virtual ~MessegeHandlerImple() = default;

 protected:
  void onSuccessInternal() override {
    if (on_success_)
      on_success_();
  }

  void onErrorInternal(const std::string& message) override {
    if (on_error_)
      on_error_(message);
  }

 private:
  MessegeHandlerImpleOnSuccess on_success_;
  MessegeHandlerImpleError on_error_;
};


/**
 * class Messenger
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
  auto handler = std::make_unique<MessegeHandlerImple>(
    []() {
      std::cout << "call OnCuccess()" << std::endl;
    },
    [](const std::string& message) {
      std::cout << "call OnError(): " << message << std::endl;
    }
  );

  messenger->setHandler(std::move(handler));

  messenger->sendMessage("Send message");
  messenger->sendMessage("");

  return 0;
}
