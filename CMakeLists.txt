cmake_minimum_required(VERSION 3.0)

project(throttleCPU)

add_executable(throttleCPU
    throttleCPU.cpp
)

target_include_directories(throttleCPU
    PRIVATE
        /usr/include/
)

install(TARGETS throttleCPU DESTINATION bin)
