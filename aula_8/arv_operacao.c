#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int inf;
    //char* inf;
    int n_filhos;
    struct no* filhos;
} no;

no* criar(int x) {
    no* novo = (no*)malloc(sizeof(no));

    if (novo == NULL) return 0;
    novo->inf = x;
    novo->n_filhos = 0;
    novo->filhos = NULL;
    return novo;
}

void inserir(no* pai, int x) {
    if (pai == NULL) return;

    pai->n_filhos++;
    pai->filhos = (no**)realloc(pai->filhos, sizeof(no*)*pai->n_filhos);
    if (pai->filhos == NULL) return;
    pai->filhos[pai->n_filhos-1] = criar(x);
}

void liberar(no* pai) {
    if (pai == NULL) return;
    for (int i = 0; i < pai->n_filhos; i++){
        liberar(pai->filhos[i]);
    }
    free(pai->filhos);
    free(pai);
}

void imprimir(no* pai, int nv) {
    if (pai == NULL) return;

    for (int i = 0; i < nv; i++) printf("    ");
    if (nv > 0) printf("simbolo");

    pritnf("%d", pai->inf);
    for (int i = 0; i < pai->n_filhos; i++)
        imprimir(pai->filhos[i]);
}

void inverter(no* pai) {
    if (pai == NULL) return;

    pai->inf *= -1;
    for (int i = 0; i < pai->n_filhos; i++) 
        inverter(pai->filhos[i]);
}

no* soma(no* a1, no* a2) {
    if (a1 == NULL && a2 == NULL) return 0;

    int v;
    if (a1 == NULL) v = a2;
    else if (a2 == NULL) v = a1;
    else v = a1->inf + a2->inf;

    no* r = criar(v);
    int max_filho = (a1 != NULL && a2 != NULL) ?
                    (a1->n_filhos > a2->n_filhos ?
                     a1->n_filhos : a2->n_filhos) :
                    (a1 != NULL ? a1->n_filhos : a2->n_filhos);

    for (int i = 0; i < max_filho; i++) {
        no* f_a1 = (a1 != NULL && i < a1->n_filhos) ? a1->filhos[i] : NULL;
        no* f_a2 = (a2 != NULL && i < a2->n_filhos) ? a2->filhos[i] : NULL;

        no* f_soma = soma(f_a1, f_a2);
        if (f_soma != NULL) {
            inserir(r, f_soma->inf);
            liberar(f_soma);
        }
    }
    return r;
}

void buscaFolha(no* pai, int* folha, int* id) {
    if (pai == NULL) return;

    if (pai->n_filhos == 0) {
        folha[*id] = pai->inf;
        (*id)++;
    }

    for (int i = 0; i < pai->n_filhos; i++)
        buscaFolha(pai->filhos[i], folha, id);
}

void multNo(no* pai, int mult) {
    if (pai == NULL) return;

    pai->inf *= mult;
    for (int i = 0; i < pai->n_filhos; i++)
        multNo(pai->filhos[i], mult);
}

no* multAvFolha(no* a1, no* a2) {
    if (a1 == NULL || a2 = NULL) return 0;

    int folha[100];
    int n_folha = 0;
    buscaFolha(a1, folha, &n_folha);

    if (n_folha == 0) return a2;

    no* r = a2;
    for (int i = 0; i < n_folha; i++)
        multNo(r, folhas[i]);
    return r;
}

no* projecao(no* a1, no* a2) {
    if (a1 == NULL || a2 == NULL) return 0;
    
    no* r = criar(0);
    for (int i = 0; i < a1->n_filhos; i++) {
        for (int j = 0; j < a2->n_filhos; j++) {
            char c[10];
            sprintf(c, "%d%c", a1->filhos[i]->inf, a2->filhos[j]->inf);
            inserir(r, atoi(c));
        }
    }
    return r;
}

char* combina(const char* s1, const char* s2) {
    char* comb = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(comb, s1);
    strcat(comb, s2);
    return comb;
}
