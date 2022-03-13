#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>

#include "base_session.h"

using namespace boost::asio;
class ServerConnection : public std::enable_shared_from_this<ServerConnection> {
public:
  ServerConnection(io_context &context,
                   const std::shared_ptr<SessionCreator> &creator,
                   const ip::tcp::endpoint &ep);

  void run();
  void fail(const boost::system::error_code &ec, const std::string &desc);

private:
  std::shared_ptr<SessionCreator> session_creator_;
  ip::tcp::acceptor acceptor_;
  io_context &context_;
};
