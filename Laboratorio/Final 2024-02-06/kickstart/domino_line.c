#include "domino_line.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "domino.h"

struct _s_line
{
     struct _line_node *head;
     unsigned int size;
};

struct _line_node
{
     struct _line_node *next;
     domino tile;
};

struct _line_node *create_node(domino t){
    struct _line_node *newNode = NULL;
    newNode = malloc(sizeof(struct _line_node));
    assert(newNode!=NULL);
    newNode->next = NULL;
    newNode->tile = t;

    return newNode;
}

domino_line line_new(domino first)
{
    /*
     * COMPLETAR
     *
     */
    domino_line tile = NULL;
    tile = malloc(sizeof(domino_line));
    assert(tile!=NULL);
    tile->size = 1;
    tile->head = create_node(first);

    return tile;
}

domino_line line_add(domino_line line, domino t)
{
    /*
     * COMPLETAR
     *
     *
    struct _line_node *new = create_node(t);
    if(line->head == NULL){
        line->head = new;
        return line; // ESTO ME DABA MEMORY LEAKS
    }*/
    struct _line_node *aux = line->head;
    while(aux->next!=NULL){
        aux = aux->next;
    }
    aux->next = create_node(t);
    line->size ++;
    
    return line;
}

unsigned int line_length(domino_line line)
{
     return line->size;
}

bool line_n_correct(domino_line line, unsigned int n)
{
    /*
     * COMPLETAR
     *
     */
     bool correct = false;
     unsigned int i = 0u;
     struct _line_node *aux = line->head;
     struct _line_node *prev = line->head;
    if(n == 0 && aux->next!=NULL){
        if(domino_matches(prev->tile, aux->next->tile)){
            correct = true;
        }
    }else if(n == line_length(line)-1){
        while(aux->next!=NULL){
            prev = aux;
            aux = aux->next;
        }

        if(domino_matches(prev->tile, aux->tile)){
            correct = true;
        }
    }else{
        while(aux->next!=NULL && !correct && i < n){
            i++;
            prev = aux;
            aux = aux->next;
        }
        if(domino_matches(prev->tile, aux->tile) && domino_matches(aux->tile, aux->next->tile)){
                correct = true;
            }
    }
     return correct;
}

int line_total_points(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
     int puntos = 0;
     struct _line_node *aux = line->head;
     while(aux!=NULL){
        puntos = puntos + domino_up(aux->tile) + domino_down(aux->tile);
        aux = aux->next;
     }

     return puntos;
}

domino* line_to_array(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
     unsigned int size = line_length(line);
     domino *array = malloc(sizeof(domino)*size);
     struct _line_node *aux = line->head;
     for(unsigned int i = 0u; i < size; i++){
        array[i] = aux->tile;
        aux = aux->next;
     }

     return array;
}

void line_dump(domino_line line)
{
    domino* array = line_to_array(line);
    for (unsigned int i = 0u; i < line_length(line); i++)
    {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
     struct _line_node *aux = NULL;

     while(line->head!=NULL){
        aux = line->head; 
        line->head = line->head->next;
        free(aux);
     }
     free(line);
     line = NULL;
     
     return line;
}

line_iterator line_iterator_begin(domino_line line)
{
    /*
     * COMPLETAR
     *
     */
     line_iterator new = line->head;
     return new;
}

domino line_iterator_get(line_iterator lit)
{
    /*
     * COMPLETAR
     *
     */
     return lit->tile;
}

line_iterator line_iterator_next(line_iterator lit)
{
    /*
     * COMPLETAR
     *
     */
     if(lit->next == NULL){
        return NULL;
     }
     else{
        lit = lit->next;
     }

     return lit;
}

bool line_iterator_end(line_iterator lit)
{
    /*
     * COMPLETAR
     *

     Devuelve “true” si ya se ha alcanzado el final
    de la lista, “false” en caso contrario. Por final
    de la lista entendemos que ya no hay
    elementos por procesar. Es decir para la lista
    [1:2, 2:2, 3:0] si el iterador “lit” está apuntado
    a 3:0 esta función devolverá FALSE, pues
    existe un elemento todavía por procesar.

     */
     
    bool is = false;
    if(lit->tile != NULL){
        is = false;
    }else{
        is = true;
    }

    return is;
}
