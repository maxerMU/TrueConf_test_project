#ifndef BASE_SESSION_H
#define BASE_SESSION_H

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

using namespace boost::asio;

class base_session {
public:
  base_session() = default;
  virtual ~base_session() = default;

  virtual void run(ip::tcp::socket &sock) = 0;
  void fail(const boost::system::error_code &ec, const std::string &desc) {
    std::cerr << "error code: " << ec.message() << " description: " << desc
              << std::endl;
  }

protected:
  std::shared_ptr<ip::tcp::socket> sock_ptr;
};

class session_creator {
public:
  session_creator() = default;
  virtual ~session_creator() = default;

  virtual std::shared_ptr<base_session> create_session() = 0;
};

#endif // BASE_SESSION_H
