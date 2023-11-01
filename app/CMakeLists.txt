set(EXE_SOURCES
    "main.cpp")

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/InputHandler)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
    ${INPUT_HANDLER_LIB_NAME})