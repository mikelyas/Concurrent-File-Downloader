cmake_minimum_required(VERSION 3.12)
project(FileTransferApp)

# This is the path to where you installed boost on you local machine
set(BOOST_ROOT "C:/Program Files/Boost")

# Find the Boost package (you can specify specific components you need, e.g., system)
find_package(Boost REQUIRED COMPONENTS system)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found.")
endif()

# Add the Boost include directories to your project
include_directories(${Boost_INCLUDE_DIRS})

# Clean the build directory before generating new files
file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}")

# Add the source files for the project
set(SOURCES
    src/Client.cpp
    src/Server.cpp
    src/InputHandler.cpp
    src/FileTransfer.cpp
    src/main.cpp
)

# Add the header files for the project
set(HEADERS
    src/Client.h
    src/Server.h
    src/InputHandler.h
    src/FileTransfer.h
)

# Add the executable target
add_executable(FileTransferApp ${SOURCES} ${HEADERS})

