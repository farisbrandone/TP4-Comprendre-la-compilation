#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>
#include "tokenType.h"


typedef struct  {

    Token tokens[MAXTOKENS];
    int tokenCount;
    } TokenizeReturn;
// Prototypes of functions
TokenizeReturn tokenize(const char* expr);

#endif
