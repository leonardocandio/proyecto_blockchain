cmake_minimum_required(VERSION 3.24)
project(proyecto_blockchain VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)


add_executable(proyecto_blockchain
        src/main.cpp
        src/app/block.cpp src/app/blockchain.cpp)
target_link_libraries(proyecto_blockchain
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
target_link_libraries(proyecto_blockchain OpenSSL::SSL OpenSSL::Crypto)
set_target_properties(proyecto_blockchain PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
        )