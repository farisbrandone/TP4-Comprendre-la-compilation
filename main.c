#include "calculatrice.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char expr[256];

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

    // Remove line break
    expr[strcspn(expr, "\n")] = 0;

    double result = evaluateExpression(expr);
    printf("Résultat: %f\n", result);

    return 0;
}
