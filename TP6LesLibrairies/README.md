# 🧮 Projet Calculatrice

Dans ce projet nous avons mis en place un programme écrit en C qui permet de faire des opérations suivantes :
- **Arithmétique simple** (+, -, *, /)
- **Trigonométrie**
- **Fonctions logarithmiques**

---

# PARTIE CMAKE

## Introduction
+ CMake est un outil simplifié permettant la
compilation de sources C et C++.
+ C'est un outil multi-plateformes sous licence
BSD
+ Nécessite la présence d'un fichier
CMakeLists.txt
+ Effectue une gestion automatique des dépendances
+ Il est Simple d'utilisation / facile à prendre en main

## CMAKE CROSS PLATFORM
cmake est un système de compilation crossplateformes. Il ne compile pas directement mais
génère des fichiers dans différents formats :

+ Makefile
+ projet Visual Studio
+ Borland Makefile
+ projet Xcode
+ Kate
+ …

cmake utilise les fichiers CMakeLists.txt et génère
des fichiers en fonction de la plate-forme de
compilation (Makefile, visual, xcode….).

## CMAKE COMME LANGUAGE
Ici nous allons resortir et montrer comment utiliser ,les commandes , les fonctions , les boucles etc. lors
de l'écriture d'un fichier CMakeLists.txt

### Configuration du project
```bash
 cmake_minimum_required(VERSION 3.10)
project(NomProjet [LANGUAGES] [C] [CXX])

exemple:
cmake_minimum_required(VERSION 3.10)
# Définition du projet
project(Calculatrice C)
```

### Déclaration et utilisation de variable
### La déclaration de variables :
* set(NAME VALUE)
* ${NAME} utiliser si on souhaite recupurer la valeur pour une utilisation par exemple afficher un message:
  ```bash
  set(NAME "HelloWorld")

message(STATUS "La valeur de NAME est : ${NAME}")
1. Rôle de STATUS dans la founction message
* STATUS est un mode de message qui indique que le message est une information générale sur l'état de la configuration.
* Les messages en mode STATUS sont affichés de manière propre et standardisée dans la sortie de CMake, généralement préfixés par -- .
* Ils sont conçus pour informer l'utilisateur de ce qui se passe pendant la configuration, sans être intrusifs (contrairement aux erreurs ou aux avertissements).
```

* la declaration peut egalement se faire lors de l'appel à cmake via la ligne de commande lors de la generation
```bash
cmake -DNAME=VALUE ...
```

### Priorité des variables dans CMake
*Variable de cache (-DNAME=VALUE)*
+ Définie via la ligne de commande : cmake -DNAME=VALUE ...
+ Stockée dans CMakeCache.txt.
+ Persiste entre les exécutions de CMake.
+ Priorité élevée : Une variable de cache écrase une variable normale définie avec set(NAME VALUE) dans le fichier CMakeLists.txt, ce ci meme si la variable dans set est defini avec l'option cache'
```bash
set(BUILD_TESTS ON CACHE BOOL "Construire les tests unitaires (désactiver pour les builds de production)")

remarque: dans cmake les valeurs de type BOOL ou bolleem sont soit ON pour 1 et OFF pour 0
```

*Variable normale (set(NAME VALUE))*
+ Définie dans CMakeLists.txt : set(NAME VALUE)
+ N'est pas stockée dans le cache.
+ Existe uniquement pendant la configuration actuelle.
+ Priorité faible : Si une variable de cache du même nom existe, la variable normale est ignorée.

*4. Comment forcer une valeur dans le script ?*
Si vous voulez forcer une valeur dans le script CMakeLists.txt, même si une variable de cache existe, utilisez :
+ FORCE : Écrasera toute valeur existante (même celle définie via -D).
```bash
set(MY_VAR "valeur_forcée" CACHE STRING "Description" FORCE)
```

### Variables standards:
- CMAKE_INCLUDE_PATH (pour les .h)
```bash
Rôle : Spécifie une liste de répertoires où CMake doit chercher les fichiers d’en-tête (.h).
Utilisation : Utile pour trouver des bibliothèques externes non installées dans des chemins standards.
Exemple :
 cmake -DCMAKE_INCLUDE_PATH=/chemin/vers/les/includes ..
Dans CMakeLists.txt :
 include_directories(${CMAKE_INCLUDE_PATH})
```
- CMAKE_LIBRARY_PATH (pour la recherche de .so)
```bash
Rôle : Spécifie une liste de répertoires où CMake doit chercher les bibliothèques partagées (.so, .dll).
Utilisation : Permet de localiser des bibliothèques externes.
Exemple :
 cmake -DCMAKE_LIBRARY_PATH=/chemin/vers/les/bibliothèques ..
 Dans CMakeLists.txt :
 find_library(MY_LIB libfoo.so PATHS ${CMAKE_LIBRARY_PATH})

```
- DESTDIR (pour l'installation)
```bash
Rôle : Définit un préfixe temporaire pour l’installation. Utile pour créer des paquets ou installer dans un répertoire temporaire avant de copier les fichiers vers leur destination finale.
Utilisation : Souvent utilisé avec make install.
Exemple :
 make DESTDIR=/tmp/staging install
Cela installera les fichiers dans /tmp/staging/<prefix>, où <prefix> est défini par CMAKE_INSTALL_PREFIX
```
- CMAKE_BUILD_TYPE (Debug, Release)
```bash
Rôle : Définit le type de build (Debug, Release, RelWithDebInfo, MinSizeRel).
Utilisation : Influence les flags de compilation et les optimisations.
Exemple :
 cmake -DCMAKE_BUILD_TYPE=Debug ..
 Dans CMakeLists.txt :
 if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build en mode Debug")
endif()

```
*Dans le CMakeLists.txt :*
- CMAKE_C_FLAGS/ CMAKE_CXX_FLAGS
```bash
Rôle : Définit les flags de compilation globaux pour le langage C/c++.
Utilisation : Ajoute des options de compilation pour tout le projet.
Exemple:
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
```
- CMAKE_CURRENT_SOURCE_DIR
```bash
Rôle : Contient le chemin absolu du répertoire source actuel (où se trouve le CMakeLists.txt en cours de traitement).
Utilisation : Utile pour référencer des fichiers locaux.
Exemple :
 include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
```
- CMAKE_C_FLAGS_DEBUG/ CMAKE_CXX_FLAGS_DEBUG
```bash
Rôle : Définit les flags de compilation spécifiques au mode Debug pour le langage C ou C++.
Utilisation : Ajoute des options de débogage (comme -g).
Exemple :
 set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
```
- CMAKE_CURRENT_BINARY_DIR
```bash
Rôle : Contient le chemin absolu du répertoire de build actuel (où les fichiers générés sont placés).
Utilisation : Utile pour référencer des fichiers générés pendant la compilation.
Exemple :
 set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
```
- CMAKE_C_FLAGS_RELEASE/ CMAKE_CXX_FLAGS_RELEASE
```bash
Rôle : Définit les flags de compilation spécifiques au mode Release pour le langage C/C++.
Utilisation : Ajoute des optimisations (comme -O3).
Exemple :
 set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
```
- CMAKE_SOURCE_DIR
```bash
Rôle : Contient le chemin absolu du répertoire source principal (le répertoire racine du projet).
Utilisation : Utile pour référencer des fichiers ou sous-répertoires depuis la racine du projet.
Exemple :
 include_directories(${CMAKE_SOURCE_DIR}/common/include)
```

#### Bonnes pratiques
- Utilisez -D pour les options de configuration globales (ex: chemins, flags de compilation).
- Utilisez set() sans CACHE pour les variables internes au projet.
- Utilisez FORCE avec prudence, car cela peut surprendre les utilisateurs qui passent des variables via -D.

### Les fonctions

- message
```bash
Rôle : Affiche un message pendant la configuration.
Exemple :
 message(STATUS "Configuration en cours...")
message(WARNING "Attention, cette option est expérimentale.")
```
- add_executable
```bash
Rôle : Crée une cible exécutable.
Exemple :
 add_executable(my_app main.c)
```
- add_library
```bash
Rôle : Crée une cible de bibliothèque (statique ou dynamique).
Exemple :
 add_library(my_lib STATIC lib.c)
add_library(my_shared_lib SHARED lib.c)
```
- target_include_directories
```bash
Rôle : Ajoute des répertoires d’en-tête pour une cible spécifique.
Exemple :
 target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
```
- target_link_libraries
```bash
Rôle : Lie une cible à des bibliothèques.
Exemple :
 target_link_libraries(my_app PRIVATE my_lib)
```
- target_compile_options
```bash
Rôle : Ajoute des options de compilation pour une cible.
Exemple :
 target_compile_options(my_app PRIVATE -Wall -Wextra)
```
- target_compile_definitions
```bash
Rôle : Définit des macros de préprocesseur pour une cible.
Exemple :
 target_compile_definitions(my_app PRIVATE DEBUG=1)
```

*Gestion des dépendances et recherche de bibliothèques*
- find_package
```bash
Rôle : Cherche et charge un package externe (comme OpenCV, Boost, etc.).
Exemple :
 find_package(OpenCV REQUIRED)
```
- find_library
```bash
Rôle : Cherche une bibliothèque spécifique.
Exemple :
 find_library(MY_LIB libfoo.so PATHS /chemin/vers/bib)
```
- find_path
```bash
Rôle : Cherche un répertoire contenant un fichier spécifique.
Exemple :
 find_path(MY_INCLUDE_DIR foo.h PATHS /chemin/vers/include)
```
- include_directories
```bash
Rôle : Ajoute des répertoires d’en-tête pour toutes les cibles.
Exemple :
 include_directories(${MY_INCLUDE_DIR})
```
- link_directories
```bash
Rôle : Ajoute des répertoires de bibliothèques pour toutes les cibles.
Exemple :
 link_directories(${MY_LIB_DIR})
```

*Gestion des conditions et des boucles*
- if
```bash
Rôle : Exécute un bloc de code conditionnellement.
Exemple :
 if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build en mode Debug")
endif()
```
- foreach
```bash
Rôle : Boucle sur une liste.
Exemple :
 foreach(file IN LISTS MY_LIST)
    message(STATUS "Fichier : ${file}")
endforeach()
```
- while
```bash
Rôle : Boucle tant qu’une condition est vraie.
Exemple :
 set(i 0)
while(i LESS 10)
    message(STATUS "i = ${i}")
    math(EXPR i "${i} + 1")
endwhile()
```

*Gestion des fichiers et des répertoires*
- file
```bash
Rôle : Manipule des fichiers et des répertoires.
Exemple :
 file(GLOB SOURCES "*.c")
file(WRITE "config.h" "#define VERSION 1.0")
```
- add_subdirectory
```bash
Rôle : Ajoute un sous-répertoire contenant un CMakeLists.txt.
Exemple :
 add_subdirectory(src)
```
- aux_source_directory
```bash
Rôle : Récupère la liste des fichiers sources dans un répertoire.
Exemple :
 aux_source_directory(. SOURCES)
```

*Gestion de l’installation*
- install
```bash
Rôle : Définit les règles d’installation pour les cibles, fichiers ou répertoires.
Exemple :
 install(TARGETS my_app DESTINATION bin)
install(FILES my_app.h DESTINATION include)
```
- set_property / get_property
```bash
Rôle : Définit ou récupère une propriété pour une cible, un répertoire ou une variable globale.
Exemple :
 set_property(TARGET my_app PROPERTY CXX_STANDARD 11)
get_property(my_std TARGET my_app PROPERTY CXX_STANDARD)
```

*gestion des test*
- enable_testing
```bash
Rôle : Active la prise en charge des tests.
Exemple :
 enable_testing()
```
- add_test
```bash
Rôle : Définit un test à exécuter.
Exemple :
 add_test(NAME my_test COMMAND my_app)
```

*Gestion des options et des variables de cache*
- option
```bash
Rôle : Définit une option booléenne pour le cache.
Exemple :
 option(BUILD_TESTS "Construire les tests unitaires" ON)
```
- mark_as_advanced
```bash
Rôle : Masque une variable dans les interfaces comme ccmake.
Exemple :
 mark_as_advanced(MY_ADVANCED_VAR)
```

*Gestion des dépendances entre cibles*
- add_dependencies
```bash
Rôle : Définit une dépendance entre deux cibles.
Exemple :
 add_dependencies(my_app my_lib)
```

*Gestion des exportations et des imports*
- export
```bash
Rôle : Exporte des cibles pour une utilisation externe.
Exemple :
 export(my_targets FILE my_targets.cmake)
```
- install(EXPORT)
```bash
Rôle : Installe un fichier d’exportation pour les cibles.
Exemple :
 install(EXPORT my_targets DESTINATION lib/cmake/MyProject)
```

*Gestion des configurations de build*
- try_run
```bash
Rôle : Exécute un programme pendant la configuration pour déterminer une valeur.
Exemple :
 try_run(RUN_RESULT COMPILE_RESULT
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_program.c
)
```
- try_compile
```bash
Rôle : Teste si un code se compile correctement.
Exemple :
 try_compile(COMPILE_RESULT
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/test_compile.c
)
```

*Gestion des modules et des politiques*
- include
```bash
Rôle : Inclut un fichier CMake.
Exemple :
 include(CheckCCompilerFlag)
```
- cmake_policy
```bash
Rôle : Définit une politique de comportement pour CMake.
Exemple :
 cmake_policy(SET CMP0048 NEW)
```

*Gestion des propriétés globales*
- set_directory_properties
```bash
Rôle : Définit des propriétés pour un répertoire.
Exemple :
 set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "DEBUG=1")
```

*Gestion des générateurs de build*
- CMAKE_GENERATOR
```bash
Rôle : Définit le générateur de build (Makefiles, Ninja, Visual Studio, etc.).
Exemple :
 cmake -G "Unix Makefiles" ..
```
- CMAKE_INSTALL_PREFIX
```bash
Rôle : Définit le répertoire d’installation par défaut.
Exemple :
 cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

*Gestion des dépendances externes*
- ExternalProject_Add
```bash
Rôle : Télécharge et construit un projet externe pendant la configuration.
Exemple :
 include(ExternalProject)
ExternalProject_Add(
    my_external_lib
    GIT_REPOSITORY https://github.com/user/lib.git
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)
```

*Gestion des tests et des benchmarks*
- add_test
```bash
Rôle : Ajoute un test à exécuter avec ctest.
Exemple :
 add_test(NAME my_test COMMAND my_app)
```
- enable_testing
```bash
Rôle : Active la prise en charge des tests.
Exemple :
 enable_testing()
```

*Gestion des paquets et des exports*
- install(EXPORT)
```bash
Rôle : Installe un fichier d’exportation pour les cibles.
Exemple :
 install(EXPORT my_targets DESTINATION lib/cmake/MyProject)
```
- export
```bash
Rôle : Exporte des cibles pour une utilisation externe.
Exemple :
 export(my_targets FILE my_targets.cmake)
```

*Gestion des propriétés des cibles*
- set_target_properties
```bash
Rôle : Définit des propriétés pour une cible.
Exemple :
 set_target_properties(my_app PROPERTIES OUTPUT_NAME "my_custom_name")
```
- get_target_property
```bash
Rôle : Récupère une propriété d’une cible.
Exemple :
 get_target_property(my_app_output_name my_app OUTPUT_NAME)
```


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

