#include <stdio.h>
#include "functions.h"

void function1() {
    printf("Entrée dans function1\n");
    function2();
    printf("Sortie de function1\n");
}

void function2() {
    printf("Entrée dans function2\n");
  int f2= function3();
    printf("Sortie de function2\n: %d\n", f2);
}

int function3() {
    printf("Entrée dans function3\n");
int f4=function4()*3;
    printf("Sortie de function3\n: %d\n", f4);

    return f4;
}

int function4() {
    printf("Entrée dans function4\n");

    // Création d'un tableau et accès hors limites
    int tableau[5] = {1, 2, 3, 4, 5};

    // Accès normal
    printf("Element à l'indice 2: %d\n", tableau[2]);

    // Accès HORS LIMITES
    printf("Element à l'indice 10 (hors limites): %d\n", tableau[10]);

    int f5= function5()*4;
    printf("Sortie de function4\n: %d\n ",f5 );
    return f5;
}

int function5() {
    printf("Entrée dans function5\n");
    printf("Sortie de function5\n");
    return 5;
}
