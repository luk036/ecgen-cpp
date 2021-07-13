cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(ECGenCppStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.1
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  add_compile_options(-fcoroutines -Wall -Wnon-virtual-dtor -Wunused -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using clang
  add_compile_options(
    -fcoroutines-ts
    -stdlib=libc++
    -fno-exceptions
    -Wall
    -Wnon-virtual-dtor
    -Wunused
    -pedantic
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  add_compile_options(/std:c++latest /await /W3 /WX)
endif()

# CPMAddPackage( NAME cppcoro GIT_TAG 1.0 GITHUB_REPOSITORY luk036/cppcoro )

CPMAddPackage(NAME ECGenCpp SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(ECGenCppStandalone ${sources})

set_target_properties(ECGenCppStandalone PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "ECGenCpp")

target_link_libraries(ECGenCppStandalone ECGenCpp::ECGenCpp cxxopts cppcoro::cppcoro)
