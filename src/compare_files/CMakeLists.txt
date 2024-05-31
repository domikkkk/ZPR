cmake_minimum_required(VERSION 3.8)

add_library(CompareFiles STATIC "kmp.cpp" "file.cpp" "block.cpp" "textdiff.cpp" "nw.cpp" "change.cpp" "comparator.cpp")

target_include_directories(CompareFiles PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
