#ifndef DOMINO_LINE_H
#define DOMINO_LINE_H

#include "domino.h"
#include <stdbool.h>

typedef struct _s_line * domino_line;

domino_line line_new(domino first);
/*
* Creates a new line of play with the tile first (must be a double tile).
*
* PRE: {domino_is_double(first)}
*   line = line_new(first);
* POS: {line --> domino_line}
*/

domino_line line_add(domino_line line, domino t);
/*
* Adds a domino tile to the line of play
*
*/

unsigned int line_length(domino_line line);
/*
* Returns how many tiles are in the line
*
* PRE: {line --> domino_line}
*   len = line_lenght(line);
* POS: {len > 0}
*
*/

bool line_n_correct(domino_line line, unsigned int n);
/*
* Indicates if n-th tile of the line is correctly placed. This is so if tile
* (n - 1) matches tile n and tile n matches tile (n + 1). If n is 0, only
* checks that the first tile matches the seconde one. If n is the last tile
* (i.e. n == line_lenght(line) - 1) checks only if previus tile matches. If
* line_length(line) == 1 (only one tile) it returns true.
*
* PRE: {n < line_length(line)}
*
*/

int line_total_points(domino_line line);
/*
* Return the sum of all tiles of the line.
*
* PRE: {line --> domino_line}
*   total = line_total_points(line);
* POS: {total >= 0}
*
*/

domino * line_to_array(domino_line line);
/*
* Returns an array in dynamic memory that holds all tiles of the line. The
* caller must free the array when it is no longer needed. The returned
* array holds the internal references of the tiles used by the domino_line
* instance (the originals, not copies) so the caller MUST NOT DESTROY THEM,
* only has to free the array.
*
* PRE: {line --> domino_line}
*   array = line_to_array(line);
* POS: {array != NULL}
*
*/

void line_dump(domino_line line);
/*
* Shows the line on the screen
*
*/

domino_line line_destroy(domino_line line);
/*
* Destroy the line, freeing all memory.
*
* PRE: {line --> domino_line}
*   line = line_destroy(line);
* POS: {line == NULL}
*
*/

#endif
