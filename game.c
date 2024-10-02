#include "game.h"
#include "game_aux.h"

/* FONCTIONS DE JEU */

game game_new(square* squares){
    if (squares == NULL) {
        fprintf(stderr, "Invalid pointer references!\n");
        exit(EXIT_FAILURE);
    }

    game g = (game)malloc(sizeof(struct game_s)); //Allocation dynamique d'une structure game_s 
    if (g == NULL) {
        fprintf(stderr, "Allocation failed !");
    }

    g->squares = (square*)calloc(HEIGHT*WIDTH, sizeof(square)); //Allocation dynamique d'un tableau de square 
    if (g->squares == NULL) {
        fprintf(stderr, "Allocation failed !");
    }

    for (uint i = 0; i < HEIGHT*WIDTH; i++) {
        g->squares[i] = squares[i]; //Initialisation du tableau de squares conformément au tableau 'squares' passé en paramètre
    }

    g->over = false; //La partie n'est pas terminée

    return g;
}

void game_set_square(game g, uint x, uint y, square s) { 
    usage_game(g);
    usage_coordinate_x(x);
    usage_coordinate_y(y);
    g->squares[y * WIDTH + x] = s; //On fait implicitement une conversion de coordonnées (x,y) en index pour le tableau à une dimension
    return;
}

square game_get_square(game g, uint x, uint y) { 
    usage_game(g);
    usage_coordinate_x(x);
    usage_coordinate_y(y);
    return g->squares[y * WIDTH + x]; 
}

char _square2str(square s) { 
    if (s == EMPTY)
        return ' ';
    else if (s == YELLOW)
        return 'o';
    else if (s == RED)
        return 'x';
    else
        return '?';
}

uint game_count_pawns_cons(game g, square s, uint x, uint y, char dir){
    usage_game(g); 
    usage_coordinate_x(x);
    usage_coordinate_y(y);

    uint count=1;

    switch(dir){
        case 'r': //Compte le nombre pions identiques consécutifs de se déplacant à droite
            while(x<WIDTH-1){
                if(game_get_square(g,x+1,y) == s){
                    x++;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
        case 'l': //Compte le nombre pions identiques consécutifs de se déplacant à gauche
            while(x>0){
                if(game_get_square(g,x-1,y) == s){
                    x--;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
        case 'b': //Compte le nombre pions identiques consécutifs en descendant
            while(y<HEIGHT-1){
                if(game_get_square(g,x,y+1) == s){
                    y++;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
        case '1': //Compte le nombre pions identiques consécutifs en montant sur la diagonale adjacente gauche
            while(x>0 && y>0){
                if(game_get_square(g,x-1,y-1) == s){
                    x--;
                    y--;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
        case '2': //Compte le nombre pions identiques consécutifs en descendant sur la diagonale adjacente droite
            while(x<WIDTH-1 && y<HEIGHT-1){
                if(game_get_square(g,x+1,y+1) == s){
                    x++;
                    y++;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
        case '3': //Compte le nombre pions identiques consécutifs en montant sur la diagonale adjacente droite
            while(x<WIDTH-1 && y>0){
                if(game_get_square(g,x+1,y-1) == s){
                    x++;
                    y--;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
        case '4': //Compte le nombre pions identiques consécutifs en descendant sur la diagonale adjacente gauche
            while(x>0 && y<HEIGHT-1){
                if(game_get_square(g,x-1,y+1) == s){
                    x--;
                    y++;
                    count++;
                }
                else{
                    break;
                }
            }
            break;
    }
    return count;
}

void game_play_move(game g, uint x, square s){ 
    usage_game(g);
    usage_coordinate_x(x);
    uint y;
    for(uint line=HEIGHT-1; line>=0; line--){ //On place le pion le plus bas possible dans la grille
        if(game_get_square(g,x,line) == EMPTY){
            game_set_square(g,x,line,s);
            y = line;
            break;
        }
    }
    uint nb_pawns_cons_line = game_count_pawns_cons(g,s,x,y,'r') + game_count_pawns_cons(g,s,x,y,'l') - 1;
    uint nb_pawns_cons_col = game_count_pawns_cons(g,s,x,y,'b');
    uint nb_pawns_cons_diag_a = game_count_pawns_cons(g,s,x,y,'1') + game_count_pawns_cons(g,s,x,y,'2') - 1;
    uint nb_pawns_cons_diag_b = game_count_pawns_cons(g,s,x,y,'3') + game_count_pawns_cons(g,s,x,y,'4') - 1;
    /*On souhaite vérifier qu'il existe une ligne de 4 pions consecutifs. Pour celà, on compte le nombre de pions consecutifs à gauche
      du pion que l'on vient d'insérer et également à droite, mais celà ne suffit pas. Par exemple si on forme une ligne en placant un
      pion ailleurs qu'à l'extrémité de la ligne (i.e oo*o ou o*oo), il faut compter non seulement le nombre de pions consecutifs à 
      gauche mais aussi à droite du pion nouvellement inséré. Pour les lignes verticales, il suffit de compter le nombre de pion
      consécutifs en se déplacant vers le bas car on place toujours un pion le plus bas possible. Le principe est le même pour vérifier
      sur les diagonales, on fait la somme des pions consecutifs descendant et remontant chaque diagonale.*/
    if(nb_pawns_cons_line >= 4 || nb_pawns_cons_col >= 4 || nb_pawns_cons_diag_a >= 4 || nb_pawns_cons_diag_b >= 4){
        game_print(g);
        if(s == YELLOW)
            printf("Le joueur 1 remporte la victoire !\n");
        else if(s == RED)
            printf("Le joueur 2 remporte la victoire !\n");
        g->over = true;
    }
}


uint game_get_nb_pawns(game g){ 
    usage_game(g);
    uint count = 0;
    for(uint y=HEIGHT-1; y>0; y--){
        for(uint x=0; x<WIDTH; x++){
            if(game_get_square(g,x,y) != EMPTY){
                count++;
            }
        }
    }
    return count;
}

bool game_is_over(game g){
    usage_game(g);
    return g->over;
}

void game_delete(game g) {
    usage_game(g);
    free(g->squares);
    free(g);
    return;
}

/* FONCTIONS USAGE */

void usage_game(game g){
    if(g == NULL){
        fprintf(stderr, "Adresse de pointeur invalide !\n");
        exit(EXIT_FAILURE);
    }
    return;
}

void usage_coordinate_x(uint x){
    if(x<0 || x>WIDTH-1){
        printf("%u\n", x);
        fprintf(stderr, "Coordonée 'x' invalide !\n");
        exit(EXIT_FAILURE);
    }
    return;
}

void usage_coordinate_y(uint y){
    if(y<0 || y>HEIGHT-1){
        fprintf(stderr, "Coordonée 'y' invalide !\n");
        exit(EXIT_FAILURE);
    }
    return;
}