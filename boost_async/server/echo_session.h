#ifndef ECHO_SESSION_H
#define ECHO_SESSION_H

#include "base_session.h"
#include <boost/system/error_code.hpp>

using namespace boost::asio;

class echo_session : public base_session,
                     public std::enable_shared_from_this<echo_session> {
public:
  echo_session() = default;

  virtual void run(ip::tcp::socket &sock) override;

private:
  void do_read();
  size_t read_complete(char *buf, const boost::system::error_code &err,
                       size_t bytes);
  void on_read(const boost::system::error_code &ec, size_t bytes);

  void do_write(const std::string &msg);
  void on_write(const boost::system::error_code &ec, size_t bytes);

  char read_buffer[1024];
  char write_buffer[1024];
};

class echo_session_creator : public session_creator {
public:
  echo_session_creator() = default;
  virtual ~echo_session_creator() = default;

  std::shared_ptr<base_session> create_session() override {
    return std::shared_ptr<base_session>(new echo_session());
  }
};

#endif // ECHO_SESSION_H
