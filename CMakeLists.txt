cmake_minimum_required(VERSION 3.10)
project(tensor_next LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -Wall -g")

option(debugMode "Debug Mode?" OFF)
option(speedMode "Speed Mode?" OFF)
option(f16Mode "Use Float 16?" OFF)
option(limitMode "Limit?" OFF)

if(debugMode)
message("### In DEBUG MODE ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MODE")
else()
message("### In NORMAL MODE ###")
endif()
if(speedMode)
message("### In SPEED MODE ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSPEED_MODE")
else()
message("### In STANDARD MODE ###")
endif()
if(f16Mode)
message("### Use Float16 ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DF16")
else()
message("### Use Float32 ###")
endif()
if(limitMode)
message("### LIMIT ###")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIMIT_MODE")
else()
message("### UNLIMIT ###")
endif()

include_directories(
    include
    ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
)

add_library(basic_hpp STATIC src/basic.cc)
add_library(memory_maintainer STATIC src/memory.cc)
add_library(logger STATIC src/log.cc)
add_library(random STATIC src/random.cc)
add_library(parallel STATIC src/parallel.cu)

function(add_test_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} 
        PRIVATE logger memory_maintainer basic_hpp random parallel
        PUBLIC  rom
    )
endfunction()

add_test_executable(test_basic_hpp test/test_basic_hpp.cc)
add_test_executable(test_vector test/test_vector.cc)
add_test_executable(test_logger test/test_log.cc)
add_test_executable(test_matrix test/test_matrix.cc)
add_test_executable(test_network test/test_network.cc)
add_test_executable(test_rom test/test_rom.cc)
add_test_executable(test_story test/test_story.cc)
add_test_executable(maker_network test/datas_maker.cc)
add_test_executable(data_reader test/data_reader.cc)
add_test_executable(model test/model.cc)
add_test_executable(test_random test/test_random.cc)
add_test_executable(test_parallel test/test_parallel.cc)
add_executable(cuda_test test/cuda_test.cu)