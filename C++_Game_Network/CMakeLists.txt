cmake_minimum_required( VERSION 3.0)
include(FetchContent)
set(CMAKE_BUILD_TYPE Release) #remplacer Release par Debug pour debug
project(r-type)
# add_subdirectory("${CMAKE_SOURCE_DIR}/lib")
# add_subdirectory("${CMAKE_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})


# add_test(NAME my_tst WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tst)

FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML)
FetchContent_MakeAvailable(SFML)

enable_testing()

add_subdirectory("${CMAKE_SOURCE_DIR}/src/res/src/") # librairy
add_subdirectory("${CMAKE_SOURCE_DIR}/src/client/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/server/src")
add_subdirectory("${CMAKE_SOURCE_DIR}/tst")
