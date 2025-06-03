#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    char inf;
    struct no* prox;
} no;

char criar(no **lista) {
    *lista = (no*)malloc(sizeof(no));
    if (lista == NULL) return 0;
    else {
        (*lista)->inf = '@';
        (*lista)->prox = NULL;
        return 1;
    }
}

int vazio(no* lista) {
    if (lista == NULL || lista->inf == '@') return 1;
}

int tamanho(no* lista) {
    int tam = 0;
    if (!vazio(lista)) {
        tam = 1;
        while (lista->prox != NULL) {
            lista = lista->prox;
            tam++;
        }
    }
    return tam;
}

char cabeca(no* lista) {
    if (lista->inf != '@') return lista->inf;
    else return 0;
}

no* cauda(no* lista) {
    if (vazio(lista)) return NULL;
    return lista->prox;
}

char busca(no* lista, char x) {
    if (!vazio(lista)) {
        while (lista != NULL) {
            if (lista->inf == NULL) return 1;
            lista =lista->prox;
        }
    }
    return 0;
}

no* insereInicio(no* lista, char x) {
    if (vazio(lista)) {
        no* aux = (no*)malloc(sizeof(no));
        lista = (no*)malloc(sizeof(no));
        aux->inf = x;
        aux->prox = NULL;
        return aux;
    } else {
        no* aux2 = (no*)malloc(sizeof(no));
        aux2->inf = x;
        aux2->prox = lista;
        return aux2;
    }
}

no* insereFim(no* lista, char x) {
    if (vazio(lista)) return insereInicio(lista, x);
    else {
        no *a1 = lista, *a2 = NULL;
        while (a1->prox != NULL) {
            a1 = a1->prox;
        }
        a2 = (no*)malloc(sizeof(no));
        a2->inf = x;
        a2->prox = a1->prox;
        a1->prox = a2;
        return lista;
    }
}

no* insereMeio(no* lista, char x) {
    if (vazio(lista)) return insereInicio(lista, x);
    else {
        no *a1 = lista, *a2 = NULL;
        while (a1->prox != NULL && a1->prox->inf < x) {
            a1 = a1->prox;
        }
        a2 = (no*)malloc(sizeof(no));
        a2->inf = x;
        a2->prox = a1->prox;
        a1->prox = a2;
        return lista;
    }
}

no* removeInicio(no* lista, char* x) {
    if (vazio(lista)) return 0;
    else {
        *x = lista->inf;
        no* aux = lista;
        free(aux);
        return lista;
    }
}

no* removeFim(no* lista, char* x) {
    if (vazio(lista)) return 0;
    if (lista->prox == NULL) {
        *x = lista->inf;
        free(lista);
        return NULL;
    }

    no *a1 = lista, *a2 = NULL;
    while (a1->prox->prox != NULL) {
        a1 = a1->prox;
    }
    a2 = a2->prox;
    *x = a2->inf;
    free(a2);
    return lista;
}

no* concatena(no* l1, no* l2) {
    no* a3 = NULL;
    char e;

    if (vazio(l1) && vazio(l2)) {
        criar(&a3);
        return a3;
    }
    if (vazio(l1)) return l2;
    if (vazio(l2)) return l1;

    criar(&a3);
    no *a1 = l1, *a2 = l2;
    while (a1 != NULL && a2 != NULL) {
        if (a1->inf <= a2->inf) {
            e = a1->inf;
            a1 = a1->prox;
        } else {
            e = a2->inf;
            a2 = a2->prox;
        }
        a3 = insereFim(a3, e);
    }

    while (a1 != NULL) {
        a3 = insereFim(a3, e);
        a1 = a1->prox;
    }
    while (a2 != NULL) {
        a3 = insereFim(a3, e);
        a2 = a2->prox;
    }
    return a3;
}

void imprimir(no* lista) {
    if (vazio(lista)) return;

    no* atual = lista;
    printf("(");
    while (atual != NULL) {
        printf("%c", atual->inf);
        if (atual->prox == NULL) {
            printf(", ");
        }
        atual = atual->prox;
    }
    printf(")\n");
}

void liberar(no* lista) {
    no* atual = lista, *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}
