#include "domino.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct _s_domino
{
    int up;
    int down;
};

/* auxiliary functions for dumping */

static char mark(bool b)
{
    return b ? 'O' : ' ';
}

static void dump_num(int num)
{
    printf("      | %c     %c |\n",
           mark(num > 1), mark(num > 3));
    printf("      | %c  %c  %c |\n",
           mark(num > 5), mark(num % 2 == 1), mark(num > 5));
    printf("      | %c     %c |\n",
           mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num)
{
    printf(" --------------------- \n");
    printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
    printf("| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

    printf(" |    %c    ", mark(num % 2 == 1));
    printf("|    %c    |\n", mark(num % 2 == 1));

    printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
    printf("| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
    printf(" --------------------- \n");
}

void dump(int num_up, int num_down)
{
    /* Pretty dump funcion for cool visualization :) */
    if (num_up != num_down)
    {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    }
    else
    {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino t)
{
    bool valid_domino = false;
    valid_domino = t != NULL &&
                   0 <= t->up && t->up <= 6 &&
                   0 <= t->down && t->down <= 6;
    return valid_domino;
}

/* Public functions */

domino domino_new(int num_up, int num_down)
{
    domino tile = NULL;
    /*
     * COMPLETAR
     *
     */
    tile = malloc(sizeof(domino)); //Intente buscar el memory leak probando con todo pero no pude
    tile->down = num_down;
    tile->up = num_up;
    assert(invrep(tile));
    return tile;
}

bool domino_is_double(domino tile)
{
    bool is_double = false;
    assert(invrep(tile));
    is_double = tile->up == tile->down;
    return is_double;
}

int domino_up(domino tile)
{
    assert(invrep(tile));
    return tile->up;
}

int domino_down(domino tile)
{
    assert(invrep(tile));
    return tile->down;
}

bool domino_matches(domino t_top, domino t_bottom)
{
    bool is_match = false;
    assert(invrep(t_top) && invrep(t_bottom));
    is_match = t_top->down == t_bottom->up;
    return is_match;
}

void domino_dump(domino tile)
{
    assert(invrep(tile));
    dump(tile->up, tile->down);
}

domino domino_destroy(domino tile)
{
    /*
     * COMPLETAR
     *
     */ 
    free(tile);
    tile = NULL;

    return NULL;
}
