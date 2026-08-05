cmake_minimum_required(VERSION 3.14)
project(EcGenInstalledTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies first - the installed config references fmt and Py2Cpp.
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Py2Cpp REQUIRED)
find_package(EcGen REQUIRED)

add_executable(ecgen_installed_test main.cpp)
target_link_libraries(ecgen_installed_test PRIVATE EcGen::EcGen)

enable_testing()
add_test(NAME ecgen_installed_test COMMAND ecgen_installed_test)
