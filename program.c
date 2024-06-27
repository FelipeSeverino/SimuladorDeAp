#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/aflib.h"
#include "include/graphviz/gvc.h"
#include "include/graphviz/cgraph.h"
#include "include/graphviz/cdt.h"
#include "include/graphviz/gvplugin.h"
#include "include/graphviz/gvplugin_layout.h"

void simulacao();
void generateAutomatonDot(AF *af, const char *filename);

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
    AF *af = criarAF();

    //Leitura dos estados
    int opcao = 0;
    int nEstados = 0;
    while (1) { //Criacao de estados
        printf("\n\n1 - Criar novo estado\n2 - Proximo passo\n");
        printf("comando >> ");
        scanf("%d", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (opcao == 2 && nEstados < 1) {
            printf("Crie ao menos um estado!");
            continue;
        }

         if (opcao == 2) {
            break;
        }

        char nome[5];
        printf("Digite o nome do estado: \n");
        fgets(nome, 5, stdin);

        int inicial = 0;
        int final = 0;

        if (af->h_estado == NULL || af->h_estado != NULL && af->h_estado->inicial == 0) {
            printf("Eh inicial? (0 ou 1) ");
            scanf("%d", &inicial);
        }

        printf("Eh final? (0 ou 1) ");
        scanf("%d", &final);

        inserirEstado(nome, inicial, final, af);
        nEstados++;
    }

    while (1) { //Criacao de transicoes
        printf("\n\n1 - Criar nova transicao\n2 - Proximo passo\n");
        printf("comando >> ");
        scanf("%d", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (opcao == 2) {
            break;
        }

        char q_from[5];
        printf("Do estado >> ");
        fgets(q_from, 5, stdin);

        char q_to[5];
        printf("Para o estado >> ");
        fgets(q_to, 5, stdin);

        char simbolo;
        printf("Simbolo >> ");
        scanf("%c", &simbolo);
        while ((c = getchar()) != '\n' && c != EOF);

        char pushSymbol[5];
        printf("Adiciona a pilha >> ");
        fgets(pushSymbol, 5, stdin);

        char popFromPile;
        printf("Remove da pilha >> ");
        scanf("%c", &simbolo);
        while ((c = getchar()) != '\n' && c != EOF);


        inserirTransicao(simbolo, popFromPile, pushSymbol, q_from, q_to, af);
    }

    while (1) {
        printf("\n**Reconhecimento de palavras**\n\n");
        printf("Digite uma palavra >> ");
        char *palavra;
        fgets(palavra, 100, stdin);

        int validade = verificarPalavra(palavra, af);
        if (validade) {
            printf("Palavra valida!");
        }
    }

    printf("\nGerando grafo visual...\n");
    generateAutomatonDot(af, "teste.dot");
    printf("Grafo criado com sucesso!\n");
    printf("\nDeletando simulacao anterior...\n");
    deleteAf(af);
    printf("Simulacao deletada com sucesso!\n\n");
}


void generateAutomatonDot(AF *af, const char *filename) {
    GVC_t *gvc;
    Agraph_t *graph;
    FILE *fp;

    gvc = gvContext();

    graph = agopen("automaton", Agdirected, NULL);

    ESTADO *currentState = af->h_estado;
    while (currentState != NULL) {
        Agnode_t *node = agnode(graph, currentState->nome, 1);
        if (currentState->final == 1) {
            agset(node, "shape", "doublecircle");
            agset(node, "color", "blue");
        } else {
            agset(node, "shape", "circle");
        }
        currentState = currentState->next;
    }

    gvLayout(gvc, graph, "dot");

    fp = fopen(filename, "w");
    agwrite(graph, fp);
    fclose(fp);

    gvRenderFilename(gvc, graph, "png", "automaton.png");

    gvFreeLayout(gvc, graph);
    agclose(graph);
    gvFreeContext(gvc);
}
