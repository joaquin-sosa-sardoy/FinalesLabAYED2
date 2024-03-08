#include <stdlib.h>
#include <assert.h>
#include "fence.h"

struct _fence_t {
    fence_t next;
    type_t type;
    unsigned int size;
};

fence_t fence_P(){
    struct _fence_t *fence = NULL;
    fence = malloc(sizeof(struct _fence_t));
    assert(fence!=NULL);
    fence->next = NULL;
    fence->size = 1;
    fence->type = P;

    return fence;
}

fence_t fence_add_P(fence_t fence){
    struct _fence_t *newfence = NULL;
    newfence = malloc(sizeof(struct _fence_t));
    assert(newfence!=NULL);
    newfence->next = NULL;
    newfence->type = P;

    if(fence == NULL){
        return newfence;
    }

    struct _fence_t *aux = fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = newfence;
    fence->size++;

    return fence;
}



fence_t fence_add_A(fence_t fence){
    struct _fence_t *newfenceA = NULL;
    newfenceA = malloc(sizeof(struct _fence_t));
    assert(newfenceA != NULL);
    newfenceA->next = NULL;
    newfenceA->type = A;

    if(fence == NULL){
        return newfenceA;
    }
    
    struct _fence_t *aux = fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = newfenceA;
    fence->size = fence->size + 1;

    return fence;
}

fence_t fence_add_H(fence_t fence){
    struct _fence_t *newfenceH = NULL;
    newfenceH = malloc(sizeof(struct _fence_t));
    assert(newfenceH != NULL);
    newfenceH->next = NULL;
    newfenceH->type = H;

    if(fence == NULL){
        return newfenceH;
    }

    struct _fence_t *aux=fence;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = newfenceH;
    fence->size++;

    return fence;
}



fence_t fence_add_T(fence_t fence){
    struct _fence_t *new = malloc(sizeof(struct _fence_t));
    assert(new!=NULL);
    new->next = NULL;
    new->type = T;
    
    if(fence == NULL){
        return new;
    }
    
    struct _fence_t *aux = fence;
    while(aux->next!=NULL){
        aux = aux->next;
    }
    aux->next = new;
    fence->size++;

    return fence;
}
bool fence_is_correct(fence_t fence){
   //ver esta
    /*bool tiene = false;
    struct _fence_t *aux = fence;
    struct _fence_t *prev = NULL;

    while(aux != NULL){
        if(aux->type == T){
            tiene = true;
        }

        if (prev != NULL && 
            prev->type != P && 
            aux->type != P) {
            return false;
        }
        if (aux->next != NULL && 
            aux->next->type != P && 
            aux->type != P) {
            return false;
        }
        
        prev = aux;
        aux = aux->next;
    }*/
    bool tiene = false;
    struct _fence_t *aux = fence;
    struct _fence_t *prev = NULL;

    while(aux != NULL){
        if(aux->type == T){
            tiene = true;
            if(tiene && prev->type != P){
                tiene = false;
            }
            if(tiene && aux->next->type != P){
                tiene = false;
            }
            if(tiene && prev == NULL){
                tiene = false;
            }
        }

        prev = aux;
        aux = aux->next;
    }
    //Otra idea a chequear: Recorrer TODO para ver si tiene T.
    // Luego, si tiene T, recorrer con aux.type != P con 2 punteros (prev y aux2)
    return tiene;
}
unsigned int fence_perimeter(fence_t fence){
    unsigned int res = 0u;
    struct _fence_t *aux = fence;
    while(aux!=NULL){
        if(aux->type != P){
            res = res + 3;
        }
        aux = aux->next;
    }

    return res;
}
unsigned int fence_size(fence_t fence){
    return fence->size;
}
type_t *fence_to_array(fence_t fence){
   type_t *array = NULL;
   array = malloc(sizeof(struct _fence_t)*fence->size);
   assert(array!=NULL);

   struct _fence_t *aux = fence;
   for(int i = fence->size - 1 ; i>=0; i--){
    array[i] = aux->type;
    aux = aux->next;
   }

   return array;
}
fence_t fence_destroy(fence_t fence){
    struct _fence_t *aux = fence;
    while(aux!=NULL){
        struct _fence_t *aux2 = aux->next;
        free(aux);
        aux = aux2;
   }

    return NULL;
}