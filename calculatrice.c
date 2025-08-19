#include "calculatrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Variables globales pour les tokens
Token tokens[MAX_TOKENS];
Token output_queue[MAX_TOKENS];
Token op_stack[MAX_STACK];
double eval_stack[MAX_STACK];

int token_count = 0;
int output_count = 0;
int op_top = -1;
int eval_top = -1;

// Fonctions de pile
void push_op(Token token) { op_stack[++op_top] = token; }
Token pop_op() { return op_stack[op_top--]; }
void push_eval(double val) { eval_stack[++eval_top] = val; }
double pop_eval() { return eval_stack[eval_top--]; }

// Priorité des opérateurs
int get_priority(char* op) {
    if (strcmp(op, "u") == 0) return 5;
    if (strcmp(op, "^") == 0) return 4;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 3;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 2;
    return 0;
}

// Associativité
typedef enum { LEFT, RIGHT } Associativity;
Associativity get_associativity(char* op) {
    if (strcmp(op, "^") == 0 || strcmp(op, "u") == 0) return RIGHT;
    return LEFT;
}

// Tokenisation
void tokenize(const char* expr) {
    const char* p = expr;
    token_count = 0;

    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // Nombres
        if (isdigit(*p) || *p == '.') {
            char num_str[32] = {0};
            int i = 0;

            while (*p && (isdigit(*p) || *p == '.' ||
                   *p == 'e' || *p == 'E' ||
                   ((*p == '-' || *p == '+') && (i > 0 && (num_str[i-1] == 'e' || num_str[i-1] == 'E'))))) {
                num_str[i++] = *p++;
            }

            tokens[token_count].type = NUMBER;
            tokens[token_count].value = atof(num_str);
            token_count++;
            continue;
        }

        // Opérateurs
        if (strchr("+-*/^", *p)) {
            tokens[token_count].type = OPERATOR;
            tokens[token_count].str[0] = *p;
            tokens[token_count].str[1] = '\0';
            token_count++;
            p++;
            continue;
        }

        // Parenthèses
        if (*p == '(') {
            tokens[token_count].type = LEFT_PAREN;
            strcpy(tokens[token_count].str, "(");
            token_count++;
            p++;
            continue;
        }

        if (*p == ')') {
            tokens[token_count].type = RIGHT_PAREN;
            strcpy(tokens[token_count].str, ")");
            token_count++;
            p++;
            continue;
        }

        // Fonctions
        if (isalpha(*p)) {
            char func[32] = {0};
            int i = 0;

            while (isalpha(*p)) {
                func[i++] = *p++;
            }

            tokens[token_count].type = FUNCTION;
            strcpy(tokens[token_count].str, func);
            token_count++;
            continue;
        }

        fprintf(stderr, "Erreur: Caractère non reconnu '%c'\n", *p);
        exit(1);
    }
}

// Moins unaire
void fix_unary_minus() {
    for (int i = 0; i < token_count; i++) {
        if (strcmp(tokens[i].str, "-") == 0) {
            if (i == 0 || tokens[i-1].type == OPERATOR || tokens[i-1].type == LEFT_PAREN) {
                strcpy(tokens[i].str, "u");
            }
        }
    }
}

// Shunting Yard
void shunting_yard() {
    output_count = 0;
    op_top = -1;

    for (int i = 0; i < token_count; i++) {
        Token t = tokens[i];

        switch (t.type) {
            case NUMBER:
                output_queue[output_count++] = t;
                break;

            case FUNCTION:
                push_op(t);
                break;

            case OPERATOR: {
                while (op_top >= 0 &&
                       op_stack[op_top].type != LEFT_PAREN &&
                       (get_priority(op_stack[op_top].str) > get_priority(t.str) ||
                       (get_priority(op_stack[op_top].str) == get_priority(t.str) &&
                       get_associativity(t.str) == LEFT))) {
                    output_queue[output_count++] = pop_op();
                }
                push_op(t);
                break;
            }

            case LEFT_PAREN:
                push_op(t);
                break;

            case RIGHT_PAREN:
                while (op_top >= 0 && op_stack[op_top].type != LEFT_PAREN) {
                    output_queue[output_count++] = pop_op();
                }
                if (op_top < 0) {
                    fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
                    exit(1);
                }
                pop_op(); // Supprimer '('

                if (op_top >= 0 && op_stack[op_top].type == FUNCTION) {
                    output_queue[output_count++] = pop_op();
                }
                break;
        }
    }

    // Vider la pile
    while (op_top >= 0) {
        if (op_stack[op_top].type == LEFT_PAREN) {
            fprintf(stderr, "Erreur: Parenthèses non équilibrées\n");
            exit(1);
        }
        output_queue[output_count++] = pop_op();
    }
}

// Évaluation RPN
double eval_rpn() {
    eval_top = -1;

    for (int i = 0; i < output_count; i++) {
        Token t = output_queue[i];

        switch (t.type) {
            case NUMBER:
                push_eval(t.value);
                break;

            case OPERATOR:
                if (strcmp(t.str, "u") == 0) {
                    push_eval(-pop_eval());
                } else {
                    double b = pop_eval();
                    double a = pop_eval();

                    if (strcmp(t.str, "+") == 0) push_eval(a + b);
                    else if (strcmp(t.str, "-") == 0) push_eval(a - b);
                    else if (strcmp(t.str, "*") == 0) push_eval(a * b);
                    else if (strcmp(t.str, "/") == 0) {
                        if (b == 0) {
                            fprintf(stderr, "Erreur: Division par zéro\n");
                            exit(1);
                        }
                        push_eval(a / b);
                    }
                    else if (strcmp(t.str, "^") == 0) push_eval(pow(a, b));
                }
                break;

            case FUNCTION:
                double arg = pop_eval();
                double res;

                if (strcmp(t.str, "sin") == 0) res = sin(arg);
                else if (strcmp(t.str, "cos") == 0) res = cos(arg);
                else if (strcmp(t.str, "tan") == 0) res = tan(arg);
                else if (strcmp(t.str, "log") == 0) {
                    if (arg <= 0) {
                        fprintf(stderr, "Erreur: Logarithme non défini\n");
                        exit(1);
                    }
                    res = log(arg);
                }
                else if (strcmp(t.str, "exp") == 0) res = exp(arg);
                else {
                    fprintf(stderr, "Fonction non supportée: %s\n", t.str);
                    exit(1);
                }
                push_eval(res);
                break;
        }
    }

    if (eval_top != 0) {
        fprintf(stderr, "Erreur: Expression invalide\n");
        exit(1);
    }

    return pop_eval();
}

// Fonction principale
double evaluate_expression(const char* expr) {
    tokenize(expr);
    fix_unary_minus();
    shunting_yard();
    return eval_rpn();
}
