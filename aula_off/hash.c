#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 100

typedef struct no {
    char *chave;
    void *valor;
    struct no *prox;
} no;

typedef struct Hash {
    no* baldes[TAMANHO_HASH];
    int cont;
} Hash;

unsigned int hash(const char *chave) {
    unsigned int hash_valor = 0;
    for (int i = 0; chave[i] != '\0'; i++) 
        hash_valor = (hash_valor * 31 + chave[i] % TAMANHO_HASH);
    return hash_valor;
}

Hash* criar() {
    Hash *ht = malloc(sizeof(Hash));
    if (!ht) return NULL;

    ht->cont = 0;
    for (int i = 0; i < TAMANHO_HASH; i++)
        ht->baldes[i] = NULL;
    return ht;
}

int insere(Hash *ht, const char* chave, void *valor) {
    if (!ht || !chave ) return 0;

    unsigned int id = hash(chave);
    no* novo = malloc(sizeof(no));
    if (!novo) return 0;

    novo->chave = strdup(chave);
    novo->valor = valor;
    novo->prox = ht->baldes[id];
    ht->baldes[id] = novo;
    ht->cont++;
    return 1;
}

void* busca(Hash* ht, const char* chave) {
    if (!ht || !chave) return NULL;

    unsigned int id = hash(chave);
    no* atual = ht->baldes[id];

    while (atual) {
        if (strcmp(atual->chave, chave) == 0) return atual->valor;
        atual = atual->prox;
    }
    return NULL;
}

int remove(Hash* ht, const char* chave) {
    if (!ht || !chave) return 0;

    unsigned int id = hash(chave);
    no* atual = ht->baldes[id];
    no* anterior = NULL;

    while (atual) {
        if (strcmp(atual->chave, chave) == 0) {
            if (anterior) anterior->prox = atual->prox;
            else ht->baldes[id] = atual->prox;
        
            free(atual->chave);
            free(atual);
            ht->cont--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

void liberar(Hash *ht) {
    if (!ht) return;
    for (int i = 0; i < TAMANHO_HASH; i++) {
        no* atual = ht->baldes[i];
        while (atual) {
            no* aux = atual;
            atual = atual->prox;
            free(aux->chave);
            free(aux);
        }
    }
    free(ht);
}