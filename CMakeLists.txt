cmake_minimum_required(VERSION 3.8)
project(linetrace_sim)

include_directories(
        include
        /usr/include
)

add_executable(${PROJECT_NAME}
        src/main.cpp
        include/matplotlibcpp.h
        )

#target_link_libraries()
