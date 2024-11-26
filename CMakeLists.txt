# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ProductCache VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include current directory and 'include' folder for headers
include_directories(${CMAKE_SOURCE_DIR})  # Adds the root directory (where ProductCache.h is located)
include_directories(${CMAKE_SOURCE_DIR}/include)  # Adds the 'include' folder

# Main executable
add_executable(product_cache src/main.cpp)

# Unit tests
# Enable testing
enable_testing()

# Add test executables
add_executable(test_product_cache tests/test_product_cache.cpp)
add_executable(test_lru_cache tests/test_lru_cache.cpp)

# Link Google Test (find package first)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(test_product_cache GTest::GTest GTest::Main pthread)
target_link_libraries(test_lru_cache GTest::GTest GTest::Main pthread)

# Add tests to CMake
add_test(NAME ProductCacheTests COMMAND test_product_cache)
add_test(NAME LRUCacheTests COMMAND test_lru_cache)
