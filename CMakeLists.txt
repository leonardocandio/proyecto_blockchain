cmake_minimum_required(VERSION 3.24)
project(proyecto_blockchain VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(proyecto_blockchain
        mainwindow.ui
        mainwindow.cpp
        main.cpp
        )
target_link_libraries(proyecto_blockchain
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

set_target_properties(proyecto_blockchain PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
        )