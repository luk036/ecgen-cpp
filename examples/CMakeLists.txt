# Examples CMakeLists.txt

cmake_minimum_required(VERSION 3.14)

add_executable(spdlog_example spdlog_example.cpp)
target_link_libraries(spdlog_example PRIVATE EcGen fmt::fmt spdlog::spdlog)