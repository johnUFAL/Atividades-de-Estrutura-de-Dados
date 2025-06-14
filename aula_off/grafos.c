#include <stdio.h>
#include <stdlib.h>

typedef enum {VERMELHO, PRETO} Cor;

typedef struct no {
    int inf;
    Cor cor;
    struct no* dir;
    struct no* esq;
    struct no* pai;
} no;

#define NIL &sentinela
no sentinela = { 0, PRETO, NIL, NIL, NIL };

no* criar(int x) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) return printf("ERROR");

    novo->inf = x;
    novo->cor = VERMELHO;
    novo->dir = NIL;
    novo->esq = NIL;
    novo->pai = NIL;
    return novo;
}

void RotEsquerda(no** r, no* x) {
    no* y = x->dir;
    x->dir = y->esq;

    if (y->esq != NIL) y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NIL) *r = y;
    else if (x == x->pai->esq) x->pai->dir = y;
    else x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}

void RotDireita(no** r, no* y) {
    no *x = y->esq;
    y->esq = x->dir;
    
    if (x->dir != NIL) x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == NIL)*r = x;
    else if (y == y->pai->dir) y->pai->dir = x;
    else y->pai->esq = x;
    
    x->dir = y;
    y->pai = x;
}

void balancear_inserir(no** r, no* z) {
    while (z != *r && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            no* y = z->pai->pai->dir; 
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    RotEsquerda(r, z);
                }

                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                RotDireita(r, z->pai->pai);
            }
        } else {
            no* y = z->pai->pai->esq;
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    RotDireita(r, z);
                }

                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                RotEsquerda(r, z->pai->pai);
            }
        }
    }
    (*r)->cor = PRETO;
}

no* insere(no* r, int e) {
    no* z = criar(e);
    no* y = NIL;
    no* x = r;

    while (x != NIL) {
        y = x;
        if (z->inf < x->inf) x = x->esq;
        else x = x->dir;
    }
    z->pai = y;

    if (y == NIL) r= z;
    else if ( z->inf < y->inf) y->esq = z;
    else y->dir = z;

    balancear_inserir(&r, z);
    return r;
}

no* minimo(no* x) {
    while (x->esq != NIL)
        x = x->esq;
    return x;
}

void balancear_remocao(no **r, no *x) {
    while (x != *r && x->cor == PRETO) {
        if (x == x->pai->esq) {
            no *w = x->pai->dir;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                RotEsquerda(r, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->dir->cor == PRETO) {
                    w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    RotDireita(r, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->dir->cor = PRETO;
                RotEsquerda(r, x->pai);
                x = *r;
            }
        } else {
            no *w = x->pai->esq;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                RotDireita(r, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->esq->cor == PRETO) {
                    w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    RotEsquerda(r, w);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esq->cor = PRETO;
                RotDireita(r, x->pai);
                x = *r;
            }
        }
    }
    x->cor = PRETO;
}

no* remover(no* r, int e) {
    no* z = r;
    no *x, *y;

    while (z != NIL) {
        if (e == z->inf) break;
        z = (e < z->inf) ? z->esq : z->dir;
    }

    if (z == NIL) return r;

    if (z->esq == NIL || z->dir == NIL) y = z;
    else {
        y = minimo(z->dir);
        z->inf = y->inf;
    }

    if (y->esq != NIL) x = y->esq;
    else x = y->dir;

    x->pai = y->pai;
    if (y->pai == NIL) r = x;
    else if (y == y->pai->esq) y->pai->esq = x;
    else y->pai->dir = x;

    free(y);
    return r;
}

no* busca(no* r, int e) {
    if (r == NIL) return NULL;
    else if (r->inf == e) return r;
    else if (e < r->inf) return busca(r->esq, e);
    else return busca(r->dir, e);
}

void listar(no* r) {
    if (r == NIL) printf("()");
    else {
        printf("(");
        listar(r->esq);
        printf(" |%d|%s ", r->inf, r->cor == VERMELHO ? "V" : "P");
        listar(r->dir);
        printf(")");
    }
}

void liberar(no* r) {
    if (r != NIL) {
        liberar(r->esq);
        liberar(r->dir);
        free(r);
    }
}
