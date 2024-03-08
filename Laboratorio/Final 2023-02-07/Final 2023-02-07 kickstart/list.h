#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

typedef enum { RIGHT, DOWN } movement_t;
typedef struct _node *list_t;
typedef list_t list_it_t;

/**
 * @brief constructor de la lista
 * 
 * @return list_t retorna una lista vacía
 */
list_t list_empty(void);

/**
 * @brief agrega un elemento a la derecha de la lista
 * 
 * @param src lista a la cual se le agrega el elemento
 * @param movement nuevo elemento de tipo 'movement_t'
 * @return list_t lista con el nuevo elemento añadido
 */
list_t list_append(list_t src, movement_t movement);

/**
 * @brief destruye la lista 'list'
 * 
 * @param list lista a ser destruida
 * @return list_t lista luego de ser destruida (NULL)
 */
list_t list_destroy(list_t list);

/**
 * @brief Muestra la lista 'list' por pantalla
 * 
 * @param list lista a ser mostrada
 */
void list_show(list_t list);

/** ITERADOR DE LISTA */

/**
 * @brief devuelve un iterador a la lisa 'list'
 * 
 * @param list lista a ser iterada
 * @return list_it_t nuevo iterador creado
 */
list_it_t list_get_iterator(list_t list);

/**
 * @brief avanza el iterator de la lista
 *        PRECONDICION: El iterador no ha finalizado
 * 
 * @param list_it iterador de lista
 * @return list_it_t nuevo iterador con la siguiente posición de la lista
 */
list_it_t list_iterator_next(list_it_t list_it);

/**
 * @brief devuelve el elemento de la posición actual del iterador
 *        PRECONDICION: El iterador no ha finalizado
 * 
 * @param list_it iterador de lista
 * @return movement_t elemento de la posición actual del iterador
 */
movement_t list_iterator_elem(list_it_t list_it);

/**
 * @brief retorna "True" si el iterador ha alcanzado el final de la lista
 * 
 * @param list_it iterador de lista
 * @return true si el iterador  alcanzó el final de la lista
 * @return false caso contrario
 */
bool list_iterator_end(list_it_t list_it);

#endif