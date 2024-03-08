#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line {
    /*
     * COMPLETAR
     *
     */
    struct _s_node *head;
    unsigned int size;
};

struct _s_node{
    domino tile;
    struct _s_node *next;
};

typedef struct c_node *_s_node;

struct _s_node *create_node(domino f){
    struct _s_node *aux = NULL;
    aux = malloc(sizeof(struct _s_node));
    assert(aux!=NULL);
    aux->next = NULL;
    aux->tile = f;

    return aux;
}

domino_line line_new(domino first) {
    /*
     * COMPLETAR
     *
     */
    domino_line aux = NULL; //si solo ponia aux.head = f... estaria agregando solo un numero
    aux = malloc(sizeof(struct _s_line));
    aux->head = create_node(first); //aca debo crear el nodo porque sino estaria poniendo solo 2 numeros
    aux->size = 1;

    return aux;
}

domino_line line_add(domino_line line, domino t) {
    /*
     * COMPLETAR
     *
     */
    struct _s_node *aux = line->head;
    while(aux->next!=NULL){
        aux = aux->next;
    }
    struct _s_node *new_node = create_node(t);
    aux->next = new_node;

    line->size = line->size + 1;

    return line;
}

unsigned int line_length(domino_line line) {
    return line->size;
}

bool line_n_correct(domino_line line, unsigned int n) {
    /*
     * COMPLETAR
     *
     */
    bool correct = false;
    struct _s_node *aux = line->head;
    struct _s_node *prev = line->head;
    unsigned int lenght = 0u;

    if(n == 0 && (line_length(line) == 1)){
        correct = true;
    }

    if(n!=line_length(line)-1){
        if(n!=lenght){
            while(aux->next != NULL && lenght != n){
                lenght++;
                prev = aux;
                aux = aux->next;
            }

            if(domino_matches(aux->tile, prev->tile) && domino_matches(aux->tile, aux->next->tile)){
                correct = true;
            }
        }
    }

    if(n == line_length(line)-1){
        while(aux->next != NULL && lenght != n){
                prev = aux;
                aux = aux->next;
            }

            if(domino_matches(aux->tile, prev->tile) && domino_matches(aux->tile, aux->next->tile)){
                correct = true;
            }
        }
    //CORREGIR ESTA

    return correct;
}
    

int line_total_points(domino_line line) {
    /*
     * COMPLETAR
     *
     */
    assert(line!=NULL);
    int res = 0u;
    struct _s_node *aux = line->head;
    while(aux!=NULL){
        res = res + (domino_down(aux->tile) + domino_up(aux->tile));
        aux = aux->next;
    }

    return res;
}

domino * line_to_array(domino_line line) {
    /*
     * COMPLETAR
     *
     */
    domino *array = NULL;
    array = malloc(sizeof(struct _s_line)*line->size);
    assert(array!=NULL);
    struct _s_node *aux = line->head;

    for(unsigned int i = 0u; i < line_length(line); i++){
        array[i] = aux->tile;
        aux = aux->next;
    }

    return array;
}

void line_dump(domino_line line) {
    domino *array=line_to_array(line);
    for (unsigned int i=0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    /*
     * COMPLETAR
     *
     */
    struct _s_node *aux = NULL;
    while(line->head != NULL){
        aux = line->head;
        line->head = line->head->next;
        domino_destroy(aux->tile);
    }
    free(line);
    line = NULL;
    return line;
}

