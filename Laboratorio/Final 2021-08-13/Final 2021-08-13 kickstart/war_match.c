#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "war_match.h"
#include "card.h"

struct _s_match {
  /*
  * COMPLETAR
  *
  */
};

war_match match_new(void) {
  /*
  * COMPLETAR
  *
  */
}

war_match match_add(war_match match, card c) {
  /*
  * COMPLETAR
  *
  */
}

unsigned int match_size(war_match match) {
  /*
  * COMPLETAR
  *
  */
}

unsigned int match_length(war_match match) {
  /*
  * COMPLETAR
  *
  */
}

bool is_match_correct(war_match match) {
  /*
  * COMPLETAR
  *
  */
}

static unsigned int player_score(war_match match, unsigned int player) {
  /*
  * COMPLETAR:
  *
  * Calcula el puntaje de 'player' en el partido 'match'
  *
  */
}

unsigned int winner_total_points(war_match match) {
  /*
  * COMPLETAR
  * tips:
  * * recordar que si is_match_correct es falso esto retorna 0
  * * usar player_score para calcular el puntaje de un jugador particular
  *
  */
}

card * match_to_array(war_match match) {
  /*
  * COMPLETAR
  *
  */
}

void match_dump(war_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

war_match match_destroy(war_match match) {
  /*
  * COMPLETAR
  *
  */
}
