/* prenom nom numéro_étudiant
* Je déclare qu'il s'agit de mon propre travail */

#include "game.h"
#include "game_aux.h"

/* FONCTION PRINCIPALE DE JEU */

int main(int argc, char *argv[]) {
    if (argc > 1) {
        printf("Error, to much parameters");
        return EXIT_SUCCESS;
    }

    game g;

    if (argc == 1) {
        g = game_empty();
    }
    while (!game_is_over(g)) {
        game_print(g);
        
        uint nb_pawns = game_get_nb_pawns(g);
        square pawn;

        if(nb_pawns%2 == 0){
            printf("JOUEUR 1 (o) : ");
            pawn = YELLOW;
        }
        else{
            printf("JOUEUR 2 (x) : ");
            pawn = RED;
        }
        
        int entry;
        char cmd;
        int col;
        entry = scanf(" %c", &cmd);
        if(entry == 1){
            switch(cmd){
                case 'r':
                    printf("Redémarrage de la partie...\n");
                    g = game_empty();
                    break;
                case 'q':
                    printf("Arrêt de la partie...\n");
                    game_delete(g);
                    return EXIT_SUCCESS;
                    break;
                default:
                    col = (cmd - '0');
                    if(col >= 0 && col < WIDTH)
                        game_play_move(g, col, pawn);
                    else
                        printf("Commande invalide !\n");
                    break;
            }
        }
    }
    game_delete(g);
}