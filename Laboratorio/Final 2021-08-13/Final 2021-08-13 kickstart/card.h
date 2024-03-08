#ifndef _CARD_H
#define _CARD_H

#include <stdbool.h>

typedef struct _s_card * card;

card card_new(unsigned int num, char suit, unsigned int player);

unsigned int card_player(card c);

unsigned int card_number(card c);

char card_suit(card c);

bool card_wins(card fst, card snd);

unsigned int card_match_points(card fst, card snd);

void card_dump(card c);

card card_destroy(card c);

#endif
