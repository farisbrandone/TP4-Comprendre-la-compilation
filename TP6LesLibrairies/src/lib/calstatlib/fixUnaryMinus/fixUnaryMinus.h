#ifndef FIX_UNARY_MINUS_H
#define FIX_UNARY_MINUS_H

#include "tokenType.h"

typedef struct {
    Token tokens[MAXTOKENS];
    int tokenCount;
} fixUnaryReturn;

fixUnaryReturn fixUnaryMinus(Token *tokens, int tokenCount);

#endif
