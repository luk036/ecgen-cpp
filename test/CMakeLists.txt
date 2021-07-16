cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(ECGenTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:onqtam/doctest#2.4.5")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.0")

# CPMAddPackage( NAME cppcoro GIT_TAG 1.0 GITHUB_REPOSITORY luk036/cppcoro )

if(TEST_INSTALLED_VERSION)
  find_package(ECGen REQUIRED)

  CPMAddPackage("gh:luk036/bingo#0.1.2")
  # CPMAddPackage("gh:TheLartians/ModernCppStarter@0.17.3")

  CPMAddPackage(
    NAME cppcoro
    GIT_TAG 1.0
    GITHUB_REPOSITORY luk036/cppcoro
  )
  # print_target_properties(cppcoro)
  if(cppcoro_ADDED)
    message(STATUS "Found cppcoro: ${cppcoro_SOURCE_DIR}")
    add_library(cppcoro::cppcoro INTERFACE IMPORTED GLOBAL)
    target_include_directories(cppcoro::cppcoro SYSTEM INTERFACE ${cppcoro_SOURCE_DIR}/include)
    set_target_properties(cppcoro::cppcoro PROPERTIES CXX_STANDARD 20)
  endif(cppcoro_ADDED)

else()
  CPMAddPackage(NAME ECGen SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

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

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(ECGenTests ${sources})
target_link_libraries(ECGenTests doctest::doctest ECGen::ECGen cppcoro::cppcoro)
set_target_properties(ECGenTests PROPERTIES CXX_STANDARD 20)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(ECGen PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(ECGen PUBLIC /W4 /WX)
    target_compile_definitions(ECGenTests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add ECGenTests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake tests. For other
# testing frameworks add the tests target instead: add_test(NAME ecgenTests COMMAND ECGenTests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(ECGenTests)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(ECGen PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(ECGen PUBLIC -fprofile-arcs -ftest-coverage)
endif()
