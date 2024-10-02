#ifndef __GAME_AUX_H__
#define __GAME_AUX_H__

#include "game.h"

/* FONCTIONS DE JEU AUXILIAIRES */

void game_print(game g); //Affiche l'état de la partie sur la sortie standard

game game_empty(void); //Génère une partie vide (chaque square assigné à EMPTY)

game game_test(void); //Génère une partie de test avec une configuration particulière

#endif