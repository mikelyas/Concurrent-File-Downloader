cmake_minimum_required(VERSION 3.16)
project(FileTransferApp)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(EXECUTABLE_NAME FileTransferApp)
set(CLIENT_LIB_NAME ClientLib)
set(SERVER_LIB_NAME ServerLib)
set(FILE_SYSTEM_HANDLER_LIB_NAME FileSystemHandlerLib)
set(FILE_TRANSFER_LIB_NAME FileTransferLib)
set(INPUT_HANDLER_LIB_NAME InputHandlerLib)

# Find the Boost package (you can specify specific components you need, e.g., system)
find_package(Boost 1.74)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found.")
endif()

# Add the Boost include directories to your project
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(app)