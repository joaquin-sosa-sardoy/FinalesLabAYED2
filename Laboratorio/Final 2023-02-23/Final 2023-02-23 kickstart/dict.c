#include <stdlib.h>     /* malloc(), free()... */
#include <stdbool.h>    /* bool type           */
#include <assert.h>     /* assert()            */
#include "key_value.h"  /* key_t               */
#include "dict.h"       /* intarface           */
#include "string.h"

struct _s_dict {
    // COMPLETAR
    struct _node_t *head;
    unsigned int size;
};

// Internal structure
struct _node_t {
    key_t key;
    value_t value;
    struct _node_t *next;
};



struct _node_t * create_node(key_t k, value_t v) {
    struct _node_t *new_node = malloc(sizeof(struct _node_t));
    new_node->key = k;
    new_node->value = v;
    new_node->next = NULL;
    return new_node;
}

struct _node_t *destroy_node(struct _node_t *node) {
    node->key = key_destroy(node->key);
    node->value = value_destroy(node->value);
    free(node);
    node=NULL;
    return node;
}

static bool invrep(dict_t dict) {
    // COMPLETAR
    unsigned int lenght = 0u;
    struct _node_t *aux = dict->head;
    while(aux!=NULL){
        lenght = lenght + 1;
        aux = aux->next;
    }

    return(lenght == dict->size); //Estaria bien, salvo agregar un bool invrep= true.. luego invrep = leng..
}
// --- Interface functions ---

dict_t dict_empty(void) {
    // COMPLETAR
    dict_t var = NULL;
    var = malloc(sizeof(struct _s_dict));
    assert(var!=NULL);

    var->head = NULL;
    var->size = 0;

    return var;
}

dict_t dict_add(dict_t dict, key_t word, value_t def){
    // COMPLETAR
    assert(invrep(dict));
    if(dict_exists(dict, word)){
        struct _node_t *aux = dict->head;
        while(aux!=NULL){
            if(string_eq(aux->key, def)){
                aux->value = string_clone(word);
                return dict; //Que corte
            }
            aux = aux->next;
        }
    }
    struct _node_t *aux2 = create_node(string_clone(word), string_clone(def));
    aux2->next = dict->head; // Lo agregamos al principio, pero tambien puede ir al final...
    dict->head = aux2;

    dict->size++; //No olvidar agregar el aumento del size

    return dict;
    }

value_t dict_search(dict_t dict, key_t word) {
    // COMPLETAR
    assert(invrep(dict));
    if(!dict_exists(dict, word)){
        return NULL;
    }

    struct _node_t *aux= dict->head;
    while(aux!=NULL){
        if(string_eq(aux->key, word)){
            return string_clone(aux->value);
        }
        aux = aux->next;
    }

    return NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    // COMPLETAR
    assert(invrep(dict));
    bool existe = false;
    struct _node_t *aux = dict->head;
    
    while(aux!=NULL && !existe){
        existe = string_eq(aux->key, word);
        aux = aux->next;
    }
    
    return existe;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    return dict->size;
}

dict_t dict_remove(dict_t dict, key_t word) {
    // COMPLETAR
    assert(invrep(dict));
    struct _node_t *aux = dict->head;
    struct _node_t *prev = dict->head;
    if(!dict_exists(dict, word)){
        return dict;
    }
    while(aux!=NULL){
        if(string_eq(aux->key, word)){
            prev->next = aux->next;
            aux = destroy_node(aux);
            dict->size--;
            break; //Si no pongo el break, la proxima asignacion de aux seria seg fault o algo erroneo.
        }
        prev = aux;
        aux = aux->next;
    }

    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    for (struct _node_t *check=dict->head; check!=NULL; check=check->next) {
        fprintf(file, "key: ");
        key_dump(check->key, file);
        fprintf(file, "\n");
        fprintf(file, "value: ");
        value_dump(check->value, file);
        fprintf(file, "\n\n");
    }
}

dict_t dict_remove_all(dict_t dict) {
    // COMPLETAR
    struct _node_t *aux = dict->head;

    while(dict->head!=NULL){
        dict->head = aux->next;
        aux = destroy_node(aux);
        dict->size--;
    }

    return dict;
    
}

dict_t dict_destroy(dict_t dict) { 
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    free(dict);
    dict=NULL;
    assert(dict==NULL);
    return dict;
}

