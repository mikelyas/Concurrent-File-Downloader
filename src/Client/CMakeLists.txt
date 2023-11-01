set(CLIENT_SOURCES
    "Client.cpp")
set(CLIENT_HEADERS
    "Client.h")

add_library(${CLIENT_LIB_NAME} STATIC
    ${CLIENT_SOURCES}
    ${CLIENT_HEADERS})

target_include_directories(${FILE_TRANSFER_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../FileTransfer
    ${CMAKE_CURRENT_SOURCE_DIR}/../FileSystemHandler)

target_link_libraries(${CLIENT_LIB_NAME} PUBLIC
    ${FILE_TRANSFER_LIB_NAME}
    ${FILE_SYSTEM_HANDLER_LIB_NAME})