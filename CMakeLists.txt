cmake_minimum_required(VERSION 3.10)

# 项目信息
project(logical_calcule C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options("/source-charset:utf-8")
endif()

# 自动添加所有 .c 文件
file(GLOB SOURCES
    *.c
)

# 生成可执行文件
add_executable(logical_calcule ${SOURCES})
