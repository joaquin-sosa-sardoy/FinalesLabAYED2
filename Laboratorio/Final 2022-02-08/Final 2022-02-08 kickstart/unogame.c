#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    struct c_node *head;
    unsigned int size;
};
struct c_node{
    struct c_node *next;
    player_t player;
    card_t card;
};

typedef struct c_node *node_c;

static node_c create_node(card_t card, player_t player){
    node_c nodo;
    nodo = malloc(sizeof(struct c_node));

    nodo->card = card;
    nodo->next = NULL;
    nodo->player = player;

    return nodo;
}

unogame_t
uno_newgame(card_t card) {
    /*
     * [COMPLETAR]
     *
     */
    unogame_t uno;
    uno = malloc(sizeof(struct s_ugame));

    uno->head = create_node(card, -1);
    uno->size = 1;

    return uno;
}

card_t
uno_topcard(unogame_t uno) {
    /*
     * [COMPLETAR]
     *
     */
    assert(uno!=NULL);
    return uno->head->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    /*
     * [COMPLETAR]
     *
     */
    assert(uno!=NULL && c!=NULL);
    
    player_t playerAux = uno_nextplayer(uno);
    node_c new_card = create_node(c, playerAux); //para agregar, necesito un nodo que toma card, y jugador.. para jugador, dentro de una partida donde quiero agregar una carta, necesito saber cual es el proximo

    new_card->next = uno->head;
    uno->head = new_card; // Esta bien, sino el head estaria en uno siempre, pero en realidad el new_card es el primer nodo.
    uno->size = uno->size + 1;

    return uno;
}

unsigned int
uno_count(unogame_t uno) {
    return uno->size;
}

bool
uno_validpile(unogame_t uno) {
    /*
     * [COMPLETAR]
     *
     */
    assert(uno!=NULL);
    bool valid = true;
    //idea ; recorrer todos los nodos con 2 punteros viendo que sean cartas compatiles con card_compatible(prev.card, aux.card)
    struct c_node *aux = uno->head;
    struct c_node *prev = uno->head;

    while(aux!=NULL && valid){
        valid = card_compatible(aux->card, prev->card);
        prev = aux;
        aux = aux->next;
    }
    valid = valid && uno->head !=NULL;

    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    assert(uno!=NULL);
    return card_get_color(uno->head->card);
}

player_t
uno_nextplayer(unogame_t uno) {
    /*
     * [COMPLETAR]
     *
     */
    assert(uno!=NULL);
    
    player_t next_player = -1 ;
    if(uno != NULL){
        next_player = (uno->size % 3)  ;
    }
    return next_player;
}



card_t *
uno_pile_to_array(unogame_t uno) {
    /*
     * [COMPLETAR]
     * Devuelve un array con las cartas en el orden que se jugaron:
     * O sea, se empieza en array[size]...array[1] => Eso se hace array[size - 1, -2 , -3...size] hasta llegar a array[0]
     */
    assert(uno!=NULL);
    card_t *array = NULL;
    array = calloc(uno->size, sizeof(card_t));
    struct c_node *aux = uno->head;

    unsigned int size = uno->size-1;

    for(unsigned int i = 0; i < uno->size ; i++){
        array[size - i] = aux->card;
        aux = aux->next;
    }

    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    /*
     * [COMPLETAR]
     *
     */
    struct c_node *aux = uno->head;
    struct c_node *prev = uno->head;
    while(aux!=NULL){
        prev = aux;
        aux = aux->next;
        free(prev);
       
    }
    free(uno);
    uno = NULL;
    return uno;
}

