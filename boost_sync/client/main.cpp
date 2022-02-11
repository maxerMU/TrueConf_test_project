#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
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

void echo_sync(std::string msg) {
  msg += '\n';

  using namespace boost::asio;
  io_service service;
  ip::tcp::socket sock(service);
  ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);
  sock.connect(ep);

  sock.write_some(buffer(msg));

  char buf[BUF_LEN];
  int bytes = read(sock, buffer(buf), boost::bind(read_complete, buf, _1, _2));

  std::string ans(buf, bytes - 1);
  std::cout << "answer: " << ans << std::endl;

  sock.close();
}

int main(int argc, char *argv[]) {
  std::string msg;
  std::cin >> msg;
  echo_sync(msg);

  return 0;
}
