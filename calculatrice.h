
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_STACK 100

typedef enum {
    NUMBER,
    OPERATOR,
    FUNCTION,
    LEFT_PAREN,
    RIGHT_PAREN
} TokenType;

typedef struct {
    TokenType type;
    char str[32];
    double value;
} Token;

// Prototypes des fonctions
void tokenize(const char* expr);
void fix_unary_minus();
void shunting_yard();
double eval_rpn();
double evaluate_expression(const char* expr);

#endif
