#include "connection.h"

#include <boost/bind.hpp>
#include <iostream>

Connection::Connection(io_context &context,
                       const std::shared_ptr<session_creator> &creator,
                       const ip::tcp::endpoint &ep)
    : session_creator_(creator), acceptor_(context), sock_(context),
      context_(context) {
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

void Connection::run() {
  acceptor_.async_accept(
      sock_, boost::bind(&Connection::on_accept, shared_from_this(), _1));
}

void Connection::on_accept(const boost::system::error_code &ec) {
  if (ec) {
    fail(ec, "accept");
    return;
  }
  session_creator_->create_session()->run(sock_);

  sock_ = ip::tcp::socket(context_);
  acceptor_.async_accept(
      sock_, boost::bind(&Connection::on_accept, shared_from_this(), _1));
}

void Connection::fail(const boost::system::error_code &ec,
                      const std::string &desc) {
  std::cerr << "error code: " << ec.message() << " description: " << desc
            << std::endl;
}
