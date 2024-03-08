#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct s_node {
    stack_elem *chunk;
    int used;
    struct s_node *next;
};

struct _s_stack {
   struct s_node *top;
   unsigned int size;
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *aux=s->top;
    if (aux!=NULL) {
        //COMPLETAR
        valid = valid && aux->chunk != NULL; //porque toma una stack s que debe ser != NULL y la estrucutra tiene el campo chunk, independientemente de si tiene algo o no, debe tener el malloc, por eso aux.chunk!=NULL
        valid = valid && aux->used <= CHUNK_CAPACITY;
    }
    return valid;
}

static bool
invrep(stack s) {
    bool invrep = true;
    invrep = (s != NULL);
   struct s_node *aux = s->top;
   unsigned int length = 0u;

   while(aux!=NULL){
     length = length + aux->used;
     aux = aux->next;
   }
   invrep = invrep && length == s->size;

   return (invrep && valid_chunks(s));
}

static struct s_node *
create_node(void) {
   struct s_node *newNode = NULL;
   newNode = malloc(sizeof(struct s_node));
   assert(newNode != NULL);
   newNode->next = NULL;
   newNode->used = 0;
   newNode->chunk = malloc(sizeof(stack_elem)*CHUNK_CAPACITY);

   return newNode;
}


static struct s_node *
destroy_node(struct s_node *node) {
  free(node->chunk);
  free(node);
  node = NULL;

    return node;
}

stack stack_empty(void) {
    struct _s_stack *stack = NULL;
    stack = malloc(sizeof(struct _s_stack));
    assert(stack!=NULL);
    stack->size = 0;
    stack->top = create_node();

    return stack;
}


stack stack_push(stack s, stack_elem e) {
    struct s_node *aux = s->top;
    if(aux->used == CHUNK_CAPACITY){
        s->top = create_node();
        s->top->next = aux;
    }
    // si esta lleno hago eso.. creo nodo nuevo
    //sino.. debo agregar un elemento en chunk
    aux->chunk[aux->used] = e;
    aux->used++;
    s->size++;

    return s;
}


stack stack_pop(stack s) {
   struct s_node *aux = s->top;
   while(aux!=NULL){
    aux = aux->next;
   }
    aux->used--;
    s->size--;
    if(s->size > 0 && aux->used == 0){
        destroy_node(aux);
    }

   return s;
}


unsigned int stack_size(stack s) {
    assert(invrep(s));
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    *top = s->top->chunk[s->top->used];
}

bool stack_is_empty(stack s) {
    return s->size == 1;
}

stack_elem *stack_to_array(stack s) {
  stack_elem *array = NULL;
  array = malloc(sizeof(stack_elem)*s->size);
  struct s_node *aux = s->top;

  int pos = s->size - 1; // O SEA, va desde el nodo N hasta el 0..

    if(s->size == 0){
        return array;
    }

    while(aux != NULL){
        for(int j = aux->used -1; j<=0; --j){
            array[pos] = aux->chunk[j];
            --pos;
        }
        aux = aux->next;
    }
}


stack stack_destroy(stack s) {
    struct s_node *i = s->top;
    struct s_node *next;
    while(i!=NULL){
        next = i->next;
        free(i);
        i = next;
    }
    return NULL;
}