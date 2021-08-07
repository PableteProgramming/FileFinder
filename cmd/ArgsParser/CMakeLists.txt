project(ArgsParser)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(PLAT_SRC_FILES ${SRC_DIR}/MSVC/dllmain.cpp)
else()
    set(PLAT_SRC_FILES)
endif()

set(SRC_FILES
    ${SRC_DIR}/argsparser.cpp
    ${PLAT_SRC_FILES}
)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${INC_DIR}
)