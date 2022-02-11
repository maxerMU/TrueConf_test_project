cmake_minimum_required(VERSION 3.5)

project(boost_sync_server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system thread REQUIRED)

add_executable(boost_sync_server
  main.cpp
)

target_link_libraries(boost_sync_server Boost::system Boost::thread)

