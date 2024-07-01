cmake_minimum_required(VERSION 3.10)
project(tensor_next)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -Wall")

include_directories(include)

add_library(simd_add STATIC src/simd_add.cc)

# Optionally add an example executable to test the library
add_executable(test_simd_add test/test_simd_add.cc)
target_link_libraries(test_simd_add simd_add)