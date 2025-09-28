
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Global variables for tokens
/*Token tokens[MAXTOKENS];

int tokenCount = 0;*/


// Tokenisation
void tokenize(const char* expr, Token *tokens) {
    const char* p = expr;
   int tokenCount = 0;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // Nombers
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

         /*TokenizeReturn result;

        result.tokenCount=tokenCount;
        int tokensArrayLength = sizeof(tokens) / sizeof(tokens[0]); // Calcul de la taille

        // Boucle for pour parcourir le tableau
        for (int i = 0; i < tokensArrayLength; i++) {
            // Instructions à exécuter pour chaque élément
           result.tokens[i]=tokens[i]
        }

       return result;*/
        exit(1);
    }
}
