cmake_minimum_required(VERSION 3.4.1)
set(PROJECT_NAME HPSocket)
project(${PROJECT_NAME})

if (INCLUDE_HPSOCKET)
    return()
endif ()

message(STATUS "正在编译 ${PROJECT_NAME}")
set(INCLUDE_HPSOCKET YES CACHE STRING DOCSTRING FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# 添加宏定义否则三方库 HPSocket 编译不通过
ADD_DEFINITIONS(-D_BROTLI_DISABLED)
ADD_DEFINITIONS(-D_SSL_DISABLED)
ADD_DEFINITIONS(-D_HTTP_DISABLED)
ADD_DEFINITIONS(-D_ICONV_DISABLED)
ADD_DEFINITIONS(-D_ZLIB_DISABLED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-suggest-override")

include_directories(.
        ./include
        ./src
)

# 本工程的源文件
file(GLOB_RECURSE HPSOCKET_SRCS ./src/*.cpp ./src/*.c)

# 编译成静态库
add_library(hpsocket_static STATIC ${HPSOCKET_SRCS})
