/**
*  @file stack.h
*  @brief TAD Stack definition
*/
#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

/**
* @brief Stack type definition
*/
typedef struct _s_stack *stack;

/**
* @brief Stack elements type definition
*/
typedef char stack_elem;

/**
* @brief Creates an empty stack
* @return An empty stack
* 
* @details  PRE  : {true}
*           USAGE: s = stack_empty();
*           POS  : {s --> stack && stack_is_empty(s)}
*
*/
stack stack_empty(void);

/**
* @brief Inserts an element at the top of the stack
* @param s A stack
* @param e An element to push into the stack
* @return The same stack given by parameter 's' with 'e' at the top.
*         The returned pointer points to the same memory address that parameter
*         's'.
*
* @details  PRE  : {s --> stack}
*           USAGE: s = stack_push(s, e);
*           POS  : {s --> stack && !stack_is_empty(s)}
*/
stack stack_push(stack s, stack_elem e);

/**
* @brief Removes the element at the top of the stack
* @param s A stack
* @return The same stack given by parameter 's' with the top element removed.
*         The returned pointer points to the same memory address that parameter
*         's'.
* @note Only applies to non-empty stacks
*
* @details  PRE  : {s --> stack && !stack_is_empty(s)}
*           USAGE: s = stack_pop(s);
*           POS  : {s --> stack}
**/
stack stack_pop(stack s);

/**
* @brief Returns the size of the stack
* @param s A stack
* @return The size of the stack
*
*/
unsigned int stack_size(stack s);

/**
* @brief Writes in 'top' the element at the top of the stacks
* @param s A stacks
* @param top A pointer to the output variable where the top of the stack will
*            be stored.
* @note Only applies to non-empty stacks
*
* @details  PRE  : {s --> stack && !stack_is_empty(s) && e!=NULL}
*
* @example stack_elem e;
*          stack_top(s, &e);
*
*/
void stack_top(stack s, stack_elem *top);

/**
* @brief Check if the given stack is empty
* @param s A stack
* @return true if the stack is empty, false otherwise
*/
bool stack_is_empty(stack s);

/**
* @brief Creates an array with all the elements of the stack
* @param s A stack
* @return An array containing all the elements of the stack. The stack top element
* becomes the rightmost element of the array. The size of the resulting
* array is determined by 'stack_size(s)'
*/
stack_elem *stack_to_array(stack s);

/**
* @brief Destroys the stack
* @param s A stack
* @note All memory resources are freed
*/
stack stack_destroy(stack s);


#endif
