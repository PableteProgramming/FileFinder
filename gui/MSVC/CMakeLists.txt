project(FileFinderGui)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)

set(RC_FILES
    ${RC_DIR}/filefinder.rc
)

set(SRC_FILES
    ${SRC_DIR}/filefinder.cpp
    ${RC_FILES}
)

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INC_DIR}
    ${RC_DIR}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    funcs
)