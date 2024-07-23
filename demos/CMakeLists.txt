cmake_minimum_required(VERSION 3.0.0)
project(MyProject LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(ZMQ REQUIRED libzmq)

# Include directories for libzmq
include_directories(${ZMQ_INCLUDE_DIRS})

# Link directories for libzmq
link_directories(${ZMQ_LIBRARY_DIRS})

# Add your executable
add_executable(my_project_demo demo1.cpp)

# Link libzmq to your executable
target_link_libraries(my_project_demo ${ZMQ_LIBRARIES})
