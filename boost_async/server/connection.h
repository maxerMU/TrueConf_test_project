#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>

#include "base_session.h"

using namespace boost::asio;
class Connection : public std::enable_shared_from_this<Connection> {
public:
  Connection(io_context &context,
             const std::shared_ptr<session_creator> &creator,
             const ip::tcp::endpoint &ep);

  void run();
  void fail(const boost::system::error_code &ec, const std::string &desc);

  void on_accept(const boost::system::error_code &ec);

private:
  std::shared_ptr<session_creator> session_creator_;
  ip::tcp::acceptor acceptor_;
  ip::tcp::socket sock_;
  io_context &context_;
};
