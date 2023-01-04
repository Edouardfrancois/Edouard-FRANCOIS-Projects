cmake_minimum_required(VERSION 3.0)

project(r-type_client)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
set(CMAKE_CXX_FLAGS "-Wall -W -ansi -pedantic -g ")

find_package(SFML REQUIRED)
if (APPLE)
    find_package(UUID REQUIRED)
endif()
SET(SOURCES
main.cpp
Lobby.cpp
GameManager.cpp
../../shared/HandleServer.cpp
ManageMessageFromServer.cpp
../../shared/FactoryMonster.cpp
../../shared/SFML/Asset.cpp
../../shared/ManageRegistry/ManageRegistry.cpp
)

add_executable (
${PROJECT_NAME} ${SOURCES}
)

set(HEADERS_DIR
"${CMAKE_SOURCE_DIR}/src/shared/"
"${CMAKE_SOURCE_DIR}/src/shared/SFML"
"${CMAKE_SOURCE_DIR}/src/shared/ecs"
"${CMAKE_SOURCE_DIR}/src/shared/ThreadPool/"
"${CMAKE_SOURCE_DIR}/src/shared/ThreadPool/utils/"
"${CMAKE_SOURCE_DIR}/src/res/"
"${CMAKE_SOURCE_DIR}/src/res/include/"
"${CMAKE_SOURCE_DIR}/src/res/include/interface/"
"${CMAKE_SOURCE_DIR}/src/client/include/"
)

target_include_directories(r-type_client PRIVATE ${HEADERS_DIR})

set(INCLUDE_DIR
"${CMAKE_SOURCE_DIR}/src/shared/"
"${CMAKE_SOURCE_DIR}/src/shared/ecs"
"${CMAKE_SOURCE_DIR}/src/shared/SFML"
"${CMAKE_SOURCE_DIR}/src/shared/ThreadPool/"
"${CMAKE_SOURCE_DIR}/src/shared/ThreadPool/utils/"
"${CMAKE_SOURCE_DIR}/src/res/"
"${CMAKE_SOURCE_DIR}/src/res/include/"
"${CMAKE_SOURCE_DIR}/src/res/include/interface/"
"${CMAKE_SOURCE_DIR}/include/"
"${CMAKE_SOURCE_DIR}/src/shared/SFML/"
"${CMAKE_SOURCE_DIR}/src/shared/ManageRegistry/"
)
find_package(Threads REQUIRED)

if(APPLE)
set(LIBRAIRIES
${SFML_LIBRARY}
${UUID_LIBRARY}
lib_res
Threads::Threads
)
else()
set(LIBRAIRIES
${SFML_LIBRARY}
uuid
lib_res
Threads::Threads
)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${LIBRAIRIES})