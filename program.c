#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/aflib.h"
#include "include/graphviz/gvc.h"
#include "include/graphviz/cgraph.h"
#include "include/graphviz/cdt.h"

int main() {
    while (1) {
        printf("---------Menu---------\n1 - Iniciar simulacao\n2 - Encerrar o programa\ncomando >> ");
        
        int opcao = 0;
        scanf("%d", &opcao);

        if (opcao == 1) {
            simulacao();
        }
        else if (opcao == 2) {
            printf("Programa finalizado!");
            break;
        }
        else {
            printf("Opcao nao identificada!");
        }
    }

    return 0;
}


void simulacao() {
    
}