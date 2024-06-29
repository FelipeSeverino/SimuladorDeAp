#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/aflib.h"
#include "include/grviz.c"

void teste1(char *palavra) { //ab
    printf("TESTE 1\n");
    AF *af = criarAF();

    inserirEstado("q0", 1, 0, af);
    inserirEstado("q1", 0, 0, af);
    inserirEstado("q2", 0, 1, af);

    inserirTransicao('a', '#', "B", "q0", "q1", af);
    inserirTransicao('b', 'B', "#", "q1", "q2", af);

    printf("Iniciando reconhecimento!\n");
    int validade = verificarPalavra(palavra, af);
    if (validade) {
        printf("Palavra valida!");
    }
    else {
        printf("Palavra invalida");
    }

    printf("###############################\n");
}

void teste2(char *palavra) { //anbn
    printf("TESTE 2\n");
    AF *af = criarAF();

    inserirEstado("q0", 1, 0, af);
    inserirEstado("q1", 0, 0, af);
    inserirEstado("q2", 0, 1, af);

    inserirTransicao('#', '#', "#", "q0", "q1", af);
    inserirTransicao('a', '#', "B", "q1", "q1", af);
    inserirTransicao('b', 'B', "#", "q1", "q1", af);
    inserirTransicao('?', '?', "#", "q1", "q2", af);

    printf("Iniciando reconhecimento!\n");
    int validade = verificarPalavra(palavra, af);
    if (validade) {
        printf("Palavra valida!\n");
    }
    else {
        printf("Palavra invalida!\n");
    }

    printf("###############################\n");
}


void teste3(char *palavra) { //|a| = |b|
    printf("TESTE 3\n");
    AF *af = criarAF();

    inserirEstado("q0", 1, 0, af);
    inserirEstado("q1", 0, 0, af);
    inserirEstado("q2", 0, 1, af);

    inserirTransicao('#', '#', "#", "q0", "q1", af);
    inserirTransicao('a', '#', "B", "q1", "q1", af);
    inserirTransicao('b', '#', "A", "q1", "q1", af);
    inserirTransicao('a', 'A', "#", "q1", "q1", af);
    inserirTransicao('b', 'B', "#", "q1", "q1", af);
    inserirTransicao('?', '?', "#", "q1", "q2", af);

    printf("Iniciando reconhecimento!\n");
    int validade = verificarPalavra(palavra, af);
    if (validade) {
        printf("Palavra valida!\n");
    }
    else {
        printf("Palavra invalida!\n");
    }

    char comando[10000] = "start \"\" \"";
    geraLinkGraphviz(comando, af);
    strcat(comando, "\"");
    printf("link: %s\n", comando);
    system(comando);

    printf("###############################\n");
}

int main() {
    //teste1("ab");
    //teste2("aabb");
    //teste3("abbabbaaab");

    // char *q0 = (char*) malloc(sizeof(char) * 5);
    // char *q1 = (char*) malloc(sizeof(char) * 5);
    // char symbol;
    // char pop;
    // char *push = (char*) malloc(sizeof(char) * 5);

    // scanf("%s->%s (%c,%c,%s)\n", q0, q1, symbol, pop, push);

    // printf("\nretorno -> %s->%s (%c,%c,%s)\n", q0, q1, &symbol, &pop, push);

    char *q0 = (char*) malloc(sizeof(char) * 5);
    char *q1 = (char*) malloc(sizeof(char) * 5);
    char symbol;
    char pop;
    char temp_push[5]; // Temporary buffer to read the push string

    if (q0 == NULL || q1 == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter input in the format q0->q1 (symbol,pop,push):\n");
    scanf("%4s->%4s (%c,%c,%4s)", q0, q1, &symbol, &pop, temp_push);

    char *push = (char*) malloc(sizeof(char) * (strlen(temp_push) + 1));
    if (push == NULL) {
        printf("Memory allocation failed\n");
        free(q0);
        free(q1);
        return 1;
    }
    strcpy(push, temp_push);

    printf("\nretorno -> %s->%s (%c,%c,%s)\n", q0, q1, symbol, pop, push);

    // Free the allocated memory
    free(q0);
    free(q1);
    free(push);

    return 0;
}