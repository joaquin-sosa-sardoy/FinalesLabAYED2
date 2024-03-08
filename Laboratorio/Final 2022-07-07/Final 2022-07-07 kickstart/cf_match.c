#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct _s_match {
    unsigned int size; ////?????
    struct s_node *head;
};


cf_match match_new(void)
{
}

cf_match match_add(cf_match match, card c)
{
}

unsigned int match_size(cf_match match)
{
}

bool is_match_correct(cf_match match)
{
}

static int player_score(cf_match match, unsigned int player)
{
}

unsigned int match_winner(cf_match match)
{
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match)
{
}

void match_dump(cf_match match)
{
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
}
