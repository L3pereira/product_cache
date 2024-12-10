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

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the library (ProductCache with ProductDatabase and LRUCache)
add_library(product_cache STATIC
    src/product_cache.cpp
    src/product_database.cpp   # Include ProductDatabase.cpp
)

# Main executable (Optional)
add_executable(product_cache_example examples/main.cpp)
target_link_libraries(product_cache_example product_cache)

# Enable testing
enable_testing()

# Add test executables for ProductCache and LRUCache tests
add_executable(test_product_cache tests/test_product_cache.cpp)
add_executable(test_lru_cache tests/test_lru_cache.cpp)
add_executable(test_product_category tests/test_product_category.cpp)

# Cross-platform settings for Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add platform-specific libraries
if(WIN32)
    # On Windows, no pthread is needed
    target_link_libraries(test_product_cache product_cache GTest::GTest GTest::Main)
    target_link_libraries(test_lru_cache product_cache GTest::GTest GTest::Main)
    target_link_libraries(test_product_category product_cache GTest::GTest GTest::Main)
else()
    # On Unix-like systems, link pthread explicitly
    target_link_libraries(test_product_cache product_cache GTest::GTest GTest::Main pthread)
    target_link_libraries(test_lru_cache product_cache GTest::GTest GTest::Main pthread)
    target_link_libraries(test_product_category product_cache GTest::GTest GTest::Main pthread)
endif()

# Register the tests with CTest
add_test(NAME product_cache_tests COMMAND test_product_cache)
add_test(NAME lru_cache_tests COMMAND test_lru_cache)
add_test(NAME product_category_tests COMMAND test_product_category)
