cmake_minimum_required(VERSION 3.14)
project(TcpWebSocketEchoServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp websocket_helper.cpp)

target_link_libraries(server PRIVATE ws2_32)