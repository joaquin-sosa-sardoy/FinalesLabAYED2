#ifndef FENCE_H
#define FENCE_H
#include <stdbool.h>

typedef enum {P, A, H, T} type_t;
typedef struct _fence_t *fence_t;

fence_t fence_P();
fence_t fence_add_P(fence_t fence);
fence_t fence_add_A(fence_t fence);
fence_t fence_add_H(fence_t fence);
fence_t fence_add_T(fence_t fence);
bool fence_is_correct(fence_t fence);
unsigned int fence_perimeter(fence_t fence);
unsigned int fence_size(fence_t fence);
type_t *fence_to_array(fence_t fence);
fence_t fence_destroy(fence_t fence);

#endif