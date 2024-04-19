cmake_minimum_required(VERSION 3.8)

add_library(File STATIC "file.cpp")

target_include_directories(File PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
