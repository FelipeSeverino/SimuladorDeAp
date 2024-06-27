#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/aflib.h"

void teste1(char *palavra) {
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

void teste2() { //anbn
    printf("TESTE 1\n");
    AF *af = criarAF();

    inserirEstado("q0", 1, 0, af);
    inserirEstado("q1", 0, 0, af);
    inserirEstado("q2", 0, 1, af);

    inserirTransicao('a', '#', "B", "q0", "q1", af);
    inserirTransicao('b', 'B', "#", "q1", "q2", af);

    printf("Iniciando reconhecimento!\n");
    int validade = verificarPalavra("abab", af);
    if (validade) {
        printf("Palavra valida!");
    }
    else {
        printf("Palavra invalida");
    }

    printf("-----------------------------\n");
}

int main() {
    teste1("ab");
    teste2("aaabbb");

    return 0;
}