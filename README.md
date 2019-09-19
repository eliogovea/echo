# Echo
Just learning how to use boost.asio with for a simple TCP echo server.

---

## Server

### Build (linux)
* cd server
* mkdir build
* cd build
* cmake ..
* make

### Run
* ./server port

### **TODO**
- [] multithread
- [] async read

---

## Client
Simple utility written in C++ using boost.asio  for sending a message to a tcp server and wait for a response (until "\n").

### Build
* cd client
* make

### Run
* ./client ip port message