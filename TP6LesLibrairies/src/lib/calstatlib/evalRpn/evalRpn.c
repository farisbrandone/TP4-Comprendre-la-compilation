#include "evalRpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Global variables for tokens

/*Token outputQueue[MAXTOKENS];
Token opStack[MAXSTACK];
double evalStack[MAXSTACK];


int outputCount = 0;
int opTop = -1;
int evalTop = -1;*/

// Fonctions of pile

void pushEval(double val, double *evalStack,int *evalTop) { evalStack[++*evalTop] = val; }
double popEval(double *evalStack, int *evalTop) { return evalStack[*evalTop--];}

// RPN Evaluation
double evalRpn(Token *outputQueue, double *evalStack, int *outputCount) {
  int  evalTop = -1;

    for (int i = 0; i < *outputCount; i++) {
        Token t = outputQueue[i];

        switch (t.type) {
            case NUMBER:
                pushEval(t.value, evalStack, &evalTop);
                break;

            case OPERATOR:
                if (strcmp(t.str, "u") == 0) {
                    pushEval(-popEval(evalStack, &evalTop), evalStack, &evalTop);
                } else {
                    double b = popEval(evalStack, &evalTop);
                    double a = popEval(evalStack, &evalTop);

                    if (strcmp(t.str, "+") == 0) pushEval(a + b, evalStack, &evalTop);
                    else if (strcmp(t.str, "-") == 0) pushEval(a - b, evalStack, &evalTop);
                    else if (strcmp(t.str, "*") == 0) pushEval(a * b, evalStack, &evalTop);
                    else if (strcmp(t.str, "/") == 0) {
                        if (b == 0) {
                            fprintf(stderr, "Erreur: Division par zéro\n");
                            exit(1);
                        }
                        pushEval(a / b, evalStack, &evalTop);
                    }
                    else if (strcmp(t.str, "^") == 0) pushEval(pow(a, b), evalStack, &evalTop);
                }
                break;

            case FUNCTION:
                double arg = popEval(evalStack, &evalTop);
                double res;

                if (strcmp(t.str, "sin") == 0) res = sin(arg);
                else if (strcmp(t.str, "cos") == 0) res = cos(arg);
                else if (strcmp(t.str, "tan") == 0) res = tan(arg);
                else if (strcmp(t.str, "log") == 0) {
                    if (arg <= 0) {
                        fprintf(stderr, "Erreur: Logarithme non défini\n");
                        exit(1);
                    }
                    res = log(arg);
                }
                else if (strcmp(t.str, "exp") == 0) res = exp(arg);
                else {
                    fprintf(stderr, "Fonction non supportée: %s\n", t.str);
                    exit(1);
                }
                pushEval(res, evalStack, &evalTop);
                break;
        }
    }

    if (evalTop != 0) {
        fprintf(stderr, "Erreur: Expression invalide\n");
        exit(1);
    }

    return popEval(evalStack, &evalTop);
}
