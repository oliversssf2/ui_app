cmake_minimum_required(VERSION 3.1)

project(ui_app)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

add_subdirectory(helper)

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
    )

target_link_libraries(application
    PRIVATE Qt5::Widgets
    PRIVATE Qt5::Gui
    PRIVATE Qt5::Core
    PRIVATE helper
    )
