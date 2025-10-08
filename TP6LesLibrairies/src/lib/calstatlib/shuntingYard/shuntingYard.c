#include "shuntingYard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Fonctions de pile CORRIGÉES (passage par pointeur)
void pushOp(Token token, Token *opStack, int *opTop) {
    opStack[++(*opTop)] = token;
}

Token popOp(Token *opStack, int *opTop) {
    return opStack[(*opTop)--];
}

// Priority of operators
int getPriority(char* op) {
    if (strcmp(op, "u") == 0) return 5;
    if (strcmp(op, "^") == 0) return 4;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 3;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 2;
    return 0;
}

// Associativity
typedef enum { LEFT, RIGHT } Associativity;
Associativity getAssociativity(char* op) {
    if (strcmp(op, "^") == 0 || strcmp(op, "u") == 0) return RIGHT;
    return LEFT;
}

// Shunting Yard CORRIGÉ
shuntingYardReturn shuntingYard(Token *tokens, int tokenCount) {
    printf("Inside shuntingYard with tokenCount: %d\n", tokenCount);

    shuntingYardReturn result;
    result.outputCount = 0;

    Token outputQueue[MAXTOKENS];
    Token opStack[MAXSTACK];
    int opTop = -1;

    for (int i = 0; i < tokenCount; i++) {
        Token t = tokens[i];

        switch (t.type) {
            case NUMBER:
                outputQueue[result.outputCount++] = t;
                break;

            case FUNCTION:
                pushOp(t, opStack, &opTop);
                break;

            case OPERATOR: {
                while (opTop >= 0 &&
                       opStack[opTop].type != LEFTPAREN &&
                       (getPriority(opStack[opTop].str) > getPriority(t.str) ||
                       (getPriority(opStack[opTop].str) == getPriority(t.str) &&
                       getAssociativity(t.str) == LEFT))) {
                    outputQueue[result.outputCount++] = popOp(opStack, &opTop);
                }
                pushOp(t, opStack, &opTop);
                break;
            }

            case LEFTPAREN:
                pushOp(t, opStack, &opTop);
                break;

            case RIGHTPAREN:
                while (opTop >= 0 && opStack[opTop].type != LEFTPAREN) {
                    outputQueue[result.outputCount++] = popOp(opStack, &opTop);
                }
                if (opTop < 0) {
                    fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
                    exit(1);
                }
                popOp(opStack, &opTop); // Supprimer '('

                if (opTop >= 0 && opStack[opTop].type == FUNCTION) {
                    outputQueue[result.outputCount++] = popOp(opStack, &opTop);
                }
                break;
        }
    }

    // Vider la pile
    while (opTop >= 0) {
        if (opStack[opTop].type == LEFTPAREN) {
            fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
            exit(1);
        }
        outputQueue[result.outputCount++] = popOp(opStack, &opTop);
    }

    // Copier la file de sortie dans le résultat
    for (int i = 0; i < result.outputCount; i++) {
        result.outputQueue[i] = outputQueue[i];
    }

    return result;
}
