cmake_minimum_required(VERSION 3.3)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${PROJECT_NAME})

add_executable(macropad macropad.cpp)

