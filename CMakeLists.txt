cmake_minimum_required(VERSION 3.23)
project(proyecto_blockchain VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Crow CONFIG REQUIRED)

add_executable(proyecto_blockchain
        src/main.cpp
        src/app/block.cpp src/app/blockchain.cpp src/app/transaction.cpp src/app/transaction.h src/app/lib/vector.hpp src/app/lib/vector_iterator.hpp)

if (MINGW)
    find_library(WSOCK32_LIBRARY wsock32)
    find_library(WS2_32_LIBRARY ws2_32)
    target_link_libraries(proyecto_blockchain PUBLIC ws2_32 wsock32)
endif ()
target_link_libraries(proyecto_blockchain PRIVATE Crow::Crow)
