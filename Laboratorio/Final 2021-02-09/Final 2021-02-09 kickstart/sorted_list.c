#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"
#include "list.h"

struct _node{
   struct _node *next;
   elem_t elem;
   unsigned int size;
};

sorted_list_t sorted_list_empty()
{
    // COMPLETE HERE
   return NULL;
}

bool sorted_list_is_empty(sorted_list_t list)
{
	// COMPLETE HERE
   return (list->size == 0);
}

elem_t sorted_list_head(sorted_list_t list)
{
	// COMPLETE HERE
   return list->elem;
}

sorted_list_t sorted_list_append(sorted_list_t list, elem_t elem)
{
   // COMPLETE HERE
   struct _node *new = malloc(sizeof(struct _node));
   new->elem = elem;
   new->next = NULL;

   sorted_list_t aux = list;
   sorted_list_t prev = NULL;

   if(list == NULL){
      list = new;
      list->size++;
   }
   while(aux != NULL && aux->elem < elem){
      prev = aux;
      aux = aux->next;
   }
   if(prev == NULL){
      new->next = list;
      list = new;
   }
   
   new->next = aux;
   prev->next = new;
   

   list->size++;

   return list;
}

sorted_list_t sorted_list_tail(sorted_list_t list)
{
    // COMPLETE HERE
   assert(!sorted_list_empty(list));

   struct _node *new = list;
   list = list->next;
   list->size--;
   free(new);

   return list;
}

unsigned int sorted_list_length(sorted_list_t list)
{
   // COMPLETE HERE
   return list->size;
}

elem_t sorted_list_elem_at(sorted_list_t list, unsigned int index)
{
  // COMPLETE HERE
   assert(index<sorted_list_length(list));

  elem_t elem = 0;
  struct _node *aux = list;
  unsigned int i = 0;
  while(aux!=NULL && i != index){
   aux = aux->next;
   i++;
  }
  elem = aux->elem;

  return elem;
}

sorted_list_t sorted_list_take(sorted_list_t list, unsigned int num)
{
   // COMPLETE HERE
   unsigned int i = 0u;
   struct _node *aux = list;
   struct _node *newlist = malloc(sizeof(struct _node));
   while(aux!=NULL && i < num){
      newlist = sorted_list_append(newlist, aux->elem);
      aux = aux->next;
      i++;
   }
   
   return newlist;
}

sorted_list_t sorted_list_drop(sorted_list_t list, unsigned int num)
{
   // COMPLETE HERE
   assert(num>0);
   sorted_list_t aux = list;
   unsigned int i = 0u;
   while(aux!=NULL && i < num){
      aux = aux->next;
      i++;
   }
   struct _node *new = malloc(sizeof(struct _node));
   while(aux!=NULL){
   new = sorted_list_append(new, aux->elem);
   aux = aux->next;
   }

   return new;
}

void sorted_list_print(sorted_list_t list)
{
   // COMPLETE HERE
   struct _node *aux = list;
   while(aux!=NULL){
      printf("%d, ", aux->elem);
      aux = aux->next;
   }
}

sorted_list_t sorted_list_destroy(sorted_list_t list)
{
   // COMPLETE HERE 
   struct _node *aux = NULL;
   while(list->next!=NULL){
      aux = list;
      list = list->next;
      free(aux);
   }
   free(list);
   list = NULL;
   return list;
}
