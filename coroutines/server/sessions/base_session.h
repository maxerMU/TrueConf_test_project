#ifndef BASE_SESSION_H
#define BASE_SESSION_H

#include <iostream>
#include <memory>

#include "net.h"

using namespace boost::asio;

class BaseSession {
public:
  BaseSession() = default;
  virtual ~BaseSession() = default;

  virtual std::future<void> run(tcp::socket sock) = 0;
  void fail(const error_code &ec, const std::string &desc) {
    std::cerr << "error code: " << ec.message() << " description: " << desc
              << std::endl;
  }

protected:
  std::shared_ptr<tcp::socket> sock_;
};

class SessionCreator {
public:
  SessionCreator() = default;
  virtual ~SessionCreator() = default;

  virtual std::shared_ptr<BaseSession> create_session() = 0;
};

#endif // BASE_SESSION_H
