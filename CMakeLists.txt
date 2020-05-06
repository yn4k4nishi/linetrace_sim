cmake_minimum_required(VERSION 3.8)
project(linetrace_sim)

#-DPYTHON_INCLUDE_DIR=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")  \
#-DPYTHON_LIBRARY=$(python -c "import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR'))")

#find_package(PythonLibs 2.7)
find_package(Python3 COMPONENTS Development NumPy)
message(python3_found : ${Python3_FOUND})

include_directories(
        include
        /usr/include
        /usr/include/eigen3
        /usr/include/x86_64-linux-gnu
#        /usr/lib/python3.8
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
