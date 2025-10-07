#include "tokenize.h"
#include "fixUnaryMinus.h"
#include "shuntingYard.h"
#include "evalRpn.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


  char expr[256];
  Token tokens[MAXTOKENS];
  Token outputQueue[MAXTOKENS];
  Token opStack[MAXSTACK];
  double evalStack[MAXSTACK];

  int tokenCount = 0;
  int outputCount = 0;
  int opTop = -1;
  int evalTop = -1;

  typedef struct  {
    Token tokens[MAXTOKENS];
    int tokenCount;
    } fixUnaryReturn;

typedef struct  {
    Token tokens[MAXTOKENS];
    Token outputQueue[MAXTOKENS];
    int tokenCount;
    } shuntingYardReturn;



int main() {


    printf("o ---- o ---- o ---- o ---- o ---- o ---- o\n");
     usleep(1000000);
    printf("|");
    printf("                                         ");
    printf("|\n");
    usleep(1000000);
    printf("o      Super calculateur FARIS-G200       o\n");
    usleep(1000000);
    printf("|");
    printf("                                         ");
    printf("|\n");
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

    // Delete break line
    expr[strcspn(expr, "\n")] = 0;

   TokenizeReturn tokenResult = tokenize(expr, tokens);


        printf("TokenCount: %d\n", tokenResult.tokenCount);
           int tokensArrayLength = sizeof(tokenResult.tokens) / sizeof(tokenResult.tokens[0]); // Calcul de la taille

        // Boucle for pour parcourir le tableau
        for (int i = 0; i < tokensArrayLength; i++) {
            // Instructions à exécuter pour chaque élément
              printf("TokenArray: %f\n", tokenResult.tokens[i].value );

        }

         // Create tokenResult-like structure
    fixUnaryReturn tokenVariable;
    tokenVariable.tokenCount = 2;
    for (int i = 0; i < tokensArrayLength; i++) {
        tokenVariable.tokens[i] = tokenResult.tokens[i];
    }


    fixUnaryReturn fixUnaryMinusResult = fixUnaryMinus(tokenVariable.tokens, tokenVariable.tokenCount);

            printf("fixUnaryMinusCount: %d\n", fixUnaryMinusResult.tokenCount);
           int tokensArrayLength1 = sizeof(fixUnaryMinusResult.tokens) / sizeof(fixUnaryMinusResult.tokens[0]); // Calcul de la taille

        // Boucle for pour parcourir le tableau
        for (int i = 0; i < tokensArrayLength1; i++) {
            // Instructions à exécuter pour chaque élément
              printf("fixUnaryMinusArray: %f\n", fixUnaryMinusResult.tokens[i].value );

        }

  shuntingYardReturn shuntingYardResult = shuntingYard(fixUnaryMinusResult.tokens, outputQueue, opStack ,tokenCount, evalTop);

               int tokensArrayLength2 = sizeof(shuntingYardResult.tokens) / sizeof(shuntingYardResult.tokens[0]); // Calcul de la taille

          printf("shuntingYardLength: %d\n", tokensArrayLength2 );
        // Boucle for pour parcourir le tableau
        for (int i = 0; i < tokensArrayLength2; i++) {
            // Instructions à exécuter pour chaque élément
              printf("shuntingYardArray: %f\n", shuntingYardResult.tokens[i].value );
        }

    double result = evalRpn(shuntingYardResult.outputQueue, evalStack, shuntingYardResult.tokenCount);
    printf("Résultat: %f\n", result);
    return 0;
}
