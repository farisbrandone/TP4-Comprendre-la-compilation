# 🧮 Projet Calculatrice

Dans ce projet nous avons mis en place un programme écrit en C qui permet de faire des opérations suivantes :
- **Arithmétique simple** (+, -, *, /)
- **Trigonométrie**
- **Fonctions logarithmiques**

---


## 🚀 Commande manuelle pour la compilation associée aux librairies statique

```bash
gcc -g -c src/lib/calstatlib/evalRpn/evalRpn.c -o src/build/evalRpn/evalRpn.o -I src/lib/calstatlib/tokenType
ar rcs src/build/evalRpn/evalRpn.a src/build/evalRpn/evalRpn.o

gcc -g -c src/lib/calstatlib/fixUnaryMinus/fixUnaryMinus.c -o src/build/fixUnaryMinus/fixUnaryMinus.o -I src/lib/calstatlib/tokenType
ar rcs src/build/fixUnaryMinus/fixUnaryMinus.a src/build/fixUnaryMinus/fixUnaryMinus.o

gcc -g -c src/lib/calstatlib/shuntingYard/shuntingYard.c -o src/build/shuntingYard/shuntingYard.o -I src/lib/calstatlib/tokenType
ar rcs src/build/shuntingYard/shuntingYard.a src/build/shuntingYard/shuntingYard.o

gcc -g -c src/lib/calstatlib/tokenize/tokenize.c -o src/build/tokenize/tokenize.o -I src/lib/calstatlib/tokenType
ar rcs src/build/tokenize/tokenize.a src/build/tokenize/tokenize.o

gcc -g -c -I./src/lib/calstatlib/tokenize -I./src/lib/calstatlib/shuntingYard -I./src/lib/calstatlib/fixUnaryMinus -I./src/lib/calstatlib/evalRpn src/app/calculatrice.c -o src/build/app/calculatrice.o


gcc -g -I./src/lib/calstatlib/tokenize -I./src/lib/calstatlib/shuntingYard -I./src/lib/calstatlib/fixUnaryMinus -I./src/lib/calstatlib/evalRpn -I src/lib/calstatlib/tokenType -c src/app/main.c -o src/build/app/main.o


gcc -g src/build/app/main.o -o src/bin/exeWithLib \
    -L./src/build/evalRpn -l:evalRpn.a\
    -L./src/build/fixUnaryMinus -l:fixUnaryMinus.a\
    -L./src/build/shuntingYard -l:shuntingYard.a\
    -L./src/build/tokenize -l:tokenize.a\
    -lm


 ./src/bin/exeWithLib

```

## 🚀 : Commande pour la compilation associées aux librairies dynamiques

```bash
 gcc -g -fPIC -c src/lib/calstatlib/evalRpn/evalRpn.c -o src/buildForDynamiqueLib/evalRpn/evalRpn.o -I src/lib/calstatlib/tokenType
gcc -shared -o src/buildForDynamiqueLib/evalRpn/evalRpn.so src/buildForDynamiqueLib/evalRpn/evalRpn.o -lm

gcc -g -fPIC -c src/lib/calstatlib/fixUnaryMinus/fixUnaryMinus.c -o src/buildForDynamiqueLib/fixUnaryMinus/fixUnaryMinus.o -I src/lib/calstatlib/tokenType
gcc -shared -o src/buildForDynamiqueLib/fixUnaryMinus/fixUnaryMinus.so src/buildForDynamiqueLib/fixUnaryMinus/fixUnaryMinus.o

gcc -g -fPIC -c src/lib/calstatlib/shuntingYard/shuntingYard.c -o src/buildForDynamiqueLib/shuntingYard/shuntingYard.o -I src/lib/calstatlib/tokenType
gcc -shared -o src/buildForDynamiqueLib/shuntingYard/shuntingYard.so src/buildForDynamiqueLib/shuntingYard/shuntingYard.o

gcc -g -fPIC -c src/lib/calstatlib/tokenize/tokenize.c -o src/buildForDynamiqueLib/tokenize/tokenize.o -I src/lib/calstatlib/tokenType
gcc -shared -o src/buildForDynamiqueLib/tokenize/tokenize.so src/buildForDynamiqueLib/tokenize/tokenize.o -lm

gcc -g -I./src/lib/calstatlib/tokenize -I./src/lib/calstatlib/shuntingYard -I./src/lib/calstatlib/fixUnaryMinus -I./src/lib/calstatlib/evalRpn -I src/lib/calstatlib/tokenType -c src/app/main.c -o src/buildForDynamiqueLib/app/main.o



gcc -g src/buildForDynamiqueLib/app/main.o -o src/bin/exeWithDynLib\
    -I src/buildForDynamiqueLib/evalRpn \
    -I src/buildForDynamiqueLib/fixUnaryMinus \
    -I src/buildForDynamiqueLib/shuntingYard \
    -I src/buildForDynamiqueLib/tokenize \
    src/buildForDynamiqueLib/evalRpn/evalRpn.so \
    src/buildForDynamiqueLib/fixUnaryMinus/fixUnaryMinus.so \
    src/buildForDynamiqueLib/shuntingYard/shuntingYard.so \
    src/buildForDynamiqueLib/tokenize/tokenize.so \
    -lm


./src/bin/exeWithDynLib
```

