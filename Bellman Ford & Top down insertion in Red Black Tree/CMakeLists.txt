cmake_minimum_required(VERSION 3.10)

project(geval_test_demo_project)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)	

add_executable(bellman_ford src/vraag1.cpp include/bellmanford.h)

add_library(bellmanfordlib SHARED src/bellmanford.cpp include/graaf.h)
target_link_libraries(bellman_ford PUBLIC bellmanfordlib)

add_executable(roodzwart src/vraag2.cpp include/rzwboom.h include/rzwknoop.h)