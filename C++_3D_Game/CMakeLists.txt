cmake_minimum_required(VERSION 3.16)
project(bomberman)

find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES_CPP ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_HPP ${CMAKE_SOURCE_DIR}/include/*.hpp)

file(GLOB_RECURSE SOURCESL_CPP ${CMAKE_SOURCE_DIR}/jsonlib/src/*.cpp)
file(GLOB_RECURSE INCLUDEL_HPP ${CMAKE_SOURCE_DIR}/jsonlib/include/*.hpp)

add_executable( bomberman 
    ${SOURCES_CPP}
    ${INCLUDE_HPP}
    ${SOURCESL_CPP}
    ${INCLUDEL_HPP}
)

target_include_directories(bomberman PRIVATE 
                        include/Entity/IA
                        include/Entity/Player
                        include/Graphic
                        include/Graphic/MyRaylib
                        include/Indi
                        include/interface
                        include/Map
                        include/Object
                        include/util
                        jsonlib/include
                        jsonlib/include/Exeption
                        jsonlib
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME} raylib)
