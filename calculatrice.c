#include "calculatrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Global variables for tokens
Token tokens[MAXTOKENS];
Token outputQueue[MAXTOKENS];
Token opStack[MAXSTACK];
double evalStack[MAXSTACK];

int tokenCount = 0;
int outputCount = 0;
int opTop = -1;
int evalTop = -1;

// Pile of function
void pushOp(Token token) { opStack[++opTop] = token; }
Token popOp() { return opStack[opTop--]; }
void pushEval(double val) { evalStack[++evalTop] = val; }
double popEval() { return evalStack[evalTop--]; }

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

// Tokenisation
void tokenize(const char* expr) {
    const char* p = expr;
    tokenCount = 0;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // Numbers
        if (isdigit(*p) || *p == '.') {
            char numStr[32] = {0};
            int i = 0;

            while (*p && (isdigit(*p) || *p == '.' ||
                   *p == 'e' || *p == 'E' ||
                   ((*p == '-' || *p == '+') && (i > 0 && (numStr[i-1] == 'e' || numStr[i-1] == 'E'))))) {
                numStr[i++] = *p++;
            }

            tokens[tokenCount].type = NUMBER;
            tokens[tokenCount].value = atof(numStr);
            tokenCount++;
            continue;
        }

        // Operators
        if (strchr("+-*/^", *p)) {
            tokens[tokenCount].type = OPERATOR;
            tokens[tokenCount].str[0] = *p;
            tokens[tokenCount].str[1] = '\0';
            tokenCount++;
            p++;
            continue;
        }

        // Brackets
        if (*p == '(') {
            tokens[tokenCount].type = LEFTPAREN;
            strcpy(tokens[tokenCount].str, "(");
            tokenCount++;
            p++;
            continue;
        }

        if (*p == ')') {
            tokens[tokenCount].type = RIGHTPAREN;
            strcpy(tokens[tokenCount].str, ")");
            tokenCount++;
            p++;
            continue;
        }

        // Functions
        if (isalpha(*p)) {
            char func[32] = {0};
            int i = 0;

            while (isalpha(*p)) {
                func[i++] = *p++;
            }

            tokens[tokenCount].type = FUNCTION;
            strcpy(tokens[tokenCount].str, func);
            tokenCount++;
            continue;
        }

        fprintf(stderr, "Erreur: Caractère non reconnu '%c'\n", *p);
        exit(1);
    }
}

// Unary minus
void fixUnaryMinus() {
    for (int i = 0; i < tokenCount; i++) {
        if (strcmp(tokens[i].str, "-") == 0) {
            if (i == 0 || tokens[i-1].type == OPERATOR || tokens[i-1].type == LEFTPAREN) {
                strcpy(tokens[i].str, "u");
            }
        }
    }
}

// Shunting Yard
void shuntingYard() {
    outputCount = 0;
    opTop = -1;

    for (int i = 0; i < tokenCount; i++) {
        Token t = tokens[i];

        switch (t.type) {
            case NUMBER:
                outputQueue[outputCount++] = t;
                break;

            case FUNCTION:
                pushOp(t);
                break;

            case OPERATOR: {
                while (opTop >= 0 &&
                       opStack[opTop].type != LEFTPAREN &&
                       (getPriority(opStack[opTop].str) > getPriority(t.str) ||
                       (getPriority(opStack[opTop].str) == getPriority(t.str) &&
                       getAssociativity(t.str) == LEFT))) {
                    outputQueue[outputCount++] = popOp();
                }
                pushOp(t);
                break;
            }

            case LEFTPAREN:
                pushOp(t);
                break;

            case RIGHTPAREN:
                while (opTop >= 0 && opStack[opTop].type != LEFTPAREN) {
                    outputQueue[outputCount++] = popOp();
                }
                if (opTop < 0) {
                    fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
                    exit(1);
                }
                popOp(); // Delete '('

                if (opTop >= 0 && opStack[opTop].type == FUNCTION) {
                    outputQueue[outputCount++] = popOp();
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
        outputQueue[outputCount++] = popOp();
    }
}

//  RPN Elevation
double evalRpn() {
    evalTop = -1;

    for (int i = 0; i < outputCount; i++) {
        Token t = outputQueue[i];

        switch (t.type) {
            case NUMBER:
                pushEval(t.value);
                break;

            case OPERATOR:
                if (strcmp(t.str, "u") == 0) {
                    pushEval(-popEval());
                } else {
                    double b = popEval();
                    double a = popEval();

                    if (strcmp(t.str, "+") == 0) pushEval(a + b);
                    else if (strcmp(t.str, "-") == 0) pushEval(a - b);
                    else if (strcmp(t.str, "*") == 0) pushEval(a * b);
                    else if (strcmp(t.str, "/") == 0) {
                        if (b == 0) {
                            fprintf(stderr, "Erreur: Division par zéro\n");
                            exit(1);
                        }
                        pushEval(a / b);
                    }
                    else if (strcmp(t.str, "^") == 0) pushEval(pow(a, b));
                }
                break;

            case FUNCTION:
                double arg = popEval();
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
                pushEval(res);
                break;
        }
    }

    if (evalTop != 0) {
        fprintf(stderr, "Erreur: Expression invalide\n");
        exit(1);
    }

    return popEval();
}

//  Principal Function
double evaluateExpression(const char* expr) {
    tokenize(expr);
    fixUnaryMinus();
    shuntingYard();
    return evalRpn();
}
