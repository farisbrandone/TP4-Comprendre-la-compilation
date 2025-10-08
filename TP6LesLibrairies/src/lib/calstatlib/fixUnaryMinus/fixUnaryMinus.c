#include "fixUnaryMinus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

fixUnaryReturn fixUnaryMinus(Token *tokens, int tokenCount) {
    printf("Inside fixUnaryMinus with tokenCount: %d\n", tokenCount);

    fixUnaryReturn result;
    result.tokenCount = tokenCount;

    // Copier les tokens d'entrée vers la sortie
    for (int i = 0; i < tokenCount; i++) {
        result.tokens[i] = tokens[i];
    }

    // Appliquer la correction du moins unaire
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(result.tokens[i].str, "-") == 0) {
            if (i == 0 ||
                result.tokens[i-1].type == OPERATOR ||
                result.tokens[i-1].type == LEFTPAREN) {
                strcpy(result.tokens[i].str, "u");
            }
        }
    }

    return result;
}
