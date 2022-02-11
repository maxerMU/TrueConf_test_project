#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <string>

#define BUF_LEN 1024

size_t read_complete(char *buf, const boost::system::error_code &err,
                     size_t bytes) {
  if (err)
    return 0;

  if (std::find(buf, buf + bytes, '\n') < buf + bytes)
    return 0;

  return 1;
}

void handle_connections() {
  using namespace boost::asio;
  io_service service;
  ip::tcp::acceptor acceptor(service,
                             ip::tcp::endpoint(ip::address_v4(), 8001));
  char buf[BUF_LEN];

  while (true) {
    ip::tcp::socket sock(service);
    acceptor.accept(sock);
    int bytes =
        read(sock, buffer(buf), boost::bind(read_complete, buf, _1, _2));

    std::string msg(buf, bytes);
    sock.write_some(buffer(msg));
    sock.close();
  }
}

int main(int argc, char *argv[]) {
  handle_connections();
  return 0;
}
