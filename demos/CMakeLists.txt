cmake_minimum_required(VERSION 3.0.0)
project(MyProject LANGUAGES C CXX)

set(CMAKE_PREFIX_PATH "/usr/include")

find_package(ZeroMQ REQUIRED)

add_executable(MyProject demo1.cpp)

target_link_libraries(MyProject PRIVATE ZeroMQ::libzmq)

set_property(TARGET MyProject PROPERTY CXX_STANDARD 11)