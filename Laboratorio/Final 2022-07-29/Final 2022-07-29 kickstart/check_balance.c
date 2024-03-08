#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stack.h"

#define GREEN "\033[38;2;0;200;0m"
#define RED "\033[0;31m"
#define NOCOLOR "\033[0m"

static void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <expression-to-check>\n\n"
           "Check if the expression has balanced parenthesis.\n",
           program_name);
}

static char* parse_expression(int argc, char *argv[]) {
    /* Parse the expression given by command line argument. */
    char *result=NULL;
    /* Program takes exactly one argument */
    if (argc != 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    /* Use the first argument ass the expression */
    result = argv[1];
    /* return expression */
    return result;
}

static bool
is_parenthesis(char c) {
    return c=='(' || c==')';
}

int main(int argc, char *argv[]) {
    // Parse arguments and get the expression to be analysed
    char *expression = parse_expression(argc, argv);
    size_t expression_length = strlen(expression);// COMPLETAR;
    size_t i=0;
    bool is_balanced=true;
    stack s = stack_empty();

    while (i < expression_length && is_balanced) {
        char chr = expression[i];
        if (is_parenthesis(chr)) {
            /*
             * COMPLETAR
             *
             */
            if (chr == '(' || chr == '[' || chr == '{') {
                // Empujar el carácter de apertura a la pila
                s = stack_push(s, chr);
            } else if (chr == ')' || chr == ']' || chr == '}') {
                // Verificar si la pila está vacía o si el carácter de cierre coincide con el carácter en la cima de la pila
                stack_top(s, &chr);
        }
        i++; 
        expression_length--;
    }

    is_balanced = is_balanced && /* COMPLETAR */stack_is_empty(s);

    if (is_balanced) {
        printf(GREEN "The given expression is balanced\n" NOCOLOR);
    } else {
        printf(RED "The given expresión is not balanced\n" NOCOLOR);

    }
    // Free all memory used by the stack
    // COMPLETAR
    while (!stack_is_empty(s)) {
        s = stack_pop(s);
    }
    free(expression);
    return EXIT_SUCCESS;
        }}

