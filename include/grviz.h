#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aflib.h"

#ifndef GRVIZ_H
#define GRVIZ_H

#define Espaco "%20"
#define QuebraL "%0A"
#define Igual "%3D"
#define ColchetesAbre "%5B"
#define ColchetesFecha "%5D"
#define ChavesFecha "%7D"
#define Virgula "%2C"
#define Vazio "%23"
#define Inicial "start->"
#define Final "%5Bshape%3Ddoublecircle%5D"
#define Seta "-%0A"
#define Epsilon "%E2%82%AC"
#define Label "%5Blabel%3D%22("
#define aspas "%22"


void geraLinkGraphviz(char *link, AF *af) {
    strcat(link, "https://dreampuf.github.io/GraphvizOnline/#digraph%20AP%20%7B%0Astart%5Bshape%3Dpoint%5D%0A");
    
    ESTADO *currentState = af->h_estado;
    while (currentState != NULL) {
        strcat(link, currentState->nome);

        if (currentState->final) {strcat(link, Final);}
        strcat(link, QuebraL);
        if (currentState->inicial) {
            strcat(link, Inicial);
            strcat(link, currentState->nome);
            strcat(link, QuebraL);
        }

        currentState = currentState->next;
    }

    TRANSICAO *tr = af->h_transicao;
    //for n2 para estados criando uma combinacao so para cada transicao
    while (tr != NULL) {
        strcat(link, tr->q_from);
        strcat(link, "->");
        strcat(link, tr->q_to);
        strcat(link, Label);
        strncat(link, &tr->symbol, 1);
        strcat(link, Virgula);
        strncat(link, &tr->popStack, 1);
        strcat(link, Virgula);
        strcat(link, tr->insertStack);
        strcat(link, ")%22");
        strcat(link, ColchetesFecha);
        strcat(link, QuebraL);
        
        tr = tr->next;
    }

    strcat(link, ChavesFecha);
}
//q0%0Aq1%5Bshape%3Ddoublecircle%5D%0Aq0-%3Eq1%5Blabel%3D%22(a%2C%23%2CA)%22%5D%0A%7D
#endif