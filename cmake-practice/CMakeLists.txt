cmake_minimum_required(VERSION 3.20)
project(HelloModernCpp LANGUAGES CXX)

# Use modern C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable from your source file
add_executable(hello test.cpp)