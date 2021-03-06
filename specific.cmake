cpmaddpackage(
  NAME
  fmt
  GIT_TAG
  7.1.3
  GITHUB_REPOSITORY
  fmtlib/fmt
  OPTIONS
  "FMT_INSTALL YES" # create an installable target
)

cpmaddpackage(
  NAME
  Bingo
  GIT_TAG
  1.0
  GITHUB_REPOSITORY
  luk036/bingo-cpp
  OPTIONS
  "INSTALL_ONLY ON")

cpmaddpackage(NAME cppcoro GIT_TAG 1.0 GITHUB_REPOSITORY luk036/cppcoro)
# print_target_properties(cppcoro)
if(cppcoro_ADDED)
  message(STATUS "Found cppcoro: ${cppcoro_SOURCE_DIR}")
  add_library(cppcoro::cppcoro INTERFACE IMPORTED GLOBAL)
  target_include_directories(cppcoro::cppcoro SYSTEM
                             INTERFACE ${cppcoro_SOURCE_DIR}/include)
endif(cppcoro_ADDED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  add_compile_options(-fcoroutines)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using clang
  add_compile_options(-fcoroutines-ts -stdlib=libc++)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  add_compile_options(/std:c++latest /await)
endif()

set(SPECIFIC_LIBS cppcoro::cppcoro Bingo::Bingo fmt::fmt)
