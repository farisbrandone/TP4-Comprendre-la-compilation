#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

#define MAXTOKENS 100
#define MAXSTACK 100

typedef enum {
    NUMBER,
    OPERATOR,
    FUNCTION,
    LEFTPAREN,
    RIGHTPAREN
} TokenType;

typedef struct {
    TokenType type;
    char str[32];
    double value;
} Token;

/*typedef struct  {

    Token tokens[MAXTOKENS];
    int tokenCount;
    } TokenizeReturn;*/
// Prototypes of functions
void tokenize(const char* expr, Token *tokens);

#endif
