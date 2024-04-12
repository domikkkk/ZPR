cmake_minimum_required(VERSION 3.8)

add_library(Cos STATIC "cos.cpp")

target_include_directories(Cos PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
