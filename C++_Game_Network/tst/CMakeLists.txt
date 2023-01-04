cmake_minimum_required( VERSION 3.0)
project(r-type_Unitest)

FetchContent_Declare(CRITERION GIT_REPOSITORY https://github.com/Snaipe/Criterion)
FetchContent_MakeAvailable(CRITERION)

SET(SOURCES
tst.cpp
)

set(INCLUDE_DIR
"${CMAKE_SOURCE_DIR}/src/shared/"
"${CMAKE_SOURCE_DIR}/src/shared/ThreadPool/"
"${CMAKE_SOURCE_DIR}/src/shared/ThreadPool/utils/"
"${CMAKE_SOURCE_DIR}/src/res/"
"${CMAKE_SOURCE_DIR}/src/res/include/"
"${CMAKE_SOURCE_DIR}/src/res/include/interface/"
"${CMAKE_SOURCE_DIR}/include/"
"${CMAKE_SOURCE_DIR}/src/server/include/"
"${CMAKE_SOURCE_DIR}/src/client/include/"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(r-type_server PRIVATE ${INCLUDE_DIR})