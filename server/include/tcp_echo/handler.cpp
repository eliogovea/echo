#include <memory>

#include <boost/asio.hpp>

// interface
class connection_handler {
  public:
    virtual void handle(std::shared_ptr<socket_type> socket, boost::system::error_code& ec) = 0;
};

//
class echo : connection_handler {
  void handle(std::shared_ptr<socket_type> socket, boost::system::error_code& ec);
}

void echo::handle(std::shared_ptr<socket_type> socket, boost::system::error_code& ec) {
 // 
}
