#include <stdio.h>
#include <stdlib.h>

#ifndef DATAST_H
#define DATAST_H


typedef struct nodoStack{
    char symbol;
    struct nodoStack *next;
} NodoStack;

typedef struct stack{
    NodoStack *topo;
}PILHA;

PILHA *cria(){
    PILHA *s = (struct stack *)malloc(sizeof(struct stack));

    if(s == NULL){
       printf("Erro ao criar Pilha!\n");
       exit(1); 
    }

    s->topo = NULL;

    return s;
}

int isEmpty(PILHA *s){
    return s->topo == NULL;
}

void push(PILHA *s, char letra){
    NodoStack *aux = (struct nodoStack*)malloc(sizeof(struct nodoStack));

    if(aux == NULL){
        printf("Erro ao empilhar letra!\n");
        exit(1);
    }
   
   aux->symbol = letra;
   aux->next = s->topo;
   s->topo = aux;
    
}

int pop(char *letra, PILHA *s){

    if(!isEmpty(s)){
        NodoStack *aux = s->topo;
        *letra = aux->symbol;
        s->topo = aux->next;
        free(aux);
        return 1;
    }else{
        return 0;
    }
}

int reinicia(PILHA *s) {
  NodoStack *aux = NULL;
  if (!isEmpty(s)) {
    aux = s->topo->next;
    while (aux != NULL) {
      free(s->topo);
      s->topo = aux;
      aux = aux->next;
    }
    free(s->topo);
    s->topo = NULL;
    return 1;
  }
  return 0;
}

void destroi(PILHA *s) {
  reinicia(s);
  free(s);
}

#endif