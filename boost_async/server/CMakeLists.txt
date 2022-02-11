cmake_minimum_required(VERSION 3.5)

project(boost_async_server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system thread REQUIRED)

add_executable(boost_async_server
  main.cpp
  connection.cpp
  echo_session.cpp
)

target_link_libraries(boost_async_server Boost::system Boost::thread)
