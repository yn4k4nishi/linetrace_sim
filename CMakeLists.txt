cmake_minimum_required(VERSION 3.8)
project(linetrace_sim)

find_package(PythonLibs 2.7)

include_directories(
        include
        /usr/include
        /usr/include/eigen3
        /usr/include/x86_64-linux-gnu
)

add_executable(${PROJECT_NAME}
        src/main.cpp
        include/matplotlibcpp.h
        include/robot.h
        include/motor.h
        include/timer.h
        include/world.h
        include/line.h
        include/noised_motor.h)

target_include_directories(${PROJECT_NAME} PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
