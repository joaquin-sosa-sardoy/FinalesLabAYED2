#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdbool.h>
#include <assert.h>

typedef int elem_t;

typedef struct _node *sorted_list_t;

sorted_list_t sorted_list_empty();
/* 
    returns an empty sorted_list
*/

bool sorted_list_is_empty(sorted_list_t list);
/* 
    returns true if sorted_list list is empty
    False otherwise
*/

sorted_list_t sorted_list_append(sorted_list_t list, elem_t elem);
/* 
    appends element e to sorted_list list. 
    list must be sorted after insertion
*/

elem_t sorted_list_head(sorted_list_t list);
/* 
    returns first list element. This method just return head. It don't modify
    list
*/

sorted_list_t sorted_list_tail(sorted_list_t list);
/* 
    returns a list with first element deleted
*/

unsigned int sorted_list_length(sorted_list_t list);
/* 
    returns list length
*/

elem_t sorted_list_elem_at(sorted_list_t list, unsigned int index);
/* 
    returns list element at position index. index must be a valid number (
        0 <= index <= sorted_list(length)
    )
*/

sorted_list_t sorted_list_take(sorted_list_t list, unsigned int num);
/* 
    takes first N elements of list l. N must be lower than list_length(l)
    It shouldn't modify list, it must return a new list
*/

sorted_list_t sorted_list_drop(sorted_list_t list, unsigned int num);
/* 
    drops first N elements of list l. N must be lower than list_length(l)
    It shouldn't modify list, it must return a new list
*/

void sorted_list_print(sorted_list_t list);
/*
    prints list elements
*/

sorted_list_t sorted_list_destroy(sorted_list_t list);
/*
    free memory and resources allocated by list
*/

#endif
