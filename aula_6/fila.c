#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char inf;
    struct no* prox;
} no;

typedef struct {
    no* frente;
    no* tras;
} fila;

char criar(fila *f) {
    f->frente = NULL;
    f->tras = NULL;
    return 1;
}

int vazio(fila f) {
    return (f.frente == NULL);
}

void enfileirar(fila* f, char x) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) return;

    novo->inf = x;
    novo->prox = NULL;

    if (vazio(*f)) {
        f->frente = novo;
        f->tras = novo;
    } else {
        f->tras->prox = novo;
        f->tras = novo;
    }
}

char desenfileirar(fila* f) {
    if (vazio(*f)) return 0;
    
    no* aux = f->frente;
    char x = aux->inf;
    f->frente = f->frente->prox;
    if (f->frente == NULL) f->tras = NULL;
    free(aux);
    return x;
}

char frente(fila f) {
    if (vazio(f)) return 0;
    return f.frente->inf;
}

void imprimir(fila f) {
    printf("Topo ->");
    no* atual = f.frente;
    while (atual != NULL) {
        printf("%c", atual->inf);
        atual = atual->prox;
    }
    printf("<- Tras\n");
}

void liberar(fila* f) {
    while (!(vazio(*f))) {
        desenfileirar(f);
    }
}