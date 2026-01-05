cmake_minimum_required(VERSION 4.0)
project(cipr)

set(CMAKE_CXX_STANDARD 17)

add_executable(cipr src/main.cpp
        src/Token/Token.h
        src/Scanner/Scanner.h
        src/Scanner/Scanner.cpp
        src/Core/Core.cpp
        src/Core/Core.h)
