cmake_minimum_required(VERSION 3.12)

project(coroutine_server LANGUAGES CXX)


set(CMAKE_CXX_COMPILER g++-10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")

set(CMAKE_INCLUDE_PATH /usr/include/c++/10/)


find_package(Boost COMPONENTS system thread REQUIRED)


add_executable(coroutine_server
  main.cpp
  connection.cpp
  sessions/echo_session.cpp
  coroutines_support/read_awaiter.cpp
  coroutines_support/write_awaiter.cpp
)

target_include_directories(coroutine_server PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/coroutines_support/
                           ${CMAKE_CURRENT_SOURCE_DIR}/net_headers/
                           ${CMAKE_CURRENT_SOURCE_DIR}/sessions/
                           )


target_link_libraries(coroutine_server Boost::system Boost::thread)
