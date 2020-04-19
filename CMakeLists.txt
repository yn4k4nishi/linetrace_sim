cmake_minimum_required(VERSION 3.8)
project(linetrace_sim)

find_package(Python2 COMPONENTS Development NumPy)

include_directories(
        include
        /usr/include
)

add_executable(${PROJECT_NAME}
        src/main.cpp
        include/matplotlibcpp.h
        )

target_include_directories(${PROJECT_NAME} PRIVATE ${Python2_INCLUDE_DIRS} ${Python2_NumPy_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Python2::Python Python2::NumPy)
