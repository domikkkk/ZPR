cmake_minimum_required(VERSION 3.8)
include(FetchContent)

project("files_compare")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

# set(Qt5_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qt/usr/lib/x86_64-linux-gnu/cmake/Qt5")
# set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qt/usr")
# set(CMAKE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qt/usr/include")
# set(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH}; ${CMAKE_CURRENT_SOURCE_DIR}/qt/usr/include/GL")
# set(CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/qt/usr/lib")

# adding qt5

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp")  # adding main

target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)


# Internet mówi, że trzeba dodać plik nagłówkowy do kompilacji też jak w gre wchodzi macro Q_OBJECT, które jest ponoć potrzebne w jakimś stopniu.
# Cmake jest upośledzony i trzeba mu samemu ustawić plik nagłówkowy do kompilacji, bo mimo tego target_include_directories (wyżej) nie znajduje tego co powinien.
# Trzeba to dać, bo inaczej wie co to Q_OBJECT, ale nie wie gdzie ma znaleźć tablice funkcji wirtualnych dla konstruktorów,
# destruktorów, funkcji ect. dla naszej klasy MainWindow, w której mamy to coś.
# A Tu przybliżona definicja Q_OBJECT skopiowana z biblioteki:

# #define Q_OBJECT \
# public: \
#     QT_WARNING_PUSH \
#     Q_OBJECT_NO_OVERRIDE_WARNING \
#     static const QMetaObject staticMetaObject; \
#     virtual const QMetaObject *metaObject() const; \
#     virtual void *qt_metacast(const char *); \
#     virtual int qt_metacall(QMetaObject::Call, int, void **); \
#     QT_TR_FUNCTIONS \
# private: \
#     Q_OBJECT_NO_ATTRIBUTES_WARNING \
#     Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
#     QT_WARNING_POP \
#     struct QPrivateSignal {}; \
#     QT_ANNOTATE_CLASS(qt_qobject, "")
set(MainWindow_HPP "${CMAKE_SOURCE_DIR}/include/mainwindow.hpp")  # tu jest właśnie danie wskazania na nasz plik hpp
set(Button_HPP "${CMAKE_SOURCE_DIR}/include/button.hpp")
set(TWidget_HPP "${CMAKE_SOURCE_DIR}/include/TWidget.hpp")

# adding subdirectory like in src/compare_files/{DIR_NAME}
add_subdirectory("src/compare_files")
add_subdirectory("src/app")

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui CompareFiles mainwindow)


FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG        "release-1.11.0"
)

FetchContent_MakeAvailable(Gtest)

# testing
add_executable(tests "test/test.cpp")

target_link_libraries(tests gtest gtest_main CompareFiles)
