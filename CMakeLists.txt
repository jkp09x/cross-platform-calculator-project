cmake_minimum_required(VERSION 3.10)
project(CalculatorApp VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform Detection
message(STATUS "Detected OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "OS Version: ${CMAKE_SYSTEM_VERSION}")

# Determine platform type
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building for Linux")
    set(PLATFORM_LINUX TRUE)
    
    # Detect RHEL version
    if(EXISTS "/etc/redhat-release")
        file(READ "/etc/redhat-release" REDHAT_RELEASE)
        message(STATUS "RHEL Release Info: ${REDHAT_RELEASE}")
        
        if(REDHAT_RELEASE MATCHES "release 7")
            message(STATUS "Detected RHEL 7")
            set(RHEL_VERSION 7)
            add_compile_definitions(RHEL7)
        elseif(REDHAT_RELEASE MATCHES "release 9")
            message(STATUS "Detected RHEL 9")
            set(RHEL_VERSION 9)
            add_compile_definitions(RHEL9)
        endif()
    else()
        message(STATUS "Generic Linux detected (not RHEL)")
        set(RHEL_VERSION 0)
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building for Windows")
    set(PLATFORM_WINDOWS TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Building for macOS")
    set(PLATFORM_MACOS TRUE)
else()
    message(WARNING "Unknown platform: ${CMAKE_SYSTEM_NAME}")
endif()

# Set compiler flags based on platform
if(MSVC)
    # Windows Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    # GCC / Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    
    # Platform-specific flags for RHEL
    if(DEFINED RHEL_VERSION)
        if(RHEL_VERSION EQUAL 7)
            # RHEL 7 might have older compilers
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
        elseif(RHEL_VERSION EQUAL 9)
            # RHEL 9 has more modern compilers
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
        endif()
    endif()
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/calculator.cpp
    src/main.cpp
)

# Create executable
add_executable(calculator ${SOURCES})

# Output directory
set_target_properties(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# ===== TESTING =====

# Enable testing
enable_testing()

# Create test executable
add_executable(calculator_test tests/calculator_test.cpp src/calculator.cpp)

# Set test output directory
set_target_properties(calculator_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add test to CTest
add_test(NAME CalculatorTests COMMAND calculator_test)

message(STATUS "Tests enabled. Run with: ctest or ./bin/calculator_test")

# Print configuration summary
message(STATUS "")
message(STATUS "========== Build Configuration ==========")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "=========================================")
message(STATUS "")

