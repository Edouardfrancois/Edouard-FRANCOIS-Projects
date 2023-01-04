# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
# Notre projet est étiqueté libhello
project(lib_res)

set(CMAKE_CXX_FLAGS "-Wall -W -ansi -pedantic -g")

# Crée des variables avec les fichiers à compiler
set(SRCS
    interface/ISocket.cpp
    Client.cpp
    Serveur.cpp
    )

set(HEADERS_DIR
"${CMAKE_SOURCE_DIR}/src/res/include/interface/"
"${CMAKE_SOURCE_DIR}/src/res/include/"
"${CMAKE_SOURCE_DIR}/src/res/"
)

add_library(lib_res ${SRCS})

target_include_directories(lib_res PUBLIC ${HEADERS_DIR})
