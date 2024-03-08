#ifndef WAR_MATCH_H
#define WAR_MATCH_H

#include "card.h"
#include <stdbool.h>

typedef struct _s_match * war_match;

war_match match_new(void);
/*
* Creates a new match line, initially the match is empty
*
*/

war_match match_add(war_match match, card c);
/*
* Adds a card to the match
*
*/

unsigned int match_size(war_match match);
/*
* Returns number of cards in the match
*
* PRE: {match --> war_match}
*   size = match_size(match);
* POS: {size >= 0}
*/

unsigned int match_length(war_match match);
/*
* Returns the number of hands player.
* If the match is invalid it returns 0
*
* PRE: {match --> war_match}
*   length = match_length(match);
* POS: {length >= 0}
*/

bool is_match_correct(war_match match);
/*
* Indicates if the match is valid:
* this is true if all of the following are correct:
* 1. Match starts with a card from player 1
* 2. Number of cards in the mathc is even
* 3. Every card from player 1 is sfollowed by a card from player 2
* 4. No consecutive cards are from the same player
*
*/

unsigned int winner_total_points(war_match match);
/*
* Return the sum of points for the winning player.
* if the match is invalid, returns 0
*
* PRE: {match --> war_match}
*   points = winner_total_points(match);
* POS: {points >= 0}
*/

card * match_to_array(war_match match);
/*
* Returns an array in dynamic memory that holds all the cards of the match. The
* caller must free the array when it is no longer needed. The returned
* array holds the internal references of the cards used by the war_match
* instance (the originals, not copies) so the caller MUST NOT DESTROY THEM,
* only has to free the array.
*
* PRE: {match --> war_match}
*   array = match_to_array(match);
* POS: {array != NULL}
*
*/

void match_dump(war_match match);
/*
* Shows the match on the screen
*
*/

war_match match_destroy(war_match match);
/*
* Destroy the match, freeing all memory.
*
* PRE: {match --> war_match}
*   match = match_destroy(match);
* POS: {match == NULL}
*
*/

#endif
