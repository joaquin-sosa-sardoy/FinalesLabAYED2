#ifndef DNA_H
#define DNA_H

#include <stdbool.h>
#include <assert.h>

typedef enum nucleobase { T, C, A, G } nucleobase_t;
typedef struct _dna_t *dna_t;

/**
 * @brief Construye una nueva caena de DNA con el nucleótido T
 * 
 * @return dna_t DNA con nucleótido T
 */
dna_t dna_T();

/**
 * @brief Construye una nueva caena de DNA con el nucleótido C
 * 
 * @return dna_t DNA con nucleótido C
 */
dna_t dna_C();

/**
 * @brief Construye una nueva caena de DNA con el nucleótido A
 * 
 * @return dna_t DNA con nucleótido A
 */
dna_t dna_A();

/**
 * @brief Construye una nueva caena de DNA con el nucleótido G
 * 
 * @return dna_t DNA con nucleótido G
 */
dna_t dna_G();

/**
 * @brief Concatena el segundo DNA al final del primer DNA. Modifica el primer argumento.
 *        El segundo argumento no se debe modificar, se crea una copia
 *        de los elementos del segundo DNA que se concatenan al primero
 * 
 * @param first Primera cadena de DNA. Este argumento se modifica
 * @param second Segunda cadena de DNA a concatenar. Este argumento NO SE MODIFICA
 * @return dna_t cadena concatenada
 */
dna_t dna_join(dna_t first, dna_t second);

/**
 * @brief Devuelve la longitud del DNA. Complejidad: O(1)
 * 
 * @param dna Cadena de DNA para calcular la longitud
 * @return unsigned int longitud de la cadena
 */
unsigned int dna_length(dna_t dna);

/**
 * @brief Imprime en pantalla un DNA.
 * 
 * @param dna DNA para imprimir
 */
void dna_print(dna_t dna);

/**
 * @brief Verifica si el primer DNA es prefijo del segundo.
 * 
 * @param first DNA a para verificar si es prefijo de second
 * @param second DNA donde se buscara first como prefijo
 * @return true si first es prefijo de second
 * @return false si first no es prefijo de second
 */
bool dna_is_prefix(dna_t first, dna_t second);

/**
 * @brief Verifica si ambos DNA son iguales (tienen la misma longitud y además uno es prefijo del otro).
 * 
 * @param first Primera cadena de DNA
 * @param second Segunda cadena de DNA
 * @return true Si first es igual a second
 * @return false caso contrario
 */
bool dna_is_equal(dna_t first, dna_t second);

/**
 * @brief Corta el DNA en dos segmentos disjuntos, el primero de longitud ‘count’. 
 *        Concatenando ambos segmentos se obtiene el DNA original. 
 *        Se asume que ‘count’ es mayor estricto que 0 y 
 *        menor estricto que la longitud del primer DNA.
 *        Los dos segmentos se devuelven en un arreglo de tamaño 2.
 * 
 * @param dna DNA para cortar
 * @param count Cantidad de elementos a cortar
 * @return dna_t* Arreglo de tamaño 2 con los 2 segmentos
 */
dna_t *dna_cut(dna_t dna, unsigned int count);

/**
 * @brief Destruye el DNA liberando sus recursos de memoria.
 * 
 * @param dna DNA para destruir
 * @return dna_t DNA destruido
 */
dna_t dna_destroy(dna_t dna);

#endif
