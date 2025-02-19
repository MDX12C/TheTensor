cmake_minimum_required(VERSION 3.10)
project(tensor_next)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -Wall -g")

option(debugMode "Debug Mode?" OFF)
option(speedMode "Speed Mode?" OFF)
option(f16Mode "Use Float 16?" OFF)

if(debugMode)
message("### In DEBUG MODE ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MODE")
elseif(speedMode)
message("### In NORMAL MODE ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSPEED_MODE")
else()
message("### In SPEED MODE ###")
endif()
if(f16Mode)
message("### Use Float16 ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DF16")
else()
message("### Use Float32 ###")
endif()

find_package(HDF5 REQUIRED COMPONENTS CXX)

include_directories(
    include
    ${HDF5_INCLUDE_DIRS}
)

add_library(basic_hpp STATIC src/basic.cc)
add_library(memory_maintainer STATIC src/memory.cc)
add_library(logger STATIC src/log.cc)
add_library(rom STATIC src/rom.cc)

function(add_test_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} 
        PRIVATE logger memory_maintainer basic_hpp 
        PUBLIC HDF5::HDF5 rom
    )
endfunction()

add_test_executable(test_basic_hpp test/test_basic_hpp.cc)
add_test_executable(test_vector test/test_vector.cc)
add_test_executable(test_logger test/test_log.cc)
add_test_executable(test_matrix test/test_matrix.cc)
add_test_executable(test_network test/test_network.cc)
add_test_executable(test_rom test/test_rom.cc)
add_test_executable(test_story test/test_story.cc)
