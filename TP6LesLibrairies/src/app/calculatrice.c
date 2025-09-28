#include "tokenize.h"
#include "fixUnaryMinus.h"
#include "shuntingYard.h"
#include "evalRpn.h"

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


//  principal Function
double evaluateExpression(const char* expr) {
    tokenize(expr, tokens);
    fixUnaryMinus(tokens, &tokenCount);
    shuntingYard(tokens, outputQueue, opStack , evalStack ,&tokenCount, &evalTop);
    return evalRpn(outputQueue, evalStack, &outputCount);
}
