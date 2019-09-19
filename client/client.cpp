#include <iostream>
#include <string>

#include <boost/asio.hpp>

template <typename T>
T to_int(const std::string& s) {
  const T base{10};
  T result{0};
  for (auto c : s) {
    result = base * result + static_cast<T>(c - '0');
  }
  return result;
}

void check_error(boost::system::error_code ec) {
  if (!ec) {
    return;
  }
  std::cout << ec.message() << std::endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "invalid number of arguments\n";
    std::cout << "usage: ./client ip port message\n";
    std::cout << std::endl;
    return -1;
  }

  boost::asio::io_service ios;
  
  const std::string ip{argv[1]};
  const auto port{to_int<uint16_t>(argv[2])};
  const std::string request{argv[3]};
  
  
  boost::asio::ip::tcp::endpoint endpoint{boost::asio::ip::address::from_string(ip), port};

  boost::asio::ip::tcp::socket socket(ios);
  
  boost::system::error_code ec;
  socket.open(endpoint.protocol(), ec);

  check_error(ec);

  socket.connect(endpoint, ec);

  check_error(ec);

  std::cout << "sending request ..." << std::endl;
  boost::asio::write(socket, boost::asio::buffer(request + "\n"), ec);

  check_error(ec);

  std::cout << "waiting for response ..." << std::endl;
  boost::asio::streambuf buf;
  boost::asio::read_until(socket, buf, '\n');

  check_error(ec);

  std::istream input{&buf};
  std::string response;
  std::getline(input, response);

  std::cout << "response: " << response << std::endl;
}
