#ifndef MATCH_TIMELINE_H
#define MATCH_TIMELINE_H
#include <stdbool.h>

#define EVENT_MAX_TIME 90u

typedef enum
{
    Goal,
    YellowCard,
    RedCard
} event;

typedef enum
{
    Home,
    Away
} team;

typedef struct s_matchTimeline *matchTimeline;

typedef unsigned int time;

typedef unsigned int playerNumber;

/** CONSTRUCTORES */

/**
 * @brief Devuelve un nuevo 'matchTimeline' creado vacío
 *
 * @return matchTimeline nuevo 'matchTimeline' creado
 */
matchTimeline matchTimeline_empty();

/**
 * @brief registra un nuevo gol
 *
 * @param mt matchTimeline en el cual se crea el registro
 * @param team equipo que registra el evento
 * @param t el minuto en el que sucede el evento
 * @param pn el número del jugador que hace el gol
 * @return matchTimeline con el nuevo registro creado
 */
matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn);

/**
 * @brief registra una nueva tarjeta roja
 *
 * @param mt matchTimeline en el cual se crea el registro
 * @param team equipo que registra el evento
 * @param t el minuto en el que sucede el evento
 * @param pn el número del jugador que recibe la tarjeta
 * @return matchTimeline con el nuevo registro creado
 */
matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn);

/**
 * @brief registra una nueva tarjeta amarilla,
 *        debe tener en cuenta de que si es la segunda tarjeta debe sacar
 *        tarjeta roja también
 *
 * @param mt matchTimeline en el cual se crea el registro
 * @param team equipo que registra el evento
 * @param t el minuto en el que sucede el evento
 * @param pn el número del jugador que recibe la tarjeta
 * @return matchTimeline con el nuevo registro creado
 */
matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn);

/* MODIFICADORES */

/**
 * @brief Devuelve True si el matchTimeline es válido
 *        Es válido cuando los registros están ordenados cronológicamente, y los
 *        goles de home (away) se corresponden con la cantidad de registros de 
 *        goles de home (away)
 *
 *
 * @param mt matchTimeline en el cual se crea el registro
 * @return true Si playerOnBoard es válido
 * @return false Si playerOnBoard no es válido
 */
bool matchTimeline_is_time_and_score_valid(matchTimeline mt);

/**
 * @brief Devuelve el resultado del partido
 *        IMPORTANTE: ESTE METODO DEBE SER CONSTANTE
 *
 * @param mt matchTimeline del cual se obtiene el resultado
 * @return unsigned int Puntaje del jugador
 */
unsigned int matchTimeline_get_score(matchTimeline mt, team team);

/**
 * @brief Devuelve la cantidad de registros que tiene el matchTimeline
 *        IMPORTANTE: ESTE METODO DEBE SER CONSTANTE
 *
 * @param mt matchTimeline
 * @return unsigned int Cantidad de registros del matchTimeline
 */
unsigned int matchTimeline_size(matchTimeline mt);

/**
 * @brief Imprime en pantalla la ficha del partido, en donde en la primer linea
 *        se debe imprimir el resultado
 *        IMPORTANTE: Es un método solo de lectura, no debe modificar la estructura
 *
 * @param mt matchTimeline
 */
void matchTimeline_print(matchTimeline mt);

/**
 * @brief Devuelve un arreglo que representa el tipo de cada evento en el orden
 *        en que ocurrieron. Este método debe pedir memoria para match timeline
 *        y la memoria pedida debe ser liberada después
 *
 * @param mt matchTimeline
 * @return event* Arreglo eventos del partido. Debe seguir el orden de la lista.
 */
event *matchTimeline_events_array(matchTimeline mt);

/**
 * @brief Destruye el registro del match Timeline y libera todos los recursos
 *        pedidos.
 *
 * @param mt matchTimeline
 * @return matchTimeline luego de ser borrado
 */
matchTimeline matchTimeline_destroy(matchTimeline mt);

#endif // MATCH_TIMELINE_H
