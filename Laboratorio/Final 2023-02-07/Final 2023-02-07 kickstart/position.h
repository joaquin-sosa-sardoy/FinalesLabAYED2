#ifndef POSITION_H
#define POSITION_H
#include "list.h"
// DO NOT MODIFY THIS FILE.

typedef struct _position *position_t;

/**
 * @brief Retorna la posición incial
 * 
 * @param dimension dimension de la matrix cuadrada (dimensionxdimension)
 * @return La nueva posición creada (0,0) para la matrix de dimension 'dimension'
 */
position_t position_initial(unsigned int dimension);

/**
 * @brief Crea una posición absoluta a partir de un fila y columna
 *        PRECONDICION: 'row' y 'column' deben ser menores que 'dimension'
 * 
 * @param row fila de la posición deseada
 * @param column columna de la posición deseada
 * @param dimension dimensión de la matriz cuadrada
 * @return position_t 
 */
position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension);
/**
 * @brief Mueve una posición hacia la izquierda de manera circular
 * 
 * @param pos posición a mover
 * @return position_t Nueva posición obtenida
 */
position_t position_left(position_t pos);

/**
 * @brief Mueve una posición hacia la derecha de manera circular
 * 
 * @param pos posición a mover
 * @return position_t Nueva posición obtenida
 */
position_t position_right(position_t pos);

/**
 * @brief Mueve una posición hacia abajo de manera circular
 * 
 * @param pos posición a mover
 * @return position_t Nueva posición obtenida
 */
position_t position_down(position_t pos);

/**
 * @brief Mueve una posición hacia arriba de manera circular
 * 
 * @param pos posición a mover
 * @return position_t Nueva posición obtenida
 */
position_t position_up(position_t pos);

/**
 * @brief devuelve la file de la posición dada
 * 
 * @param pos posición de la matriz para obtener la fila
 * @return unsigned int fila de la posición
 */
unsigned int position_row(position_t pos);

/**
 * @brief retorna la columna de la posición dada
 * 
 * @param pos posición de la matriz
 * @return unsigned int columna de la posición
 */
unsigned int position_column(position_t pos);

/**
 * @brief Construye una matriz con el valor 0 en todas las celdas, excepto
          por la celda correspondiente a la posición p que tiene valor 1
 * 
 * @param pos posición de la matriz
 * @return unsigned int** 
 */
unsigned int **position_board(position_t pos);

/**
 * @brief Devuelve una lista de movimientos necesarios para alcanzar
          la posición p a partir de la posición inicial (0,0). 
          La lista contiene una secuencia de movimientos
          de columnas (hacia la derecha) seguida de una secuencia 
          de movimientos de fila (hacia abajo).
 * 
 * @param pos posición de la matriz
 * @return list_t lista de movimientos
 */
list_t position_movements(position_t pos);


/**
 * @brief destruye la posición
 * 
 * @param pos posición a destruir
 * @return position_t  posición luego de ser destruida
 */
position_t position_destroy(position_t pos);

#endif
