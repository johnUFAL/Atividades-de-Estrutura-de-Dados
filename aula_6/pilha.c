#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char inf;
    struct no* prox;
} no;

char criar(no** pilha) {
    *pilha = NULL;
    return 1;
}

int vazio(no* pilha) {
    return (pilha == NULL);
}

no* empilhar(no* pilha, char x) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) return pilha;

    novo->inf = x;
    novo->prox = pilha;
    return novo;
}

no* desempilhar(no* pilha, char* x) {
    if (vazio(pilha)) return NULL;

    no* aux = pilha;
    *x = pilha->inf;
    pilha = pilha->prox;
    free(aux);
    return pilha;
}

char topo(no* pilha) {
    if (vazio(pilha)) return 0;
    return pilha->inf;
}

void imprimir(no* pilha) {
    printf("Topo ->");
    while (pilha != NULL) {
        printf("%c", pilha->inf);
        pilha = pilha->prox;
    }
    printf("\n");
}

void liberar(no* pilha) {
    no* atual = pilha, *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}
