#ifndef UNO_GAME_H
#define UNO_GAME_H

#include "card.h"

typedef struct s_ugame * unogame_t;

typedef int player_t;

#define NUM_PLAYERS 3

unogame_t
uno_newgame(card_t card);
/*
 * Creates a new instance of unogame_t with first card <c> in the discard-pile
 *
 */

card_t
uno_topcard(unogame_t uno);
/*
 * Returns the last card added to the discard-pile
 *
 */

unogame_t
uno_addcard(unogame_t uno, card_t c);
/*
 * Adds card <c> in the game discard-pile. This functions DOES NOT checks
 * compatibility, just adds the new card.
 *
 */

unsigned int
uno_count(unogame_t uno);
/*
 * Returns the number of cards in the discard-pile.
 *
 */

color_t
uno_currentcolor(unogame_t uno);
/*
 * Returns the active color of the game
 *
 */

player_t
uno_nextplayer(unogame_t uno);
/*
 * Tells the player that must play the next card
 *
 * PRE: {uno --> unogame_t}
 *     np = uno_nextplayer(uno);
 * POS: {0 <= np && np < NUM_PLAYERS}
 *
 */

bool
uno_validpile(unogame_t uno);
/*
 * Checks if the pile is well formed.
 *
 */

card_t *
uno_pile_to_array(unogame_t uno);
/*
 * Returns an array with the cards played in order
 *
 *
 */

unogame_t
uno_destroy(unogame_t uno);
/*
 * Destroy the instance
 *
 */


#endif
