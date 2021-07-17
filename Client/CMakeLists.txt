cmake_minimum_required(VERSION 3.4.1)
set(PROJECT_NAME Client)
project(${PROJECT_NAME})

# 如果没有包含Communication模块
if (NOT INCLUDE_CLIENT)
    message(STATUS "正在编译 ${PROJECT_NAME}")
    set(INCLUDE_CLIENT YES CACHE STRING DOCSTRING FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

    # 单元测试
    if (UNIT_TEST)
        message(STATUS "${PROJECT_NAME} 进行覆盖率统计")
        # 添加覆盖率编译参数
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif ()

    # 本工程引用的外部头文件目录
    include_directories(
            ./Export_Inc
            ./Source
            ../Common
            ../HPSocket/include
    )

    # 引用的其他库
    add_subdirectory(../HPSocket HPSocket.out)

    # 本工程的源文件
    file(GLOB_RECURSE CLIENT_SRCS Source/*.cpp)

    # 编译成静态库
    add_library(Client_static STATIC ${CLIENT_SRCS})
    target_link_libraries(
            Client_static
            -Wl,--start-group
            HPSocket_static
            -Wl,--end-group
    )

endif ()

