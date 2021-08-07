project(FileFinder)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC_FILES
    ${SRC_DIR}/filefinder.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INC_DIR}
)