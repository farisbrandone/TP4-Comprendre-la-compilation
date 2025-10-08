#include "fixUnaryMinus.h"
#include "shuntingYard.h"
#include "evalRpn.h"
#include "tokenize.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char expr[256];

    printf("o ---- o ---- o ---- o ---- o ---- o ---- o\n");
    usleep(1000000);
    printf("|                                         |\n");
    usleep(1000000);
    printf("o      Super calculateur FARIS-G200       o\n");
    usleep(1000000);
    printf("|                                         |\n");
    usleep(1000000);
    printf("o ---- o ---- o ---- o ---- o ---- o ---- o\n\n");
    usleep(1000000);
    printf("Bienvenue sur le super calculateur FARIS-G200\n ");
    usleep(1000000);
    printf("Ici nous calculons tous:\n");
    usleep(1000000);
    printf("- Opérations simple(+, -, *, /)\n");
    usleep(1000000);
    printf("- Trigonométrie(cos, sin, tan)\n");
    usleep(1000000);
    printf("- Fonction logarithmique\n\n");
    usleep(1000000);
    printf("Exemple d'entrée d'opération à faire:\n");
    usleep(1000000);
    printf("(2*cos(30)+3)/2\n\n");
    usleep(1000000);
    printf("Commencons à calculer,\n");
    usleep(1000000);
    printf("Entrer une opération comme indiqué ci-dessus et appuyer sur entrée\n");

    if (!fgets(expr, sizeof(expr), stdin)) {
        fprintf(stderr, "Erreur de lecture\n");
        return 1;
    }

    // Supprimer le saut de ligne
    expr[strcspn(expr, "\n")] = 0;

    // Tokenization
    TokenizeReturn tokenResult = tokenize(expr);
    printf("TokenCount: %d\n", tokenResult.tokenCount);

    // Afficher les tokens
    for (int i = 0; i < tokenResult.tokenCount; i++) {
        printf("Token %d: type=%d, str=%s, value=%.2f\n",
               i, tokenResult.tokens[i].type, tokenResult.tokens[i].str, tokenResult.tokens[i].value);
    }

    // Fix unary minus
    fixUnaryReturn fixUnaryMinusResult = fixUnaryMinus(tokenResult.tokens, tokenResult.tokenCount);
    printf("fixUnaryMinusCount: %d\n", fixUnaryMinusResult.tokenCount);

    for (int i = 0; i < fixUnaryMinusResult.tokenCount; i++) {
        printf("fixUnaryMinusToken %d: type=%d, str=%s, value=%.2f\n",
               i, fixUnaryMinusResult.tokens[i].type, fixUnaryMinusResult.tokens[i].str, fixUnaryMinusResult.tokens[i].value);
    }

    // Shunting Yard
    shuntingYardReturn shuntingYardResult = shuntingYard(fixUnaryMinusResult.tokens, fixUnaryMinusResult.tokenCount);
    printf("shuntingYardOutputCount: %d\n", shuntingYardResult.outputCount);

    for (int i = 0; i < shuntingYardResult.outputCount; i++) {
        printf("shuntingYardOutput %d: type=%d, str=%s, value=%.2f\n",
               i, shuntingYardResult.outputQueue[i].type, shuntingYardResult.outputQueue[i].str, shuntingYardResult.outputQueue[i].value);
    }

    // Évaluation RPN
    double result = evalRpn(shuntingYardResult.outputQueue, shuntingYardResult.outputCount);
    printf("Résultat final: %f\n", result);

    return 0;
}
