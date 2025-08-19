# 🧮 Projet Calculatrice

Dans ce projet nous avons mis en place un programme écrit en C qui permet de faire des opérations suivantes :
- **Arithmétique simple** (+, -, *, /)
- **Trigonométrie**
- **Fonctions logarithmiques**

---

## 📁 Etape 0 : Structure du projet

Le projet comporte les fichiers suivants issus des programmes écrits et de la compilation :
`calculatrice.h`, `calculatrice.c`, `main.c`, `calculatrice.o`, `main.o`

*   **`calculatrice.h`** (extension `.h`) : utilisé pour la déclaration des fonctions et structures
*   **`calculatrice.c`** (extension `.c`) : utilisé pour l'implémentation des fonctions issues de `calculatrice.h`
*   **`main.c`** : programme principal, point d'entrée pour l'utilisateur, lieu d'appel des différentes fonctions déclarées dans `calculatrice.c`. C'est le fichier qui réalise les instructions d'exécution.

Suivez les étapes ci-dessous et exécutez les commandes suivantes pour compiler le programme enfin d'effectuer les opérations.

---

## 🚀 Etape 1 : Cloner le repository

```bash
git clone git@github.com:farisbrandone/TP4-Comprendre-la-compilation.git
cd TP4-Comprendre-la-compilation
```

## Étape 2 : Explorer la structure du projet

```bash
ls -la
```
## Phase 1 : Compilation

Cette phase permet d'obtenir le fichier object (.o) et comporte :
- Le traitement par le préprocesseur
- La compilation proprement dite
- L'assemblage

### Commandes à exécuter (dans le dossier du projet) :

```bash
gcc -c calculatrice.c -o calculatrice.o
gcc -c main.c -o main.o
```
## Phase 2 : Édition des liens

Dans cette phase :
- Les fichiers object obtenus de la compilation sont liés entre eux
- Sont ajoutés les fichiers objects correspondants aux librairies précompilées ayant pour extension (.a)

### Commande à exécuter :

```bash
gcc calculatrice.o main.o -L./ -lm -o calculatrice
```
-  **`bash -L./`** permet de lier calculatrice.o à main.o et **`-lm`** pour lier main.o avec les librairies mathématique. 

### Si vous souhaiter n'activer que l'étape :
 
- de traitement par le preprocesseur pendant la compilation alors taper la commande suivante:
    
```bash
    gcc -E calculatrice.c -o calculatrice.i
```
- de preprocesseur et de compilation et obtenir un fichier assembleur alors taper la commande suivante:
```bash
    gcc -S calculatrice.c -o calculatrice.s
```
- produire des infos symbolique au deboguage pour une compilation complète en une seule fois
```bash
    gcc -g calculatrice.c -o calculatrice
```

## Etape4: Exécution
 
 une fois l'etape de compilation terminer nous obtenons un fichier dit   **`EXÉCUTABLE`** nommé `calculatrice`
 
 * Commande pour lancer l'exécutable
```bash
  ./calculatrice
```

## Dans le cas avec un fichier Makefile, voici les commande à exécuter

```bash
  make clean
  make run
```
 
### Resultat
- ![Second Branch](./capture/resultat.png)



