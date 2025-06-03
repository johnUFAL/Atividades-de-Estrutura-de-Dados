#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int inf;
    struct no *dir;
    struct no *esq;
} no;

no* criar_no(int e) {
    no* novo = (no*) malloc(sizeof(no));
    if (novo == NULL) {
        printf("ERROR\n");
        exit(1);
    }
    novo->inf = e;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

no* insere(no *r, int e) {
    if (r == NULL) return criar_no(e);
    else {
        if (e < r->inf) {
            r->esq = insere(r->esq, e);
        } else { 
            r->dir = insere(r->dir, e);
        }
        return r;
    }
}

no* busca(no *r, int e) {
    if (r == NULL) return NULL;
    else if (r->inf == e) {
        return r;
    } else if (e < r->inf) {
        return busca(r->esq, e);
    } else {
        return busca(r->dir, e);
    }
}

void listar(no *r) {
    if (r == NULL) printf("()");
    else {
        printf("(");
        listar(r->esq);
        printf(" |%d| ", r->inf);
        listar(r->dir);
        printf(")");
    }
}

no* remover(no *r, int e) {
    if (r == NULL)  return NULL;
    else if (e < r->inf) {
        r->esq = remover(r->esq, e);
    } else if (e > r->inf) {
        r->dir = remover(r->dir, e);
    } else {
        no* aux;

        if (r->esq == NULL || r->dir == NULL) {
            free(r);
            return NULL;
        } else if (r->esq == NULL) {
            aux = r->dir;
            free(r);
            return aux;
        } else if (r->dir == NULL) {
            aux = r->esq;
            free(r);
            return aux;
        } else {
            aux = r->esq;
            while (aux->dir != NULL) {
                aux = r->esq;
            }
            r->inf = aux->inf;
            r->esq = remover(r->esq, aux->inf);
        }
    }
    return r;
}

void liberar(no *r) {
    if (r != NULL) {
        liberar(r->esq);
        liberar(r->dir);
        free(r);
    }
}

int main() {
    no *raiz = NULL;
    int opcao, e;

    raiz = insere(raiz, 10);
    raiz = insere(raiz, 30);
    raiz = insere(raiz, 50);
    raiz = insere(raiz, 70);
    raiz = insere(raiz, 80);
    raiz = insere(raiz, 60);
    raiz = insere(raiz, 40);
    raiz = insere(raiz, 20);

    printf("Arvore inicia com: 10, 30, 50, 70, 80, 60, 40, 20\n");

    do {
        printf("\n--- MENU ---\n");
        printf("Opcao 1: inserir\n");
        printf("Opcao 2: busca\n");
        printf("Opcao 3: listar\n");
        printf("Opcao 4: remover\n");
        printf("Opcao 5: sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            printf("Digite o valor para inserer: ");
            scanf("%d", &e);
            raiz = insere(raiz, e);
            printf("Sucesso!\n");
            break;
            
        case 2:
            printf("Busque o valor: ");
            scanf("%d", &e);
            int resultado = busca(raiz, e);
            if (resultado != NULL) {
                printf("Encontrado na arvore!\n");
            } else {
                printf("Nao encontrado na arvore.\n");
            }
            break;
            
        case 3:
            printf("Arvore: ");
            listar(raiz);
            printf("\n");
            break;
            
        case 4:
            printf("Digite o valor para remover: ");
            scanf("%d", &e);
            raiz = remover(raiz, e);
            printf("Removido!\n");
            break;
            
        case 5:
            printf("Encerrando programa...\n");
            break;
            
        default:
            printf("Opcao invalida!\n");
        
        }

    } while (opcao != 5);

    liberar(raiz);

    return 0;
}