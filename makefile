# Makefile for evaluation of expressions with handle extern library

# Définition du compilateur à utiliser (gcc dans ce cas)
CC = gcc

# Options de compilation :
# -Wall : Active tous les warnings standards
# -Wextra : Active des warnings supplémentaires
# -g : Inclut les informations de débogage pour GDB
CFLAGS = -Wall -Wextra -g

# Options de l'éditeur de liens :
# -lm : Lie avec la bibliothèque mathématique (libm)
LDFLAGS = -lm

# Répertoire où chercher les bibliothèques (ici le répertoire courant)
LIB_DIR = ./

# Nom de l'exécutable final
TARGET = calculatrice

# Liste des fichiers objets nécessaires pour créer l'exécutable
OBJ = calculatrice.o main.o

# Cible par défaut quand on lance juste 'make'
# Dépend de $(TARGET), donc construit l'exécutable
all: $(TARGET)

# Règle pour créer l'exécutable à partir des fichiers objets
# $@ représente le nom de la cible ($(TARGET))
# $^ représente toutes les dépendances ($(OBJ))
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) $(LDFLAGS)

# Règle générique pour compiler les fichiers .c en fichiers .o
# % est un wildcard qui correspond à n'importe quel nom
# $< représente le premier prérequis (le fichier .c)
# $@ représente la cible (le fichier .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cible pour nettoyer les fichiers générés
clean:
	rm -f $(OBJ) $(TARGET)

# Cible pour exécuter le programme après compilation
# Dépend de $(TARGET) pour s'assurer que le programme est à jour
run: $(TARGET)
	./$(TARGET)

# Déclare les cibles qui ne correspondent pas à des fichiers
# Évite les conflits si des fichiers nommés 'all', 'clean' ou 'run' existent
.PHONY: all clean run
