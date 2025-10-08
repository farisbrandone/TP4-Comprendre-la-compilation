#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <stdbool.h>
#include "tokenType.h"

typedef struct {
    Token outputQueue[MAXTOKENS];
    int outputCount;
} shuntingYardReturn;

// Prototype simplifié - la fonction gère ses propres piles
shuntingYardReturn shuntingYard(Token *tokens, int tokenCount);

#endif
