#ifndef ECHO_SESSION_H
#define ECHO_SESSION_H

#include "base_session.h"
#include <boost/system/error_code.hpp>

#include "net.h"

class EchoSession : public BaseSession,
                    public std::enable_shared_from_this<EchoSession> {
public:
  EchoSession() = default;

  virtual std::future<void> run(tcp::socket sock) override;

private:
  size_t iterations_left = 3; // TODO
};

class EchoSessionCreator : public SessionCreator {
public:
  EchoSessionCreator() = default;
  virtual ~EchoSessionCreator() = default;

  std::shared_ptr<BaseSession> create_session() override {
    return std::shared_ptr<BaseSession>(new EchoSession());
  }
};

#endif // ECHO_SESSION_H
