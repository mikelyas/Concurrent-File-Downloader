set(FILE_TRANSFER_SOURCES
    "FileTransfer.cpp")
set(FILE_TRANSFER_HEADERS
    "FileTransfer.h")

add_library(${FILE_TRANSFER_LIB_NAME} STATIC
    ${FILE_TRANSFER_SOURCES}
    ${FILE_TRANSFER_HEADERS})

target_include_directories(${FILE_TRANSFER_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../FileSystemHandler)

target_link_libraries(${FILE_TRANSFER_LIB_NAME} PUBLIC
    ${FILE_SYSTEM_HANDLER_LIB_NAME})