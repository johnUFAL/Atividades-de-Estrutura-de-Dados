#include <stdio.h>
#include <stdlib.h>

typedef struct DiscoLista{
    int *peso;
    struct DiscoLista *seguinte;
} Disco;

typedef struct PinhaOrganizada {
    Disco *inicio;
    int tamanho;
} Pilha;

void inicializacao(Pilha *torre) {
    torre->inicio = NULL;
    torre->tamanho = 0;
}

int empilhar(Pilha *torre, int peso) {
    Disco *novo_disco;
    novo_disco = (Disco*) malloc(sizeof(Disco));

    int *valor;
    valor = (int *) malloc(sizeof(int));
    if (valor == NULL) return -1;
    
    *valor = peso;
    if (novo_disco == NULL) return -1;
    else {
        novo_disco->peso = valor;
    }

    novo_disco->peso = valor;
    novo_disco->seguinte = torre->inicio;
    torre->inicio = novo_disco;
    torre->tamanho++;
    return 0;
}

int desenpilhar(Pilha *torre) {
    Disco *remove_disco;
    if (torre->tamanho == 0) return -1;

    int valor;
    remove_disco = torre->inicio;
    valor = *remove_disco->peso;
    torre->inicio = torre->inicio->seguinte;
    free(remove_disco->peso);
    free(remove_disco);
    torre->tamanho--;
    return valor;
}

void exibe(Pilha *torre) {
    Disco *aux;
    aux = torre->inicio;

    while (aux != NULL) {
        printf("Disco: %d\n", *aux->peso);
        aux = aux->seguinte;
    }    
}

Pilha* criar() {
    Pilha *pilha;
    if ((pilha = (Pilha*) malloc(sizeof(Pilha))) == NULL) return NULL;
    return pilha;
}

int inicializarDisco(Pilha *torre, int *discos) {
    printf("Quantos discos deseja? \n");
    scanf("%d", discos);
    
    if (*discos < 0) {
        return 1;
    }

    int aux = *discos;
    while (aux > 0) {
        empilhar(torre, aux);
        aux--;
    }
    return 2;
}

int tamanho(Pilha *torre) {
    return torre->tamanho;
}

int topo(Pilha *torre) {
    if (torre->inicio == NULL) return 9999;
    return *torre->inicio->peso;
}

void mostrarTorre(Pilha *torre1, Pilha *torre2, Pilha *torre3) {
    Disco *a = torre1->inicio;
    Disco *b = torre2->inicio;
    Disco *c = torre3->inicio;

    printf("\nEstado atual das torres:\n");

    while (a != NULL || b != NULL || c != NULL) {
        if (a != NULL) {
            printf("    %d", *a->peso);
            a = a->seguinte;
        } else printf("     ");

        if (b != NULL) {
            printf("    %d", *b->peso);
            b = b->seguinte;
        } else printf("     ");

        if (c != NULL) {
            printf("    %d", *c->peso);
            c = c->seguinte;
        } else printf("     ");

        printf("\n");
    }
}


void mover(Pilha *origem, Pilha *destino) {
    if (tamanho(origem) > 0 && (tamanho(destino) <= 0 || topo(origem) < topo(destino))) {
        empilhar(destino, desenpilhar(origem));
    } else {
        printf("Movimento invalido!\n");
    }
}

int movimentar(Pilha *torre1, Pilha *torre2, Pilha *torre3) {
    printf("Proximo movimento: \n\n");
    printf("1 - Mover disco do pino A para o pino B \n");
    printf("2 - Mover disco do pino A para o pino C \n");
    printf("3 - Mover disco do pino B para o pino A \n");
    printf("4 - Mover disco do pino B para o pino C \n");
    printf("5 - Mover disco do pino C para o pino A \n");
    printf("6 - Mover disco do pino C para o pino B \n");
    printf("\nDigite -1 para desistir.\n");

    int movimento;
    scanf("%d", &movimento);

    if (movimento == -1) return -1;

    switch(movimento) {
        case 1: mover(torre1, torre2); break;
        case 2: mover(torre1, torre3); break;
        case 3: mover(torre2, torre1); break;
        case 4: mover(torre2, torre3); break;
        case 5: mover(torre3, torre1); break;
        case 6: mover(torre3, torre2); break;
        default: printf("Movimento invalido\n"); return -1; break;
    }
}

int verificarTorre(Pilha *torre1, Pilha *torre2, Pilha *torre3, int discos) {
    if (torre1->tamanho == 0 && torre2->tamanho == discos && torre3->tamanho == 0) {
        printf("Probelma Solucionado! Torre B\n");
        return 1;
    }

    if (torre1->tamanho == 0 && torre2->tamanho == 0 && torre3->tamanho == discos) {
        printf("Probelma Solucionado! Torre C\n");
        return 1;
    }
    return 0;
}

int main() {
    int discos = 0;

    Pilha *A = criar();
    inicializacao(A);
    Pilha *B = criar();
    inicializacao(B);
    Pilha *C = criar();
    inicializacao(C);
    
    int m;
    inicializarDisco(A, &discos);

    do {
        mostrarTorre(A, B, C);
        m = movimentar(A, B, C);
        if (m == -1) {
            printf("Jogo encerrado pelo usuário.\n");
            break;
        }
    } while (verificarTorre(A, B, C, discos) != 1);

    return 0;

}
