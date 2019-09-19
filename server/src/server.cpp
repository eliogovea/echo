#include <iostream>
#include <thread>

#include "tcp_echo/server.hpp"

namespace tcp_echo {

void connection_handler::handle(std::shared_ptr<socket_type> socket, boost::system::error_code& ec) {
  std::cout << "start handling connection ..." << std::endl;

  std::cout << "reading request ..." << std::endl;
  boost::asio::streambuf buf;
  boost::asio::read_until(*socket.get(), buf, "\n");

  std::istream input{&buf};
  std::string request;
  std::getline(input, request);

  std::cout << "request: " << request << std::endl;

  std::cout << "sending response" << std::endl;
  boost::asio::write(*socket.get(), boost::asio::buffer(request + "\n")); // echo

  std::cout << "closing connection ..." << std::endl;
  socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);

  std::cout << "\n\n";
}

server::server(boost::asio::io_service& ios, const uint16_t port) : 
  ios_(ios), 
  endpoint_(boost::asio::ip::address_v4::any(), port), 
  acceptor_(ios_, endpoint_) 
{
  std::cout << "server ctor: " << port << std::endl;
}

server::~server() {
  std::cout << "server dtor" << std::endl;
  stop();
}

void server::start() {
  std::cout << "starting server ..." << std::endl;
  main_loop_thread_.reset(new std::thread([this]() {run();}));
}

void server::run() {
  std::cout << "start listening ..." << std::endl;
  acceptor_.listen();

  is_running.store(true);

  while (is_running.load()) {
    std::cout << "creating new socket ..." << std::endl;
    auto socket = std::make_shared<socket_type>(ios_);

    std::cout << "accepting connection ..." << std::endl; 
    acceptor_.accept(*socket.get());

    // TODO create a thread
    boost::system::error_code ec;
    handler_.handle(socket, ec);
  }

  std::cout << "finish listenning" << std::endl;
}

void server::stop() {
  std::cout << "stopping server ..." << std::endl;
  is_running.store(false);
  if (main_loop_thread_) {
    main_loop_thread_->join();
  }
}

}
