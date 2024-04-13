cmake_minimum_required(VERSION 3.8)

add_library(KMP STATIC "kmp.cpp")

target_include_directories(KMP PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
