cmake_minimum_required(VERSION 3.4)
project(HPSocketDemo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_compile_options(-fPIC)
add_compile_options(-g)

add_subdirectory(client client.out)
add_subdirectory(server server.out)