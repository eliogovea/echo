project(echo_tcp)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS          "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG    "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3")

find_package(Threads)

add_executable(server
  src/main.cpp
  src/server.cpp
)

target_link_libraries(server
  pthread 
  boost_system
)
