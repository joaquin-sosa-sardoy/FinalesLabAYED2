#include "dna.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TEST

int main()
{
    /** COMPLETAR ACÁ */

   dna_t dna1 = dna_T();
    printf("DNA1: ");
    dna_print(dna1);

    
    dna_destroy(dna1);
    return(0);
}

#endif
