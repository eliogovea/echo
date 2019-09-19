#include <iostream>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>

#include "tcp_echo/server.hpp"
#include "tcp_echo/utils.hpp"


int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "argc != 2" << std::endl;
    std::cout << "usage: ./app port" << std::endl;
    return -1;
  }

  boost::asio::io_service ios;

  const auto port = utils::to_integer<uint16_t>(std::string(argv[1]));
  tcp_echo::server srv{ios, port};
  srv.start();
}
