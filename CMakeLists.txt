cmake_minimum_required(VERSION 3.1)

project(ui_app)
set(CMAKE_PREFIX_PATH "/home/fongsu/Qt/5.12.0/gcc_64/lib/cmake/Qt5")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Gui Core CONFIG REQUIRED)

#add_subdirectory(helper)
add_library(helper INTERFACE)
target_include_directories(helper INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/helper/")
target_sources(helper INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/helper/helper.h")

add_subdirectory(cmake)

add_executable(application)

target_sources(application
    PRIVATE main.cpp
    PRIVATE mainwindow.cpp
    PRIVATE mainwindow.h
    PRIVATE mainwindow.ui
    PRIVATE renderarea.cpp
    PRIVATE renderarea.h
    PRIVATE renderarea.ui
    PRIVATE pathplanner.cpp
    PRIVATE pathplanner.h
    PRIVATE pathplanner.ui
    PRIVATE "src/paths.qrc"
    PRIVATE "src/aircrafts.qrc"
    )

target_link_libraries(application
    PRIVATE Qt5::Widgets
    PRIVATE Qt5::Gui
    PRIVATE Qt5::Core
    PUBLIC helper
    )

target_include_directories(application
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/cmake"
    )

add_subdirectory(tool)
