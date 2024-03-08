#include "dna.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct _node {
    nucleobase_t elem;
    struct _node *next;
};

struct _dna_t
{
    struct _node* head;
    unsigned int lenght;
};

static struct _node *destroy_node(struct _node *nodo);

static struct _node* single_node(nucleobase_t e)
{
    struct _node *node = calloc(1, sizeof(struct _node));
    assert(node != NULL);
    node->elem = e;
    node->next = NULL;
    return (node);
}

dna_t dna_T()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    assert(res!=NULL);

    res->head = single_node(T);
    res->lenght = 1;

    return res;
}

dna_t dna_C()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    assert(res!=NULL);

    res->head = single_node(C);
    res->lenght = 1;
    return res;
}

dna_t dna_A()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    assert(res!=NULL);

    res->head = single_node(A);
    res->lenght = 1;
    return res;
}

dna_t dna_G()
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
    res = malloc(sizeof(struct _dna_t));
    assert(res!=NULL);

    res->head = single_node(G);
    res->lenght = 1;
    return res;
}


dna_t dna_join(dna_t first, dna_t second)
{
    dna_t res = NULL;
    /** COMPLETAR ACÁ */
      /*
    Concatena el segundo DNA al final del primer DNA. Modifica el primer argumento.
 *        El segundo argumento no se debe modificar, se crea una copia
 *        de los elementos del segundo DNA que se concatenan al primero
 * 
 * @param first Primera cadena de DNA. Este argumento se modifica
 * @param second Segunda cadena de DNA a concatenar. Este argumento NO SE MODIFICA
 * @return dna_t cadena concatenada
    */
   assert(first!=NULL && second!=NULL);

   res = malloc(sizeof(struct _dna_t));
   assert(res!=NULL);

   res->head = NULL;

    if(first->head == NULL){
        res->head = second->head;
    }
    else {
        struct _node *aux = first->head;
        while(aux != NULL){
            aux = aux->next;
        }
        aux = second->head;
        res->head = first->head;
        destroy_node(aux);
    }

    res->lenght = first->lenght + second->lenght; 

    return res;
}

unsigned int dna_length(dna_t dna)
{
    /* unsigned int res = 0u; ESTO ESTA BIEN PERO NO ES CONSTANTE
     COMPLETAR ACÁ 
    assert(dna!=NULL);
    struct _node *aux = dna->head;
    while(aux != NULL){
        res++;
        aux = aux->next;
    }
    */ 
    unsigned int res = 0u; 
    res = dna->lenght; 

    return res;
}

void dna_print(dna_t dna)
{
    /** COMPLETAR ACÁ */
    assert(dna!=NULL);
    struct _node *aux = dna->head;
    while(aux!=NULL){
        printf(" %c ", aux->elem);
        aux = aux->next;
    }

}

bool dna_is_prefix(dna_t first, dna_t second)
{
    bool is_prefix = false;
    /** COMPLETAR ACÁ */
    struct _node *aux1 = first->head;
    struct _node *aux2 = second->head;
    unsigned int count= 0u; 
    if(first->lenght <= second->lenght){
    while(aux1 != NULL ){
        if(aux1->elem == aux2->elem ){
            count++;
        }
        aux1= aux1->next;
        aux2= aux2->next;
    }
    is_prefix= (count == first->lenght);
    }
    return is_prefix;
}

bool dna_is_equal(dna_t first, dna_t second)
{
    bool is_equal = false; // modifique a true porque esto me decia el enunciado = FALSE

    is_equal = (first->lenght == second->lenght) && (dna_is_prefix(first,second));

    return is_equal;
}

dna_t *dna_cut(dna_t dna, unsigned int count)
{
    dna_t* res = NULL;
    /** COMPLETAR ACÁ */
    /**
    * @brief_Corta el DNA en dos segmentos disjuntos, el primero de longitud ‘count’. 
    *        Concatenando ambos segmentos se obtiene el DNA original. 
    *        Se asume que ‘count’ es mayor estricto que 0 y 
    *        menor estricto que la longitud del primer DNA.
    *        Los dos segmentos se devuelven en un arreglo de tamaño 2.
    * 
    * @param_dna DNA para cortar
    * @param_count Cantidad de elementos a cortar
    * @return_dna_t* Arreglo de tamaño 2 con los 2 segmentos
    */
   assert(dna!=NULL);
   assert(count>0 && count < dna->lenght);
   for(unsigned int i=0u; i < count; i++){
        res[i] = malloc(sizeof(struct _dna_t));
        assert(res[i] != NULL);
        res[i]->head = NULL;
        res[i]->lenght = 0;
   }

   struct _node *aux = dna->head;
   unsigned int c = 0u;
   while(aux!=NULL && c < count){
    res[0]->head = single_node(aux->elem);
    res[0]->head = res[0]->head->next;
    c++;
    aux = aux->next;
   }

//sigo con mi iteracion pero ya hice la primera parte pues c < count
   while(aux!=NULL){
    res[1]->head = single_node(aux->elem);
    res[1]->head = res[1]->head->next;
    aux = aux->next;
   }

    return res;
}

dna_t dna_destroy(dna_t dna)
{
    /** COMPLETAR ACÁ */
    //Itero sobre dna raramente :v
    assert(dna!=NULL);
    struct _node *aux = NULL;
    while(aux!=NULL){
        aux = dna->head;
        dna->head = dna->head->next;
        aux = destroy_node(aux);
    }
    free(dna);
    dna=NULL;

    return dna;
}
// FUNCION AUXILIAR PARA DNA DESTROY
static struct _node *destroy_node(struct _node *nodo){
    assert(nodo!=NULL);
    nodo->next = NULL;
    free(nodo);
    nodo = NULL;

    return nodo;
}


/*
nucleobase_t *nucleo_to_array(dna_t d){
    nucleobase_t *a=NULL; 
    unsigned int length = dna_length(d); 
    unsigned int i = 0;
    a = calloc(length , sizeof(nucleobase_t));
    struct _node *aux = d->head; 
    while(length != i) {
        a[i] = aux->elem;
        aux=aux->next; //maybe s= stack_pop(s);  
        i++;
    }
    return a;
}
*/
