cmake_minimum_required(VERSION 4.1)
project(Simulator_ETTI)

set(CMAKE_CXX_STANDARD 20)

add_executable(Simulator_ETTI main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
