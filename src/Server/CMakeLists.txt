set(SERVER_SOURCES
    "Server.cpp")
set(SERVER_HEADERS
    "Server.h")

add_library(${SERVER_LIB_NAME} STATIC
    ${SERVER_SOURCES}
    ${SERVER_HEADERS})

target_include_directories(${FILE_TRANSFER_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../FileTransfer)

target_link_libraries(${SERVER_LIB_NAME} PUBLIC
    ${FILE_TRANSFER_LIB_NAME})