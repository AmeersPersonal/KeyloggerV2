cmake_minimum_required(VERSION 3.29)
project(keyloggerv2)

set(CMAKE_CXX_STANDARD 20)

add_executable(keyloggerv2 main.cpp
        main.hpp
        linux_logger.cpp
        linux_logger.hpp
        window_logger.cpp
        window_logger.hpp)
