#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Grafo {
    int Nvertices;
    bool matAdjacencia[MAX_VERTICES][MAX_VERTICES];
} Grafo;

Grafo* criar(int Nvertices) {
    if (Nvertices <= 0 || Nvertices > MAX_VERTICES) {
        printf("inválido!\n");
        return NULL;
    }
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->Nvertices = Nvertices;

    for (int i = 0; i < Nvertices; i++) {
        for (int j = 0; j < Nvertices; j++) {
            grafo->matAdjacencia[i][j] = false;
        }
    }
    return grafo;
}

void addAresta(Grafo* grafo, int origem, int destino) {
    if (grafo == NULL || origem < 0 || destino < 0 || 
        origem >= grafo->Nvertices || destino >= grafo->Nvertices) {
        printf("inválido!\n");
        return;
    }
    grafo->matAdjacencia[origem][destino] = true;
    grafo->matAdjacencia[destino][origem] = true; 
}

void remAresta(Grafo* grafo, int origem, int destino) {
    if (grafo == NULL || origem < 0 || destino < 0 || 
        origem >= grafo->Nvertices || destino >= grafo->Nvertices) {
        printf("inválido!\n");
        return;
    }
    grafo->matAdjacencia[origem][destino] = false;
    grafo->matAdjacencia[destino][origem] = false; 
}

void listar(Grafo* grafo) {
    if (grafo == NULL) return;
    
    printf("Mat de Adjacencia:\n");
    for (int i = 0; i < grafo->Nvertices; i++) {
        for (int j = 0; j < grafo->Nvertices; j++) {
            printf("%d ", grafo->matAdjacencia[i][j] ? 1 : 0);
        }
        printf("\n");
    }
}

void liberar(Grafo* grafo) {
    if (grafo != NULL) {
        free(grafo);
    }
}
