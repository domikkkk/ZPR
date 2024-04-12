cmake_minimum_required(VERSION 3.8)
include(FetchContent)

project("files_compare")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_DIR}/cmake")

add_executable(${PROJECT_NAME} "src/main.cpp")  # adding main

target_link_libraries(${PROJECT_NAME})


# adding qt5

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)


# adding subdirectory like in src/compare_files/{DIR_NAME}
add_subdirectory("src/app/mainwindow")
add_subdirectory("src/compare_files/cos")


target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Widgets mainwindow Cos)


FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG        "release-1.11.0"
)

FetchContent_MakeAvailable(Gtest)

# testing
add_executable(tests "test/test.cpp")

target_link_libraries(tests gtest gtest_main Cos)