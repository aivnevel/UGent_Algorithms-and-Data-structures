cmake_minimum_required(VERSION 3.10)

project(geval_test_demo_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)	

add_executable(exthash src/main.cpp)

add_library(exthashlib SHARED include/exthash.h include/schijf.h include/pagina.h include/utils.h src/exthash.cpp)
target_link_libraries(exthash PUBLIC exthashlib)
