cmake_minimum_required(VERSION 3.4.1)
set(PROJECT_NAME Client)
project(${PROJECT_NAME})

# 如果没有包含Communication模块
if (INCLUDE_CLIENT)
    return()
endif ()

message(STATUS "正在编译 ${PROJECT_NAME}")
set(INCLUDE_CLIENT YES CACHE STRING DOCSTRING FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# 单元测试
if (COVERAGE)
    message(STATUS "${PROJECT_NAME} 进行覆盖率统计")
    # 添加覆盖率编译参数
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif ()

# 本工程引用的外部头文件目录
include_directories(
        include
        ../common
        ../hpsocket/include
)

# 引用的其他库
add_subdirectory(../hpsocket hpsocket.out)

# 本工程的源文件
file(GLOB_RECURSE CLIENT_SRCS src/*.cpp)

# 编译成静态库
add_library(client_static STATIC ${CLIENT_SRCS})
target_link_libraries(
        client_static
        -Wl,--start-group
        hpsocket_static
        -Wl,--end-group
)

OPTION(TEST "set ON to run client" ON)
if (TEST)
    add_executable(run_client test/test.cpp)
    target_link_libraries(run_client client_static)
endif ()

