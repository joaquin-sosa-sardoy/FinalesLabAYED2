#ifndef cf_match_H
#define cf_match_H

#include "card.h"
#include <stdbool.h>

typedef struct _s_match * cf_match;

cf_match match_new(void);
/*
* Creates a new match line, initially the match is empty
*
*/

cf_match match_add(cf_match match, card c);
/*
* Adds a card to the match
*
*/

unsigned int match_size(cf_match match);
/*
* Returns number of cards in the match
*
* PRE: {match --> cf_match}
*   size = match_size(match);
* POS: {size >= 0}
*/

bool is_match_correct(cf_match match);
/*
* Indicates if the match is valid:
*/

unsigned int match_winner(cf_match match);
/*
* Returns the player that wins the match ( 1 || 2).
* If the match is a tie returns 0
* If the match is invalid it returns -1
*
* PRE: {match --> cf_match}
*   winner = match_winner(match);
* POS: {winner == -1 || 0 || 1 || 2}
*/


unsigned int winner_total_points(cf_match match);
/*
* Return the sum of points for the winning player.
* if the match is invalid, returns 0
*
* PRE: {match --> cf_match}
*   points = winner_total_points(match);
* POS: {points >= 0}
*/

card * match_to_array(cf_match match);
/*
* Returns an array in dynamic memory that holds all the cards of the match. The
* caller must free the array when it is no longer needed. The returned
* array holds the internal references of the cards used by the cf_match
* instance (the originals, not copies) so the caller MUST NOT DESTROY THEM,
* only has to free the array.
*
* PRE: {match --> cf_match}
*   array = match_to_array(match);
* POS: {array != NULL}
*
*/

void match_dump(cf_match match);
/*
* Shows the match on the screen
*
*/

cf_match match_destroy(cf_match match);
/*
* Destroy the match, freeing all memory.
*
* PRE: {match --> cf_match}
*   match = match_destroy(match);
* POS: {match == NULL}
*
*/

#endif
