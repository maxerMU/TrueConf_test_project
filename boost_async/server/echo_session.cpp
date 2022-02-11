#include "echo_session.h"
#include <boost/bind.hpp>

size_t echo_session::read_complete(char *buf,
                                   const boost::system::error_code &err,
                                   size_t bytes) {
  if (err)
    return 0;

  if (std::find(buf, buf + bytes, '\n') < buf + bytes)
    return 0;

  return 1;
}

void echo_session::run(boost::asio::ip::tcp::socket &sock) {
  sock_ptr = std::make_shared<ip::tcp::socket>(std::move(sock));

  do_read();
}

void echo_session::do_read() {
  async_read(*sock_ptr, buffer(read_buffer),
             boost::bind(&echo_session::read_complete, shared_from_this(),
                         read_buffer, _1, _2),
             boost::bind(&echo_session::on_read, shared_from_this(), _1, _2));
}

void echo_session::on_read(const boost::system::error_code &ec, size_t bytes) {
  if (ec) {
    fail(ec, "read");
    return;
  }

  std::string msg(read_buffer, bytes - 1);
  std::cout << "Server get message: " << msg << std::endl;

  do_write(msg);
}

void echo_session::do_write(const std::string &msg) {
  std::copy(msg.cbegin(), msg.cend(), write_buffer);
  std::cout << "Prepare msg:" << write_buffer << std::endl;

  sock_ptr->async_write_some(
      buffer(write_buffer),
      boost::bind(&echo_session::on_write, shared_from_this(), _1, _2));
}

void echo_session::on_write(const boost::system::error_code &ec, size_t bytes) {
  if (ec) {
    fail(ec, "write");
    return;
  }

  sock_ptr->close();
}
