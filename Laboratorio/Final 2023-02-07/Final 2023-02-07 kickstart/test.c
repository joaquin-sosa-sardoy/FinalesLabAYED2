/**
ALGO2 FINAL 04 JULIO 2018
Autor: Leo Rodríguez
**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "position.h"
#include "list.h"


#define M_UP 0
#define M_DOWN 1
#define M_LEFT 2
#define M_RIGHT 3

// DO NOT MODIFY THIS FILE.

void bye();

void check(unsigned int a1,
           unsigned int a2,
           int mov, unsigned int b1, unsigned int b2, unsigned int dimension)
{
        position_t p = position_absolute(a1, a2, dimension);
        char m[7];

        switch (mov) {
        case M_UP:
                p = position_up(p);
                strcpy(m, "UP");
                break;
        case M_DOWN:
                p = position_down(p);
                strcpy(m, "DOWN");
                break;
        case M_LEFT:
                p = position_left(p);
                strcpy(m, "LEFT");
                break;
        case M_RIGHT:
                p = position_right(p);
                strcpy(m, "RIGHT");
                break;
        default:
                break;
        }

        printf("Dimension %u\n", dimension);
        printf("Expected (%u, %u)=%s=>(%u, %u) ... \n", a1, a2, m, b1, b2);
        printf("Returned (%u, %u)=%s=>(%u, %u) ... \n",
               a1, a2, m, position_row(p), position_column(p));

        if (b1 == position_row(p) && b2 == position_column(p)) {
                printf("OK\n");
        } else {
                printf("FAIL\n");
                exit(1);
        }

        printf("Checking position board (%u, %u) ... \n", b1, b2);
        unsigned int **matrix = position_board(p);
        for (unsigned int i = 0; i < dimension; i++) {
                for (unsigned int j = 0; j < dimension; j++) {
                        unsigned int k = (i == b1 && j == b2);
                        printf("Position (%u, %u) expected to be %d ... ", i, j,
                               k);
                        if (matrix[i][j] == k) {
                                printf("OK\n");
                        } else {
                                printf("FAIL\n");
                                exit(1);
                        }
                }
                free(matrix[i]);
        }
        free(matrix);

        printf("Checking generated movements (%u, %u) ...\n", b1, b2);
        list_t movements = position_movements(p);
        list_it_t movements_it = list_get_iterator(movements);
        int k = 0;
        for (unsigned int i = 0; i < position_column(p); i++) {
                printf("Movement %d expected to be RIGHT\n", k);
                if (list_iterator_end(movements_it) || (list_iterator_elem(movements_it) != RIGHT)) {
                        printf("Unexpected movement %s should be RIGHT\n",
                               list_iterator_end(movements_it) ? "NULL" : "DOWN");
                        printf("FAIL\n");
                        list_destroy(movements);
                        exit(1);
                }
                k++;
                movements_it = list_iterator_next(movements_it);
        }
        for (unsigned int i = 0; i < position_row(p); i++) {
                printf("Movement %d expected to be DOWN\n", k);
                if (list_iterator_end(movements_it) || (list_iterator_elem(movements_it) != DOWN)) {
                        printf("Unexpected movement %s should be DOWN\n",
                               list_iterator_end(movements_it) ? "NULL" : "RIGHT");
                        printf("FAIL\n");
                        list_destroy(movements);
                        exit(1);
                }
                movements_it = list_iterator_next(movements_it);
                k++;
        }
        if (! list_iterator_end(movements_it)) {
                printf("List has more elements than necessary\n");
                printf("FAIL\n");
                list_destroy(movements);
                exit(1);
        }

        printf("Destroying ... \n");
        list_destroy(movements);
        position_destroy(p);

}

#define SIZE 40

int m[][6] = {
        {0, 1, M_RIGHT, 0, 2, 6},
        {0, 1, M_LEFT, 0, 0, 6},
        {0, 1, M_UP, 5, 1, 6},
        {0, 1, M_DOWN, 1, 1, 6},

        {1, 0, M_RIGHT, 1, 1, 6},
        {1, 0, M_LEFT, 1, 5, 6},
        {1, 0, M_UP, 0, 0, 6},
        {1, 0, M_DOWN, 2, 0, 6},

        {5, 1, M_RIGHT, 5, 2, 6},
        {5, 1, M_LEFT, 5, 0, 6},
        {5, 1, M_UP, 4, 1, 6},
        {5, 1, M_DOWN, 0, 1, 6},

        {1, 5, M_RIGHT, 1, 0, 6},
        {1, 5, M_LEFT, 1, 4, 6},
        {1, 5, M_UP, 0, 5, 6},
        {1, 5, M_DOWN, 2, 5, 6},

        {0, 0, M_RIGHT, 0, 1, 6},
        {0, 0, M_LEFT, 0, 5, 6},
        {0, 0, M_UP, 5, 0, 6},
        {0, 0, M_DOWN, 1, 0, 6},

        {5, 5, M_RIGHT, 5, 0, 6},
        {5, 5, M_LEFT, 5, 4, 6},
        {5, 5, M_UP, 4, 5, 6},
        {5, 5, M_DOWN, 0, 5, 6},

        {2, 2, M_RIGHT, 2, 3, 6},
        {2, 2, M_LEFT, 2, 1, 6},
        {2, 2, M_UP, 1, 2, 6},
        {2, 2, M_DOWN, 3, 2, 6},

        {0, 0, M_RIGHT, 0, 0, 1},
        {0, 0, M_LEFT, 0, 0, 1},
        {0, 0, M_UP, 0, 0, 1},
        {0, 0, M_DOWN, 0, 0, 1},

        {0, 5, M_RIGHT, 0, 0, 6},
        {0, 5, M_LEFT, 0, 4, 6},
        {0, 5, M_UP, 5, 5, 6},
        {0, 5, M_DOWN, 1, 5, 6},

        {5, 0, M_RIGHT, 5, 1, 6},
        {5, 0, M_LEFT, 5, 5, 6},
        {5, 0, M_UP, 4, 0, 6},
        {5, 0, M_DOWN, 0, 0, 6}

};

int main()
{
        for (unsigned int i = 0; i < SIZE; i++) {
                check(m[i][0], m[i][1], m[i][2], m[i][3], m[i][4], m[i][5]);
        }
        bye();
}































void bye()
{
        printf("Thank you very much!!\n");
        printf
            ("Series recomendadas: Better Call Saul, The Handmaid's Tale, Utopia, Dark\n");
}
