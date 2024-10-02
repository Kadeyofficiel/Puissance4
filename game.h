#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 7 //Largeur de la grille
#define HEIGHT 6 //Hauteur de la grille

typedef unsigned int uint;

typedef enum {
  EMPTY = 0, //Carré vide
  YELLOW = 1,  //Carré occupé par un pion jaune
  RED = 2,  //Carré occupé par un pion rouge
} square;

struct game_s {
    square* squares; //Tableau de 'square' pour représenter la grille
    bool over; //Boolean témoignant de l'état de la partie, initialisé sur false et la partie s'arrête lorsqu'il passe sur true
};

typedef struct game_s *game; //'game' est un pointeur sur une structure 'struct game_s'

/* FONCTIONS DE JEU */

game game_new(square* squares); //Initialise une partie à partir du tableau de pions passé en paramètre

void game_set_square(game g, uint x, uint y, square s); //Assigne un pion à une certaine position

square game_get_square(game g, uint x, uint y); //Récupère le pion à une certaine position

char _square2str(square s); //converti un square en un certain caractère pour pouvoir le représenter

uint game_count_pawns_cons(game g, square s, uint x, uint y, char dir); //Compte le nombre de pions identiques consecutifs suivant une certaine direction

void game_play_move(game g, uint x, square s); //Permet de faire descendre un pion dans une colonne

uint game_get_nb_pawns(game g); //Indique le nombre de pions présents sur la grille

bool game_is_over(game g); //Vérifie si la partie est terminée

void game_delete(game g); //Libère la mémoire associée à la strucutre game_s

/* FONCTIONS USAGE */

void usage_game(game g); //Vérifie la validité d'un pointeur sur un game_s

void usage_coordinate_x(uint x); //Vérifie la validité de la coordonnée x

void usage_coordinate_y(uint y); //Vérifie la validité de la coordonnée y

#endif