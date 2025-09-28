#include "shuntingYard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Global variables for tokens
/*Token tokens[MAXTOKENS];
Token outputQueue[MAXTOKENS];
Token opStack[MAXSTACK];
double evalStack[MAXSTACK];

int tokenCount = 0;
int outputCount = 0;
int opTop = -1;
int evalTop = -1;*/

// Fonctions of pile
void pushOp(Token token, Token *opStack ,int *opTop) { opStack[++*opTop] = token; }
Token popOp(Token *opStack ,int *opTop) { return opStack[*opTop--]; }


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


// Shunting Yard
void shuntingYard(Token *tokens, Token *outputQueue, Token *opStack , double *evalStack ,int *tokenCount, int *evalTop) {
   int outputCount = 0;
   int opTop = -1;

    for (int i = 0; i < *tokenCount; i++) {
        Token t = tokens[i];

        switch (t.type) {
            case NUMBER:
                outputQueue[outputCount++] = t;
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
                    outputQueue[outputCount++] = popOp(opStack, &opTop);
                }
                pushOp(t, opStack, &opTop);
                break;
            }

            case LEFTPAREN:
                pushOp(t, opStack, &opTop);
                break;

            case RIGHTPAREN:
                while (opTop >= 0 && opStack[opTop].type != LEFTPAREN) {
                    outputQueue[outputCount++] = popOp(opStack, &opTop);
                }
                if (opTop < 0) {
                    fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
                    exit(1);
                }
                popOp(opStack, &opTop); // Delete '('

                if (opTop >= 0 && opStack[opTop].type == FUNCTION) {
                    outputQueue[outputCount++] = popOp(opStack, &opTop);
                }
                break;
        }
    }

    // Empty the pile
    while (opTop >= 0) {
        if (opStack[opTop].type == LEFTPAREN) {
            fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
            exit(1);
        }
        outputQueue[outputCount++] = popOp(opStack, &opTop);
    }

   /* shuntingYardReturn result;
    result.tokenCount=tokenCount;

    int tokensArrayLength = sizeof(tokens) / sizeof(tokens[0]); // Calcul de la taille
    int outputQueueArrayLength = sizeof(outputQueue) / sizeof(outputQueue[0]); // Calcul de la taille
        // Boucle for pour parcourir le tableau
        for (int i = 0; i < tokensArrayLength; i++) {
            // Instructions à exécuter pour chaque élément
           result.tokens[i]=tokens[i]
        }

         for (int i = 0; i < outputQueueArrayLength; i++) {
            // Instructions à exécuter pour chaque élément
           result.outputQueue[i]=tokens[i]
        }

       return result;*/

       exit(0);
}
