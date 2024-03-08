#ifndef _DOMINO_H
#define _DOMINO_H

#include <stdbool.h>

typedef struct _s_domino * domino;

domino domino_new(int num_up, int num_down);

bool domino_is_double(domino tile);

int domino_up(domino tile);

int domino_down(domino tile);

bool domino_matches(domino t_top, domino t_botton);

void domino_dump(domino tile);

domino domino_destroy(domino tile);


#endif
