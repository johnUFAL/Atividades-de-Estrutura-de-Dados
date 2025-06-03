#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int inf;
    int num_filhos;
    struct no** filhos;
} no;

no* criar_no(int x) {
    no* novo = (no*) malloc(sizeof(no));
    if (novo == NULL) return 0;
    
    novo->inf = x;
    novo->num_filhos = 0;
    novo->filhos = NULL;
    return novo;
}

void insere_filho(no* pai, int x) {
    if (pai == NULL) return;

    pai->num_filhos++;
    pai->filhos = (no**) realloc(pai->filhos, sizeof(no*) * pai->num_filhos);

    if (pai->filhos == NULL) return;

    pai->filhos[pai->num_filhos - 1] = criar_no(x);
}

no* busca(no* pai, int x) {
    if (pai == NULL) return NULL;
    if (pai->inf == x) return pai;

    for (int i = 0; i < pai->num_filhos; i++) {
        no* achou = busca(pai->filhos[i], x);
        if (achou != NULL) return achou;
    }
    return NULL;
}

void listar(no* pai) {
    if (pai == NULL) printf("()");

    printf("(%d, )", pai->inf);
    for (int i = 0; i < pai->num_filhos; i++) {
        printf(" ");
        listar(pai->filhos[i]);
    }
    printf(")");
}

no* remover(no* pai, int x) {
    if (pai == NULL) return NULL;

    if (pai->inf == x) {
        if (pai->num_filhos == 0) {
            free(pai->filhos);
            free(pai);
            return NULL;
        } else {
            return pai;
        }
    }

    for (int i = 0; i < pai->num_filhos; i++) {
        if (pai->filhos[i]->inf == x && pai->filhos[i]->num_filhos == 0) {
            free(pai->filhos[i]->filhos);
            free(pai->filhos[i]);
        }

        for (int j = i; j < pai->num_filhos - 1; j++) {
            pai->filhos[j] = pai->filhos[j+1];
        }
        pai->num_filhos--;
        pai->filhos = (no**) realloc(pai->filhos, sizeof(no*) * pai->num_filhos);
        return pai;
    }
    return pai;
}

void liberar(no* pai) {
    if (pai == NULL) return NULL;

    for (int i = 0; i < pai->num_filhos; i++) {
        liberar(pai->filhos[i]);
    }
    free(pai->filhos);
    free(pai);
}

int main() {
    no *raiz = criar_no(10);

    insere_filho(raiz, 20);
    insere_filho(raiz, 30);
    insere_filho(raiz->filhos[0], 40);
    insere_filho(raiz->filhos[0], 50);
    insere_filho(raiz->filhos[1], 60);


    printf("Arvore inicia: \n");
    listar(raiz);
    printf("\n");

    int opcao, e;
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
            printf("Digite o valor do pai: ");
            int pai;
            scanf("%d", &pai);
            no* no_pai = busca(raiz, pai);
            if (no_pai == NULL) printf("Nao encontrado\n");
            else {
                printf("Valor do filho: \n");
                scanf("%d", &e);
                insere_filho(no_pai, e);
                printf("\nSucesso");
            }
            break;
            
        case 2:
            printf("Busque o valor: ");
            scanf("%d", &e);
            no* encontrado = busca(raiz, e);
            if (encontrado != NULL) {
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