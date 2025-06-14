#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int inf;
    struct no* dir;
    struct no* esq;
    int h; //altura
} no;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(no* n) {
    if (n == NULL) return 0;
    return n->h;
}

no* criar(int x) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) {
        printf("Erro∖n");
        exit(1);
    }

    novo->inf = x;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->h = 1;
    return novo;
}

no* Rotdireita(no* y) {
    no* x = y->esq;
    no* T2 = x->dir;

    x->dir = y;
    y->dir = T2;

    y->h = max(altura(y->esq), altura(y->dir)) + 1;
    x->h = max(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

no* Rotesquerda(no* x) {
    no* y = x->dir;
    no* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->h = max(altura(x->esq), altura(x->dir)) + 1;
    y->h = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

int balanceamento(no* n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

no* insere (no* r, int x) {
    if (r == NULL)return criar(x);

    if (x < r->inf) r->esq = insere(r->esq, x);
    else if (x > r->inf) r->dir = insere(r->dir, x);
    else return r;

    r->h = 1 + max(altura(r->esq), altura(r->dir));
    int balanco = balanceamento(r);

    if (balanco > 1 && x < r->esq->inf) return Rotdireita(r);
    if (balanco < -1 && x > r->dir->inf) return Rotesquerda(r);
    if (balanco > 1 && x > r->esq->inf) {
        r->esq = Rotesquerda(r->esq);
        return Rotdireita(r);
    }
        if (balanco < -1 && x < r->dir->inf) {
        r->dir = Rotdireita(r->dir);
        return Rotesquerda(r);
    }
    return r;
}

no* menor(no* n) {
    no* atual = n;
    while (atual->esq != NULL) 
        atual = atual->esq;
    return atual;
}

no* remover(no* r, int x) {
    if (r == NULL) return r;

    if (x < r->inf) r->esq = remover(r->esq, x);
    else if (x > r->inf) r->dir = remover(r->dir, x);
    else {
        if ((r->esq == NULL) || (r->dir == NULL)) {
            no* aux = r->esq ? r->esq : r->dir;

            if (aux == NULL) {
                aux = r;
                r = NULL;
            } else *r = *aux;
            free(aux);
        } else {
            no* aux = menor(r->dir);
            r->inf = aux->inf;
            r->dir = remover(r->dir, aux->inf);
        }
    }

    if (r == NULL) return r;
    r->h = 1 + max(altura(r->esq), altura(r->dir));
    int balanco = balanceamento(r);

    if (balanco > 1 && balanceamento(r->esq) >= 0) return Rotdireita(r);
    if (balanco > 1 && balanceamento(r->esq) < 0) {
        r->esq = Rotesquerda(r->esq);
        return Rotdireita(r);
    }
    if (balanco < -1 && balanceamento(r->dir) <= 0) return Rotesquerda(r);
    if (balanco < -1 && balanceamento(r->dir) > 0) {
        r->dir = Rotdireita(r->dir);
        return Rotesquerda(r);
    }
    return r;
}

no* busca (no* r, int x) {
    if (r == NULL) return NULL;
    else if (r->inf == x) return r;
    else if (x < r->inf) return busca(r->esq, x);
    else return busca(r->dir, x);
}

void listar(no* r) {
    if (r == NULL) printf("()");
    else {
        printf("(");
        listar(r->esq);
        printf(" -%d- ", r->inf);
        listar(r->dir);
        printf(")");
    }
}

void liberar(no* r) {
    if (r != NULL) {
        liberar(r->esq);
        liberar(r->dir);
        free(r);
    }
}
