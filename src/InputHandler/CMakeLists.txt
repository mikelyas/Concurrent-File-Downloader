set(INPUT_HANDLER_SOURCES
    "InputHandler.cpp")
set(INPUT_HANDLER_HEADERS
    "InputHandler.h")

add_library(${INPUT_HANDLER_LIB_NAME} STATIC
    ${INPUT_HANDLER_SOURCES}
    ${INPUT_HANDLER_HEADERS})

target_include_directories(${INPUT_HANDLER_LIB_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../Client
    ${CMAKE_CURRENT_SOURCE_DIR}/../Server)

target_link_libraries(${INPUT_HANDLER_LIB_NAME} PUBLIC
    ${CLIENT_LIB_NAME}
    ${SERVER_LIB_NAME})