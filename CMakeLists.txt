cmake_minimum_required(VERSION 3.8)
project(linetrace_sim)

#find_package(PythonLibs 2.7)
find_package(Python3 COMPONENTS Development NumPy)

message("Python3_FOUND : ${Python3_FOUND}")
message("Python3_Development_FOUND : ${Python3_Development_FOUND}")
message("Python3_INCLUDE_DIRS : ${Python3_INCLUDE_DIRS}")
message("Python3_NumPy_INCLUDE_DIRS : ${Python3_NumPy_INCLUDE_DIRS}")

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
        include/noised_motor.h
        include/noised_sensor.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Python3::Python Python3::NumPy)
