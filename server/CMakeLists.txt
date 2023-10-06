# Spécifie la version minimale de CMake requise
cmake_minimum_required(VERSION 3.5)

# Nomme votre projet et spécifie le langage C
project(server)

# include files
include_directories(include)

# src files
set(SOURCES
    src/main.cpp
    src/server.cpp
    src/logs.cpp
)

add_executable(server ${SOURCES})

# Lier la bibliothèque ws2_32 (uniquement sous Windows)
target_link_libraries(server PRIVATE ws2_32)

# Exemple : Activer les avertissements et activer le standard C11
target_compile_options(server PRIVATE -Wall -std=c11)