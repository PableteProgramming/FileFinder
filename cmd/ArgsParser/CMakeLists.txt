project(ArgsParser)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC_FILES
    ${SRC_DIR}/argsparser.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INC_DIR}
)