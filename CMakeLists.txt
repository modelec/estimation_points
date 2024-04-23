cmake_minimum_required(VERSION 3.25)
project(estimation_points)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(TCPSocket REQUIRED TCPSocket)

add_executable(estimation_points main.cpp
        tcp/MyClient.cpp
        tcp/MyClient.h
        tcp/MyClient.h)
