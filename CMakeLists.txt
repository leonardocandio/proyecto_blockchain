cmake_minimum_required(VERSION 3.23)
project(proyecto_blockchain VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR} --build=missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()


add_executable(proyecto_blockchain
        src/main.cpp
        src/app/block.cpp src/app/blockchain.cpp src/app/lib/vector.hpp src/app/lib/vector_iterator.hpp)
target_link_libraries(proyecto_blockchain ${CONAN_LIBS})
