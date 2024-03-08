#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matchTimeline.h"

/* ============================================================================
HELPER
============================================================================ */

static void print_event_array(matchTimeline mt)
{
    event *mtArray = matchTimeline_events_array(mt);
    fprintf(stdout, "\nAs array [ ");
    for (unsigned int i = 0u; i < matchTimeline_size(mt); i++)
    {
        char *e = NULL;
        switch (mtArray[i])
        {

        case Goal:
            e = "G";
            break;
        case YellowCard:
            e = "Y";
            break;
        case RedCard:
            e = "R";
            break;
        }

        fprintf(stdout, "%s ", e);
    }
    fprintf(stdout, "]\n");
    free(mtArray);
}

/* ============================================================================
TESTS
============================================================================ */

static void test_all_ok()
{
    matchTimeline mt = matchTimeline_empty();
    mt = matchTimeline_score_goal(mt, Home, 23, 10);
    mt = matchTimeline_score_goal(mt, Home, 36, 11);
    mt = matchTimeline_receive_yellowCard(mt, Home, 45, 24);
    mt = matchTimeline_receive_yellowCard(mt, Away, 54, 14);
    mt = matchTimeline_score_goal(mt, Away, 80, 10);
    mt = matchTimeline_score_goal(mt, Away, 81, 10);
    mt = matchTimeline_receive_yellowCard(mt, Away, 86, 26);
    mt = matchTimeline_receive_yellowCard(mt, Away, 90, 9);
    mt = matchTimeline_receive_yellowCard(mt, Home, 90, 8);
    mt = matchTimeline_receive_redCard(mt, Home, 90, 8);

    // todo deberia andar
    assert(matchTimeline_is_time_and_score_valid(mt));
    assert(matchTimeline_size(mt) == 10);
    assert(matchTimeline_get_score(mt, Home) == 2);
    assert(matchTimeline_get_score(mt, Away) == 2);

    // print
    matchTimeline_print(mt);
    print_event_array(mt);

    // destroy mt
    matchTimeline_destroy(mt);
}

/**
 * @brief este test chequea que luego de la segunda amarilla de un jugador se
 *        crea automaticamente una roja a ese jugador
 *
 */
static void test_two_yellows_then_red()
{
    matchTimeline mt = matchTimeline_empty();
    mt = matchTimeline_receive_yellowCard(mt, Away, 44, 24);
    mt = matchTimeline_receive_yellowCard(mt, Away, 54, 24);

    // todo deberia andar
    assert(matchTimeline_is_time_and_score_valid(mt));
    assert(matchTimeline_size(mt) == 3);
    assert(matchTimeline_get_score(mt, Home) == 0);
    assert(matchTimeline_get_score(mt, Away) == 0);

    // print
    matchTimeline_print(mt);
    print_event_array(mt);

    // destroy mt
    matchTimeline_destroy(mt);
}

/**
 * @brief este test chequea que luego que un jugador tiene tarjeta roja, los 
 *        eventos que se agreguen de ese mismo jugador, no se crea el registro
 *        en el matchTimeline
 *
 */
static void test_new_event_on_red_card()
{
    matchTimeline mt = matchTimeline_empty();

    // COMPLETAR

    matchTimeline_destroy(mt);
}

/**
 * @brief este test chequea que luego que se cumplen los 90 minutos, los 
 *        eventos que se agreguen con un tiempo mayor a 90, no se crea el 
 *        registro en el matchTimeline
 *
 */
static void test_insert_after_90_minutes()
{

    matchTimeline mt = matchTimeline_empty();
    mt = matchTimeline_score_goal(mt, Home, 23, 10);
    mt = matchTimeline_score_goal(mt, Away, 91, 11);

    assert(matchTimeline_is_time_and_score_valid(mt));
    assert(matchTimeline_size(mt) == 1);
    assert(matchTimeline_get_score(mt, Home) == 1);
    assert(matchTimeline_get_score(mt, Away) == 0);

    matchTimeline_print(mt);
    print_event_array(mt);

    // destroy mt
    matchTimeline_destroy(mt);
}

/**
 * @brief este test comprueba la función matchTimeline_is_time_and_score_valid
 *        es decir que devuelva false en un matchTimeline que está "mal". En 
 *        este caso, se agregan registros que están desordenados
 *
 */
static void test_invalid_time_order()
{

    matchTimeline mt = matchTimeline_empty();
    mt = matchTimeline_score_goal(mt, Home, 23, 10);
    mt = matchTimeline_score_goal(mt, Home, 36, 11);
    mt = matchTimeline_receive_yellowCard(mt, Home, 35, 24);

    assert(!matchTimeline_is_time_and_score_valid(mt));
    assert(matchTimeline_size(mt) == 3);
    assert(matchTimeline_get_score(mt, Home) == 2);
    assert(matchTimeline_get_score(mt, Away) == 0);

    matchTimeline_print(mt);
    print_event_array(mt);

    // destroy mt
    matchTimeline_destroy(mt);
}



int main(void)
{
    fprintf(stdout, "test_all_ok() <-------------------------\n");
    test_all_ok();
    fprintf(stdout, "\n");

    fprintf(stdout, "test_two_yellows_then_red() <-----------\n");
    test_two_yellows_then_red();
    fprintf(stdout, "\n");

    fprintf(stdout, "test_new_event_on_red_card <------------\n");
    test_new_event_on_red_card();
    fprintf(stdout, "\n");

    fprintf(stdout, "test_insert_after_90_minutes <----------\n");
    test_insert_after_90_minutes();
    fprintf(stdout, "\n");

    fprintf(stdout, "test_invalid_time_order <---------------\n");
    test_invalid_time_order();
    fprintf(stdout, "\n");

    return EXIT_SUCCESS;
}
