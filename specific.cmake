CPMAddPackage(
  NAME fmt
  GIT_TAG 7.1.3
  GITHUB_REPOSITORY fmtlib/fmt
  OPTIONS "FMT_INSTALL YES" # create an installable target
)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  add_compile_options(-fcoroutines)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using clang
  add_compile_options(-stdlib=libc++)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  add_compile_options(/std:c++latest /await:strict)
endif()

set(SPECIFIC_LIBS fmt::fmt)
# remember to turn off the warnings
