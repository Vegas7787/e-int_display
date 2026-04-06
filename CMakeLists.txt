cmake_minimum_required(VERSION 3.15)
project(eink)

set(CMAKE_CXX_STANDARD 17)

find_package(pybind11 REQUIRED)
find_package(OpenCV REQUIRED)

pybind11_add_module(eink bindings.cpp convert_img.cpp)

target_link_libraries(eink PRIVATE ${OpenCV_LIBS})