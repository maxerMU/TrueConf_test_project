#include "connection.h"

#include "echo_session.h"
#include <boost/bind.hpp>
#include <iostream>

ServerConnection::ServerConnection(
    io_context &context, const std::shared_ptr<SessionCreator> &creator,
    const ip::tcp::endpoint &ep)
    : session_creator_(creator), acceptor_(context), context_(context) {
  boost::system::error_code ec;

  acceptor_.open(ep.protocol(), ec);
  if (ec) {
    fail(ec, "open acceptor");
    return;
  }

  acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
  if (ec) {
    fail(ec, "set option");
    return;
  }

  acceptor_.bind(ep, ec);
  if (ec) {
    fail(ec, "bind");
    return;
  }

  acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
  if (ec) {
    fail(ec, "listen");
    return;
  }
}

void ServerConnection::run() {
  acceptor_.async_accept([this](error_code ec, tcp::socket sock) {
    if (ec) {
      fail(ec, "accept");
      return;
    }
    session_creator_->create_session()->run(std::move(sock));

    run();
  });
}

void ServerConnection::fail(const boost::system::error_code &ec,
                            const std::string &desc) {
  std::cerr << "error code: " << ec.message() << " description: " << desc
            << std::endl;
}
