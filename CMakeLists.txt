cmake_minimum_required(VERSION 3.15)
project(bletest VERSION 0.0.1)

find_package(simpleble REQUIRED CONFIG)

add_executable(bletest_exe 
    Source/bleclient.cpp
    Source/utils.cpp)

target_link_libraries(bletest_exe PRIVATE simpleble::simpleble)
set_target_properties(bletest_exe PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED True)