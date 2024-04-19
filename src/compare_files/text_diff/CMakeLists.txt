cmake_minimum_required(VERSION 3.8)

add_library(TextDiff STATIC "textdiff.cpp")

target_include_directories(TextDiff PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
