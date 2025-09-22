# Gemini Code Assistant Report

## Project Overview

This project, `ecgen-cpp`, is a C++ library for generating combinatorial objects. It leverages C++20 features, particularly coroutines, to provide an efficient and easy-to-use interface for iterating through combinations, permutations, and other combinatorial structures.

The project is well-structured, with a clear separation between the library code, tests, and examples. It uses modern CMake for building and managing dependencies, and also provides an alternative build system using xmake.

The core of the library lies in its use of coroutines to implement generators. This allows for lazy generation of combinatorial sequences, which is memory-efficient as it doesn't require storing all the generated objects in memory at once. The library also provides Gray code-like generators that return only the "delta" or change from the previous object, further enhancing efficiency.

## Building and Running

The project can be built using either CMake or xmake.

### CMake

**Build all targets (library, tests, and standalone executable):**

```bash
cmake -S all -B build
cmake --build build
```

**Run tests:**

```bash
./build/test/EcGenTests
```

**Run standalone executable:**

```bash
./build/standalone/EcGen --help
```

### xmake

**Build the project:**

```bash
xmake
```

**Run tests:**

```bash
xmake run test_ecgen
```

## Development Conventions

### Coding Style

The project enforces a consistent coding style using `clang-format` for C++ code and `cmake-format` for CMake files. The formatting can be checked and fixed using the following commands:

```bash
# Check formatting
cmake --build build --target format

# Fix formatting
cmake --build build --target fix-format
```

### Testing

The project uses the `doctest` framework for unit testing. Tests are located in the `test` directory and can be run using the `ctest` command or by directly executing the test binary.

### Dependencies

Dependencies are managed using `CPM.cmake`, which is a CMake script that allows for reproducible dependency management. Dependencies are declared in the `CMakeLists.txt` file.

### Documentation

The project uses Doxygen to generate documentation from the source code comments. The documentation can be built using the following command:

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
```
