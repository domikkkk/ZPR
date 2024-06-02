cmake_minimum_required(VERSION 3.8)

# definicja MainWindow_HPP w głównym cmake wraz z objaśnieniem dlaczego tak, a nie inaczej.
add_library(mainwindow STATIC "mainwindow.cpp" ${MainWindow_HPP} "button.cpp" ${Button_HPP} "TWidget.cpp" ${TWidget_HPP} "legend.cpp" ${Legend_HPP})

target_include_directories(mainwindow PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(mainwindow PUBLIC CompareFiles Qt5::Widgets Qt5::Core Qt5::Gui)
