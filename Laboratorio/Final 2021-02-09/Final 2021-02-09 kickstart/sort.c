#include <stdlib.h>
#include <stdio.h>
#include "sorted_list.h"
#include "sort.h"

void sort(int a[], unsigned int length)
{
   // COMPLETE HERE
   sorted_list_t sorted = sorted_list_empty();
   for (unsigned int i = 0; i < length; i++)
   {
     sorted = sorted_list_append(sorted,a[i]);
   }
   sorted_list_print(sorted);
}
