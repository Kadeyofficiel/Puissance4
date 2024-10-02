#include <stdlib.h>
#include "game.h"


void game_print(game g) {
    usage_game(g);
    // ligne 1 : 0 1 2 ... WIDTH-1
    printf("   ");
    for (uint x = 0; x<WIDTH; x++) {
        printf("%u ", x);
    }
    printf("\n");

    // ligne 2 : - - - - - - -
    printf("   ");
    for (uint x = 0; x<WIDTH; x++) {
        printf("- ");
    }
    printf("\n");

    // affichage du tableau
    for (uint y=0; y<HEIGHT; y++) {
        printf("   ");
        for (uint x=0; x<WIDTH; x++) {
            printf("%c ", _square2str(game_get_square(g, x, y)));
        }
        printf("\n");
    }
    // dernière ligne : - - - - - - -
    printf("   ");
    for (uint x = 0; x<WIDTH; x++) {
        printf("- ");
    }
    printf("\n");

    return;
}

game game_empty(void){
    square s[] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    return game_new(s);
}

game game_test(void){
    square s[] = {YELLOW, RED, YELLOW, RED, RED, YELLOW, YELLOW,
                  RED, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED,
                  YELLOW, RED, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
                  YELLOW, YELLOW, YELLOW, RED, RED, YELLOW, RED,
                  YELLOW, RED, YELLOW, YELLOW, YELLOW, YELLOW, RED,
                  YELLOW, YELLOW, RED, YELLOW, RED, RED, YELLOW};
    return game_new(s);
}