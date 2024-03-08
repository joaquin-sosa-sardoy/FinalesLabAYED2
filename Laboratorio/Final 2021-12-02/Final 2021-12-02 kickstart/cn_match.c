#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cn_match.h"
#include "card.h"

struct _s_match {
  /*
  * COMPLETAR
  *
  */
  struct _s_match *next;
  card carta;
};

cn_match match_new(void) {
  /*
  * COMPLETAR
  *
  */
  return NULL;
}

cn_match match_add(cn_match match, card c) {
  /*
  * COMPLETAR
  *
  */
  struct _s_match *aux = match;
  while(aux->next != NULL){
    aux = aux->next;
  }
  struct _s_match *new = NULL;
  new = malloc(sizeof(struct _s_match));
  new->carta = c;
  new->next = NULL;

  aux->next = new;

  return match;
}

unsigned int match_size(cn_match match) {
  /*
  * COMPLETAR
  *
  */
 unsigned int res = 0u;
 struct _s_match *aux = match;
 while(aux!=NULL){
  res = res + 1;
  aux = aux->next;
 }
  return res;

}

unsigned int match_length(cn_match match) {
  /*
  * COMPLETAR
  *
  */
  if(!is_match_correct(match)){
    return 0;
  }
  
  return match_size(match) / 2;
}

bool is_match_correct(cn_match match) {
  /*
  * COMPLETAR
  *
  */
 bool esPar = ((match_size(match) % 2) == 0);
 bool empiezaelUno = card_number(match->carta) == 1;
 bool correct = false;

 struct _s_match *aux=match;
 while(aux!=NULL && empiezaelUno && esPar && !correct){
  if(card_number(aux->carta) != 1 || card_number(aux->next->carta) != 2){
    correct = false;
  }
  aux = aux->next;
 }

 return correct && esPar && empiezaelUno;
}

unsigned int winner_total_points(cn_match match) {
  /*
  * COMPLETAR
  * tips:
  * * recordar que si is_match_correct es falso esto retorna 0
  *
  */
  if(!is_match_correct(match)){
    return 0;
  }
  unsigned int res=0u;
  struct _s_match *aux = match;

  while(aux->next!=NULL){
    if(card_color(aux->carta) == card_color(aux->next->carta)){
      res = res + 1;
    }
    if(card_number(aux->carta) == card_number(aux->next->carta)){
      res = res + 10;
    }

    aux = aux->next;
  }
  return res;
}

card * match_to_array(cn_match match) {
  /*
  * COMPLETAR
  *
  */
 card *array = NULL;
 array=malloc(sizeof(struct _s_match)* match_size(match));
 assert(array!=NULL);
 struct _s_match *aux = match;

 for(unsigned int i = 0u; i < match_size(match); i++){
  array[i] = aux->carta;
  aux = aux->next;
 }

 return array;
}

void match_dump(cn_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

cn_match match_destroy(cn_match match) {
  /*
  * COMPLETAR
  *
  */
 struct _s_match *aux = match;
 while(aux!=NULL){
  match = match->next;
  card_destroy(aux->carta);
  free(aux);
  aux = NULL;
  aux = match;
 }
 
 return match;
}
