cmake_minimum_required(VERSION 3.12)
project(FileTransferApp)

# Clean the build directory before generating new files
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

# This is the path to where you installed boost on you local machine
set(BOOST_ROOT "C:/Program Files/Boost")

# Find the Boost package (you can specify specific components you need, e.g., system)
find_package(Boost REQUIRED COMPONENTS system)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found.")
endif()

# Add the Boost include directories to your project
include_directories(${Boost_INCLUDE_DIRS})

# Add the source files for the project
set(SOURCES
    src/Client.cpp
    src/Server.cpp
    src/InputHandler.cpp
    src/FileTransfer.cpp
    src/FileSystemHandler.cpp
    src/main.cpp
)

# Add the header files for the project
set(HEADERS
    src/Client.h
    src/Server.h
    src/InputHandler.h
    src/FileTransfer.h
    src/FileSystemHandler.h
)

# Add the executable target
add_executable(FileTransferApp ${SOURCES} ${HEADERS})

# Set C++17 as the target compile feature
target_compile_features(FileTransferApp PRIVATE cxx_std_17)
target_compile_definitions(FileTransferApp PRIVATE _WIN32_WINNT=0x0A00)