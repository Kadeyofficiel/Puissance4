#version minimale de cmake nécessaire
cmake_minimum_required(VERSION 2.6)

#nom du projet
project (Puissance4 C)

#activation des tests
enable_testing()
include(CTest)

#positionne la variable
set(CMAKE_C_FLAGS "-O0 -std=c99 -g -Wall --coverage")

#------ EXECUTABLES ET BIBLIOTHEQUE ------#
add_executable(game_main game_main.c)

target_link_libraries(game_main game)

add_library(game game.c game_aux.c)
#les dépendances sont calculées automatiquement
#----------------------------------------#