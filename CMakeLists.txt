cmake_minimum_required(VERSION 3.10)
project(tensor_next)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -Wall")

include_directories(include)

add_library(basic_hpp STATIC src/basic.cc)
add_library(memory_maintainer STATIC src/memory.cc)

add_executable(test_basic_hpp test/test_basic_hpp.cc)
target_link_libraries(test_basic_hpp basic_hpp)

add_executable(test_vector test/test_vector.cc)
target_link_libraries(test_vector basic_hpp memory_maintainer)