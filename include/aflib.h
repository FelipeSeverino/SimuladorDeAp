#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datast.h"

#ifndef AFLIB_H
#define AFLIB_H

typedef struct estado ESTADO;
typedef struct transicao TRANSICAO;
typedef struct af AF;

typedef struct af {
    ESTADO *h_estado;
    TRANSICAO *h_transicao;
    PILHA *pilha;
} AF;

AF* criarAF() {
    AF *novoAF = (AF*) malloc(sizeof(AF));

    if (novoAF == NULL) {
        printf("Erro ao criar AF!! (Mem alloc)\n");
        exit(1);
    }

    novoAF->h_estado = NULL;
    novoAF->h_transicao = NULL;

    return novoAF;
}


typedef struct estado {
    int inicial; // 0 = false, 1 = true
    int final; // 0 = false, 1 = true
    char *nome;

    struct estado * next;
} ESTADO;

ESTADO* criarEstado(char *nome, int inicial, int final) {
    ESTADO *novoEstado = (ESTADO*) malloc(sizeof(ESTADO));
    novoEstado->nome = (char*) malloc(sizeof(char) * 5);

    if (novoEstado == NULL) {
        printf("Erro ao criar estado!! (Mem alloc)\n");
        exit(1);
    }

    strcpy(novoEstado->nome, nome);
    novoEstado->inicial = inicial;
    novoEstado->final = final;
    novoEstado->next = NULL;

    return novoEstado;
}

void inserirEstado(char *nome, int inicial, int final, AF *af) {
    ESTADO *estado = criarEstado(nome, inicial, final);
    if (af == NULL) {
        printf("AF invalido!! \n");
        return;
    }

    if (af->h_estado == NULL) {  //primeiro estado registrado
        af->h_estado = estado;
        return;
    }

    if (estado->inicial == 1) { //estado inicial, insere no inicio
        ESTADO *old_estado = af->h_estado;
        af->h_estado = estado;
        estado->next = old_estado;

        free(old_estado);
        return;
    }
    
    //nao eh estado inicial, insere ao final
    ESTADO *currentEstado = af->h_estado;
    while (currentEstado->next != NULL) {
        currentEstado = currentEstado->next;
    }
    currentEstado->next = estado;
}

typedef struct transicao {
    char symbol;
    char insertPile;
    char popPile;

    char *q_from;
    char *q_to;

    struct transicao * next;
} TRANSICAO;

TRANSICAO* criarTransicao(char symbol, char insertPile, char popPile, char *from, char *to) {
    TRANSICAO *novaTransicao = (TRANSICAO*) malloc(sizeof(TRANSICAO));

    if (novaTransicao == NULL) {
        printf("Erro ao criar transicao!! (Mem alloc)\n");
        exit(1);
    }

    
    novaTransicao->symbol = symbol;
    novaTransicao->insertPile = insertPile;
    novaTransicao->popPile = popPile;

    novaTransicao->q_from = (char*) malloc(sizeof(char*) * 5);
    novaTransicao->q_to = (char*) malloc(sizeof(char*) * 5);
    strcpy(novaTransicao->q_from, from);
    strcpy(novaTransicao->q_to, to);

    novaTransicao->next = NULL;

    return novaTransicao;
}

void inserirTransicao(char symbol, char insertPile, char popPile, char *from, char *to, AF *af) {
    TRANSICAO *transicao = criarTransicao(symbol, insertPile, popPile, from, to);

    if (af == NULL) {
        printf("AF invalido!! \n");
        return;
    }

    if (af->h_transicao == NULL) {
        af->h_transicao = transicao;
    }
    else {
        TRANSICAO *currentTransicao = af->h_transicao;
        while (currentTransicao->next != NULL) {
            currentTransicao = currentTransicao->next;
        }
        currentTransicao->next = transicao;
    }
}

#endif