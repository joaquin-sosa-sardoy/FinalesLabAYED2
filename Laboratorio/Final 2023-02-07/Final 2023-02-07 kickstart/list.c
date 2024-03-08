#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

struct _node {
        movement_t mov;
        struct _node *next;
};


static list_t create_node(movement_t movement){
    list_t new_node = calloc(1, sizeof(struct _node));
    if(new_node != NULL)
    {
        new_node->mov = movement;
        new_node->next = NULL;
    }
    return new_node;
}

list_t list_empty(void)
{
    return NULL;
}

list_t list_append(list_t src, movement_t movement)
{
        list_t result = NULL;
        list_t new_node = create_node(movement);
        if(src == NULL)
        {
            result = new_node;
        }
        else
        {
            list_t aux = src;
            result = src;
            while(aux->next != NULL)
            {
                aux = aux->next;
            }
            aux->next = new_node;
        }
        return (result);
}

list_t list_destroy(list_t list)
{
        list_t aux = list;
        while (aux != NULL) {
                list_t tmp = aux->next;
                free(aux);
                aux = tmp;
        }
        return (aux);
}

void list_show(list_t list)
{
        list_t aux = list;
        printf(".");
        while (aux != NULL) {
                printf("%s.", aux->mov == RIGHT ? "R" : "D");
                aux = aux->next;
        }
        printf("\n");
}

list_it_t list_get_iterator(list_t list)
{
    return list;
}

list_it_t list_iterator_next(list_it_t list_it)
{
    assert(list_it != NULL);
    return list_it->next;
}

movement_t list_iterator_elem(list_it_t list_it)
{
    assert (list_it != NULL);
    return list_it->mov;
}

bool list_iterator_end(list_it_t list_it)
{
    return list_it == NULL;
}