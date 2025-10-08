#include "evalRpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Fonctions de pile CORRIGÉES (passage par pointeur)
void pushEval(double val, double *evalStack, int *evalTop) {
    evalStack[++(*evalTop)] = val;
}

double popEval(double *evalStack, int *evalTop) {
    return evalStack[(*evalTop)--];
}

// RPN Evaluation CORRIGÉE
double evalRpn(Token *outputQueue, int outputCount) {
    printf("Inside evalRpn with outputCount: %d\n", outputCount);

    double evalStack[MAXSTACK];
    int evalTop = -1;

    for (int i = 0; i < outputCount; i++) {
        Token t = outputQueue[i];

        switch (t.type) {
            case NUMBER:
                pushEval(t.value, evalStack, &evalTop);
                break;

            case OPERATOR:
                if (strcmp(t.str, "u") == 0) {
                    // Moins unaire
                    double operand = popEval(evalStack, &evalTop);
                    pushEval(-operand, evalStack, &evalTop);
                } else {
                    // Opérateurs binaires
                    double b = popEval(evalStack, &evalTop);
                    double a = popEval(evalStack, &evalTop);

                    if (strcmp(t.str, "+") == 0)
                        pushEval(a + b, evalStack, &evalTop);
                    else if (strcmp(t.str, "-") == 0)
                        pushEval(a - b, evalStack, &evalTop);
                    else if (strcmp(t.str, "*") == 0)
                        pushEval(a * b, evalStack, &evalTop);
                    else if (strcmp(t.str, "/") == 0) {
                        if (b == 0) {
                            fprintf(stderr, "Erreur: Division par zéro\n");
                            exit(1);
                        }
                        pushEval(a / b, evalStack, &evalTop);
                    }
                    else if (strcmp(t.str, "^") == 0)
                        pushEval(pow(a, b), evalStack, &evalTop);
                }
                break;

            case FUNCTION:
                double arg = popEval(evalStack, &evalTop);
                double res;

                if (strcmp(t.str, "sin") == 0)
                    res = sin(arg * M_PI / 180.0); // Conversion degrés -> radians
                else if (strcmp(t.str, "cos") == 0)
                    res = cos(arg * M_PI / 180.0);
                else if (strcmp(t.str, "tan") == 0)
                    res = tan(arg * M_PI / 180.0);
                else if (strcmp(t.str, "log") == 0) {
                    if (arg <= 0) {
                        fprintf(stderr, "Erreur: Logarithme non défini\n");
                        exit(1);
                    }
                    res = log10(arg); // Log base 10
                }
                else if (strcmp(t.str, "ln") == 0) {
                    if (arg <= 0) {
                        fprintf(stderr, "Erreur: Logarithme naturel non défini\n");
                        exit(1);
                    }
                    res = log(arg); // Log naturel
                }
                else if (strcmp(t.str, "exp") == 0)
                    res = exp(arg);
                else {
                    fprintf(stderr, "Fonction non supportée: %s\n", t.str);
                    exit(1);
                }
                pushEval(res, evalStack, &evalTop);
                break;

            default:
                fprintf(stderr, "Erreur: Type de token non géré dans evalRpn\n");
                exit(1);
        }
    }

    if (evalTop != 0) {
        fprintf(stderr, "Erreur: Expression invalide (evalTop = %d)\n", evalTop);
        exit(1);
    }

    return popEval(evalStack, &evalTop);
}
