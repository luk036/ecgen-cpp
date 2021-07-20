cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(ECGenStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.1
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

include(../specific.cmake)

# CPMAddPackage( NAME cppcoro GIT_TAG 1.0 GITHUB_REPOSITORY luk036/cppcoro )

CPMAddPackage(NAME ECGen SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(ECGenStandalone ${sources})

set_target_properties(ECGenStandalone PROPERTIES CXX_STANDARD 20 OUTPUT_NAME "ECGen")

target_link_libraries(ECGenStandalone ECGen::ECGen cxxopts cppcoro::cppcoro)
