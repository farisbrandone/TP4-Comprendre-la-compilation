
#include "fixUnaryMinus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Global variables for tokens


// Unary minus
void fixUnaryMinus(Token *tokens, int *tokenCount ) {
    for (int i = 0; i < *tokenCount; i++) {
        if (strcmp(tokens[i].str, "-") == 0) {
            if (i == 0 || tokens[i-1].type == OPERATOR || tokens[i-1].type == LEFTPAREN) {
                strcpy(tokens[i].str, "u");
            }
        }
    }

    /*TokenizeReturn result;
    result.tokenCount=tokenCount;
    int tokensArrayLength = sizeof(tokens) / sizeof(tokens[0]); // Calcul de la taille

        // Boucle for pour parcourir le tableau
    for (int i = 0; i < tokensArrayLength; i++) {
            // Instructions à exécuter pour chaque élément
         result.tokens[i]=tokens[i]
    }

    return result;*/
    exit(0);
}
