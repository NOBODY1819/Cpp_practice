cmake_minimum_required(VERSION 3.10)
project(TcpEchoServer)

add_executable(server main.cpp)

target_compile_features(server PRIVATE cxx_std_17)
target_link_libraries(server PRIVATE ws2_32)