#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

TokenizeReturn tokenize(const char* expr) {
    fprintf(stderr, "Inside Tokenize with '%s'\n", expr);

    const char* p = expr;
    TokenizeReturn result;
    result.tokenCount = 0;  // Initialiser le compteur

    while (*p && result.tokenCount < MAXTOKENS) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        // Numbers
        if (isdigit(*p) || *p == '.') {
            char numStr[32] = {0};
            int i = 0;

            while (*p && (isdigit(*p) || *p == '.' ||
                   *p == 'e' || *p == 'E' ||
                   ((*p == '-' || *p == '+') && (i > 0 && (numStr[i-1] == 'e' || numStr[i-1] == 'E'))))) {
                if (i < 31) {  // Éviter le débordement
                    numStr[i++] = *p;
                }
                p++;
            }

            result.tokens[result.tokenCount].type = NUMBER;
            result.tokens[result.tokenCount].value = atof(numStr);
            result.tokenCount++;
            continue;
        }

        // Operators
        if (strchr("+-*/^", *p)) {
            result.tokens[result.tokenCount].type = OPERATOR;
            result.tokens[result.tokenCount].str[0] = *p;
            result.tokens[result.tokenCount].str[1] = '\0';
            result.tokenCount++;
            p++;
            continue;
        }

        // Parentheses
        if (*p == '(') {
            result.tokens[result.tokenCount].type = LEFTPAREN;
            strcpy(result.tokens[result.tokenCount].str, "(");
            result.tokenCount++;
            p++;
            continue;
        }

        if (*p == ')') {
            result.tokens[result.tokenCount].type = RIGHTPAREN;
            strcpy(result.tokens[result.tokenCount].str, ")");
            result.tokenCount++;
            p++;
            continue;
        }

        // Functions
        if (isalpha(*p)) {
            char func[32] = {0};
            int i = 0;

            while (isalpha(*p) && i < 31) {
                func[i++] = *p++;
            }

            result.tokens[result.tokenCount].type = FUNCTION;
            strcpy(result.tokens[result.tokenCount].str, func);
            result.tokenCount++;
            continue;
        }

        fprintf(stderr, "Erreur: Caractère non reconnu '%c'\n", *p);
        exit(1);
    }

    return result;
}
