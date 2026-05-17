# Calculator Application

A simple C++ Calculator application built with CMake for cross-platform support.

## Features

- **Sum**: Add two integers
- **Difference**: Calculate difference between two integers
- **Multi-platform support**: Linux, RHEL7, RHEL9

## Prerequisites

- CMake 3.10 or higher
- C++11 compatible compiler (GCC, Clang, or MSVC)
- Make or Ninja build system

## Building on Different Platforms

### Generic Linux
```bash
cd build
cmake ..
make
./bin/calculator
```

### RHEL 7
```bash
cd build
cmake ..
make
./bin/calculator
```

### RHEL 9
```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./bin/calculator
```

### With Release Build Type
```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./bin/calculator
```

### With Debug Build Type
```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
./bin/calculator
```

## Project Structure
```
.
├── CMakeLists.txt
├── README.md
├── include/
│   └── calculator.h
├── src/
│   ├── calculator.cpp
│   └── main.cpp
└── build/
    └── (generated files)
```

## Expected Output
```
Calculator Demo
===============
10 + 5 = 15
10 - 5 = 5
```

## CMake Platform Detection

The CMakeLists.txt automatically detects the platform and RHEL version, applying appropriate compiler flags and compile definitions:

- **Linux (Generic)**: Standard compilation flags
- **RHEL 7**: Optimized for older compiler toolchains
- **RHEL 9**: Optimized for modern compiler toolchains

Each platform gets its own compile definition which can be used in your code if needed.
