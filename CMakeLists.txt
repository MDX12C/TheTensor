cmake_minimum_required(VERSION 3.10)
project(tensor_next)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -Wall")

include_directories(include)

add_library(basic_hpp STATIC src/basic.cc)
add_library(memory_maintainer STATIC src/memory.cc)
add_library(logger STATIC src/log.cc)
add_library(rom STATIC src/rom.cc)
find_package(HDF5 REQUIRED COMPONENTS CXX)

add_executable(test_basic_hpp test/test_basic_hpp.cc)
target_link_libraries(test_basic_hpp logger memory_maintainer basic_hpp HDF5::HDF5 rom)

add_executable(test_vector test/test_vector.cc)
target_link_libraries(test_vector logger memory_maintainer basic_hpp HDF5::HDF5 rom)

add_executable(test_logger test/test_log.cc)
target_link_libraries(test_logger logger memory_maintainer basic_hpp HDF5::HDF5 rom)

add_executable(test_matrix test/test_matrix.cc)
target_link_libraries(test_matrix logger memory_maintainer basic_hpp HDF5::HDF5 rom)

add_executable(test_network test/test_network.cc)
target_link_libraries(test_network logger memory_maintainer basic_hpp HDF5::HDF5 rom)

add_executable(test_rom test/test_rom.cc)
target_link_libraries(test_rom logger memory_maintainer basic_hpp HDF5::HDF5 rom)