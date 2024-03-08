#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

void
dump_array(char *array, unsigned int size) {
    printf("|");
    for (unsigned int i=0; i < size; i++) {
        printf("%c", array[i]);
    }
    printf("|\n");
}

static void
print_stackstatus(stack s) {
    printf("[stack_size(): %2u, stack_is_empty(): %s]",
            stack_size(s), 
            stack_is_empty(s) ? "true ": "false");
}


int main(int argc, char *argv[]) {
    stack s;
    if (argc < 1) {
        printf("A parameter is required!\n");
        exit(EXIT_FAILURE);
    }
    char *input_str=argv[1];

    s = stack_empty();
    for (unsigned int i=0; i < strlen(input_str); i++) {
        print_stackstatus(s);
        printf(" pushing: '%c' ", input_str[i]);
        stack_push(s, input_str[i]);
        print_stackstatus(s);
        printf("\n");
    }
    char *array = stack_to_array(s);
    printf("\nstack_to_array(): ");
    dump_array(array, stack_size(s));
    printf("\n");
    for (unsigned int i=0; i < strlen(input_str); i++) {
        print_stackstatus(s);
        printf(" popping ");
        stack_pop(s);
        print_stackstatus(s);
        printf("\n");
    }
    s = stack_destroy(s);
    free(array);
    return EXIT_SUCCESS;
}

