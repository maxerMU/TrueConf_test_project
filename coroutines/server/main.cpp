#include "connection.h"
#include "echo_session.h"
#include <boost/asio.hpp>
#include <memory>

using namespace boost::asio;
int main(int argc, char *argv[]) {
  io_context ioc;
  ip::tcp::endpoint ep(ip::address_v4(), 8001); // TODO

  std::shared_ptr<SessionCreator> creator(new EchoSessionCreator());

  std::shared_ptr<ServerConnection> con(new ServerConnection(ioc, creator, ep));
  con->run();

  signal_set signals(ioc, SIGINT, SIGTERM);
  signals.async_wait([&ioc](boost::system::error_code const &, int) {
    // Stop the io_context. This will cause run()
    // to return immediately, eventually destroying the
    // io_context and any remaining handlers in it.
    ioc.stop();
  });

  ioc.run();

  return 0;
}
