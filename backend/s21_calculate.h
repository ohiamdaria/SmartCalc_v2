#ifndef CALCULATE_H_
#define CALCULATE_H_

#define ln(x) log(x)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char a[256]; // данные
  unsigned int n; // сколько элементов хранится в стеке
  size_t size;
} Stack;

typedef struct {
  double a[256]; // данные
  unsigned int n; // сколько элементов хранится в стеке
  size_t size;
} Stack_number;

typedef struct {
  double x;
  double result;
  int code;
} data_task_t;

#define OK 0
#define ERROR 1

// calc
void smart_calc(char *str, data_task_t *data);
void calc(char *s, data_task_t *data);
double parser_numbers(char *str);

// working with stack(numbers)
void init_stackn(Stack_number *st);
double popn(Stack_number *st);
void pushn(Stack_number *st, double data);
int peekn(Stack_number *head);
void printn(Stack_number *st);
// int check_priority(char k);

// for notation
void notation(char *str, char *str_output, Stack *stack);
char *add_space_to_str(char *str);
char *from_str_to_notation(char *str, data_task_t *data);
// helpers
char *change_functions_in_str(char *str);
char *add_current_symbol(char *str_output, char current_symbol);
char *add_from_stack(char *str, char *str_output, Stack *stack, int cases);
char *add_numbers(char *str, char *str_output);
int check_unary_minus_plus(char *str, char current_op);
int check_priority(char k);
// working with stack
void init_stack(Stack *st);
char pop(Stack *st);
void push(Stack *st, int data);
int peek(Stack *head);
void print(Stack *st);
void deleteStack(Stack *st);
char *add_null_to_str(char *str);

// find error func
void init_input(data_task_t *data);
void catch_a_beach(char *str, data_task_t *data);
int count_braces(char *str);

#endif // CALCULATE_H_
