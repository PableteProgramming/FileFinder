project(FileFinder)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(FUNCS_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../funcs/include)

set(SRC_FILES
    ${SRC_DIR}/filefinder.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INC_DIR}
    ${FUNCS_INC_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    termcolor
    ArgsParser
    funcs
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)