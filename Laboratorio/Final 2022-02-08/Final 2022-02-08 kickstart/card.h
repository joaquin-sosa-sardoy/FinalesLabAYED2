#ifndef CARD_H
#define CARD_H

#include <stdbool.h>

typedef struct s_card * card_t;

typedef enum {blue, red, yellow, green} color_t;
typedef enum {normal, change_color, skip} type_t;

card_t
card_new(unsigned int num, color_t color, type_t t);
/*
 * Creates a new instance of card_t with number <num>, color <color> and
 * <t> indicates if the card is regular (t==normal) or an special card
 * (t==change_color, t==skip).
 *
 * PRE: {(num < 10) &&
 *       (color==red || color==green || color==blue || color==yellow) &&
 *       (t==normal  || t==change_color || t==skip)
 *      }
 *
 * card = card_new(num, color, t);
 *
 * POS: {card --> card_t}
 *
 */

type_t
card_get_number(card_t card);
/*
 * Gets the number of <card>
 *
 */

color_t
card_get_color(card_t card);
/*
 * Gets the color of <card>
 *
 */

type_t
card_get_type(card_t card);
/*
 * Gets the type of <card>
 *
 */

bool
card_samenum(card_t c1, card_t c2);
/*
 * Indicates if cards <c1> and <c2> have the same number
 *
 */

bool
card_samecolor(card_t c1, card_t c2);
/*
 * Indicates if cards <c1> and <c2> have the same color
 *
 */


bool
card_compatible(card_t new_card, card_t pile_card);
/*
 * Indicates if <new_card> and <pile_card> are compatible, where <new_card> it
 * will be placed over <pile_card>.
 *
 * If both cards have the same color then are compatible, regardless the type
 * of <new_card> and <pile_card>
 *
 * If <new_card> is the special card with <change_color> type, then is allways
 * compatible with <pile_card>.
 *
 * As the rules of UNO states, if both <new_card> an <pile_card> are regular
 * cards (with type <normal>), then they are compatible if have the same number
 * or have the same color.
 *
 * if <new_card> is special with <skip>, then is compatible with <pile_card> if
 * both have the same color or the same type.
 *
 */

card_t
card_destroy(card_t card);
/*
 * Destroy an instance of card_t freeing all resources.
 *
 */


#endif
