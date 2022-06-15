cmake_minimum_required(VERSION 3.4)
project(HPSocketDemo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# 添加编译选项
add_compile_options(-fPIC)

include_directories(
        Common
        Client/Export_Inc
        Server/Export_Inc
)

add_subdirectory(Client Client.out)
add_subdirectory(Server Server.out)

aux_source_directory(Common COMMON_SRCS)
add_library(Communication_shared SHARED ${COMMON_SRCS})
target_link_libraries(
        Communication_shared
        Client_static
        Server_static
)

add_executable(runMain main.cpp)
target_link_libraries(
        runMain
        Communication_shared
)