#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

struct s_node
{
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};

struct s_matchTimeline
{
    struct s_node *head;
    // COMPLETAR
    unsigned int size;
    unsigned int golesAway;
    unsigned int golesHome;
};

/* ============================================================================
INVERP & VALIDATION
============================================================================ */

static bool invrep(matchTimeline mt)
{
    // COMPLETAR
    static bool res = true;
    res = mt!=NULL;
    unsigned int lenght = 0u;
    struct s_node *aux = mt->head;
    while(aux!=NULL){
        lenght++;
        aux = aux->next;
    }
    res = res && lenght == mt->size;
    return res; // Just for compiling, delete it
}

bool matchTimeline_is_time_and_score_valid(matchTimeline mt)
{

    // COMPLETAR
    unsigned int away = 0u;
    unsigned int home = 0u;
    unsigned int time = 0u;
    bool res = true;
    struct s_node *aux = mt->head;
    while(aux!=NULL){
        if(aux->e == Goal){
            if(aux->team == Away){
                away = away + 1;
            }
            if(aux->team == Home){
                home = home + 1;
            }
        }
        if(aux->t < time){
            res = false;
        }
        time = aux->t;

        aux = aux->next;
    }
    res = res && away == mt->golesAway && mt->golesHome == home;

    return res;
}

/* ============================================================================
CONSTRUCTOR
============================================================================ */

matchTimeline matchTimeline_empty(void)
{
    matchTimeline mt = NULL;
    // COMPLETAR
    mt = malloc(sizeof(struct s_matchTimeline));
    mt->golesAway = 0u;
    mt->golesHome = 0u;
    mt->head = NULL;
    mt->size = 0u;

    assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn)
{

    struct s_node *new_node = NULL;
    // COMPLETAR
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->e = e;
    new_node->next = NULL;
    new_node->pn = pn;
    new_node->t = t;
    new_node->team = team;

    return new_node;
}
// HARE UN FUNCION AUXILIAR QUE ES INSERTAR NODO YA QUE EN MUCHAS FUNCIONES DEBO AGREGAR
void insert_node(matchTimeline mt, team team, event e, time t, playerNumber pn){
    struct s_node *newNode = create_node(team,e,t,pn);
    if(mt->head == NULL){ // IMPORTANTISIMO. IF MT O FENCE == NULL
        mt->head = newNode;
    } else {
        struct s_node *aux = mt->head;
        while(aux->next != NULL){
            aux = aux->next;
        }

        aux->next = newNode;
    }

    mt->size++; //Debo sumar uno al size ya que agregue un nodo
}

/* ============================================================================
GOAL
============================================================================ */

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    
    // COMPLETAR
    struct s_node *aux = mt->head;
    if(t<=EVENT_MAX_TIME){
        while(aux != NULL){
            if(aux->e == RedCard && aux->pn == pn){
                return mt;
            }
            aux = aux->next;
        }

        insert_node(mt,team,Goal,t,pn);
        //Debo considerar que equipo hizo el gol.
        if(team == Home){
            mt->golesHome++;
        }
        if(team == Away){
            mt->golesAway++;
        }
    }

    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */

matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));

    // COMPLETAR
    if(t<=EVENT_MAX_TIME){
        bool tieneAmarilla = false;
        struct s_node *aux = mt->head;
        while(aux!=NULL){
            if(aux->e == YellowCard && aux->pn == pn){
                tieneAmarilla = true;
            }
            if(aux->pn == pn && aux->e == RedCard){
                return mt;
            }
            aux = aux->next;
        }
        insert_node(mt,team,YellowCard,t,pn);

        if(tieneAmarilla){
            insert_node(mt,team,RedCard,t,pn);
        }
    }

    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));

    // COMPLETAR
    if(t<=EVENT_MAX_TIME){
        struct s_node *aux = mt->head;
        while(aux!=NULL){
            if(aux->e == RedCard && aux->pn == pn){
                return mt;
            }
            aux = aux->next;
        }
        insert_node(mt,team,RedCard,t,pn);
    }

    return mt;
}

/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team)
{
    assert(invrep(mt));

    // COMPLETAR
    unsigned int res = 0u;
    if(team == Home){
        res = mt->golesHome;
    }
    if(team == Away){
        res = mt->golesAway;
    }

    return res;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt)
{
    assert(invrep(mt));
    // COMPLETAR

    return mt->size;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt)
{
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL)
    {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt)
{
    event *array = NULL;
        // COMPLETAR
    array = malloc(sizeof(struct s_matchTimeline)*mt->size);
    unsigned int size = mt->size;
    struct s_node *aux = mt->head;
    for(unsigned int i = 0u; i < size ; i++){
        array[i] = aux->e;
        aux = aux->next;
    }

    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node)
{
    
    // COMPLETAR
    node->next = NULL;
    free(node);
    node = NULL;

    return node;
}

matchTimeline matchTimeline_destroy(matchTimeline mt)
{
    assert(invrep(mt));

    // COMPLETAR
    struct s_node *aux = NULL;
    while(mt->head != NULL){
        aux = mt->head;
        mt->head = mt->head->next;
        aux = destroy_node(aux);
    }
    free(mt);
    mt = NULL;

    return mt;
}
