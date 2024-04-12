cmake_minimum_required(VERSION 3.8)

add_library(mainwindow STATIC "mainwindow.cpp")

target_include_directories(mainwindow PUBLIC "${CMAKE_SOURCE_DIR}/include/" ${CMAKE_CURRENT_SOURCE_DIR})
