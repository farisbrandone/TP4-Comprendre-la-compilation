# Configuration minimale requise
cmake_minimum_required(VERSION 3.10)

# Définition du projet
project(Calculatrice C)

# Configuration des flags de compilation
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_BUILD_TYPE Debug)

# Définition des répertoires
set(LIB_DIR src/lib/calstatlib)
set(BUILD_DIR src/build)
set(BIN_DIR src/bin)
set(TOKEN_TYPE_INCLUDE ${LIB_DIR}/tokenType)
set(SRC_DIR src/app)
# Création des bibliothèques statiques

# 1. Bibliothèque evalRpn
add_library(evalRpn STATIC ${LIB_DIR}/evalRpn/evalRpn.c)
target_include_directories(evalRpn PRIVATE ${TOKEN_TYPE_INCLUDE})
# Explication : Crée une lib statique avec le flag -g implicite via CMAKE_C_FLAGS
# L'include directory est privé car interne à la bibliothèque

# 2. Bibliothèque fixUnaryMinus
add_library(fixUnaryMinus STATIC ${LIB_DIR}/fixUnaryMinus/fixUnaryMinus.c)
target_include_directories(fixUnaryMinus PRIVATE ${TOKEN_TYPE_INCLUDE})

# 3. Bibliothèque shuntingYard
add_library(shuntingYard STATIC ${LIB_DIR}/shuntingYard/shuntingYard.c)
target_include_directories(shuntingYard PRIVATE ${TOKEN_TYPE_INCLUDE})

# 4. Bibliothèque tokenize
add_library(tokenize STATIC ${LIB_DIR}/tokenize/tokenize.c)
target_include_directories(tokenize PRIVATE ${TOKEN_TYPE_INCLUDE})

# Création de l'exécutable principal
add_executable(calculatrice
    ${SRC_DIR}/main.c
)

# Configuration des includes pour l'exécutable
target_include_directories(calculatrice PRIVATE
    ${LIB_DIR}/tokenize
    ${LIB_DIR}/shuntingYard
    ${LIB_DIR}/fixUnaryMinus
    ${LIB_DIR}/evalRpn
    ${TOKEN_TYPE_INCLUDE}
)

# Liaison des bibliothèques
target_link_libraries(calculatrice
    evalRpn
    fixUnaryMinus
    shuntingYard
    tokenize
    m  # Bibliothèque mathématique (-lm)
)

# Définition du répertoire de sortie
set_target_properties(calculatrice PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
