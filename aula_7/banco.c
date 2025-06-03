#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {
    int id;
    int prioridade;
    struct Cliente *proximo;
    int tempoAtendimento;
} Cliente;

typedef struct fila {
    Cliente *inicio;
} Fila;

int filaVazia(Fila *fila) {
    return (fila->inicio == NULL);
}

Fila* inicializar() {
    Fila *nova_fila = (Fila*) malloc(sizeof(Fila));
    nova_fila->inicio = NULL;

    return nova_fila;
}

void inserir(Fila *fila, int id, int prioridade, int *movimento) {
    Cliente *novo_cliente = (Cliente*) malloc(sizeof(Cliente));
    novo_cliente->id = id;
    novo_cliente->prioridade = prioridade;
    novo_cliente->tempoAtendimento = 0;

    Cliente *anterior = NULL;
    Cliente *atual = fila->inicio;

    if (filaVazia(fila)) {
        novo_cliente->proximo = fila->inicio;
        fila->inicio = novo_cliente;
        return;
    }

    while (novo_cliente->prioridade <= atual->prioridade) {
        anterior = atual;
        atual = atual->proximo;
        if (atual == NULL) break;
    }

    if (anterior == NULL) {
        novo_cliente->proximo = fila->inicio;
        fila->inicio = novo_cliente;
    } else {
        anterior->proximo = novo_cliente;
        novo_cliente->proximo = atual;
    }

    (*movimento)++;
    atual = fila->inicio;

    while (atual != NULL) {
        atual->tempoAtendimento++;
        atual = atual->proximo;
    }

    return;
}

void consulta(Fila* fila, int prioridade, int *movimento) {
    Cliente *anterior = NULL;
    Cliente *atual = fila->inicio;

    if (filaVazia(fila)) {
        printf("Fiça vazia\n");
        return;
    }

    while (prioridade < atual->prioridade) {
        anterior = atual;
        atual = atual->proximo;

        if (atual == NULL) {
            if (prioridade == 0) consulta(fila, 3, movimento);
            else consulta(fila, prioridade-1, movimento);
            return;
        }
    }

    printf("Cliente: %d\nPrioridade: %d\t Atendido!\n", atual->id, atual->prioridade);
    printf("Tempo de Atendimento: %d\n", atual->tempoAtendimento);
    printf("\n");

    if (anterior != NULL) anterior->proximo = atual->proximo;
    else fila->inicio = fila->inicio->proximo;
    free(atual);

    Cliente *aux = fila->inicio;
    while (aux != NULL) {
        aux->tempoAtendimento += 1;
        aux = aux->proximo;
    }
    *movimento += 1;
    return;
}

void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia\n");
        return;
    }

    Cliente *atual = fila->inicio;
    printf("\n--- Fila Atual ---\n");
    while (atual != NULL) {
        printf("Cliente %d (Prioridade: %d) - Tempo de espera: %d\n",
                atual->id, atual->prioridade, atual->tempoAtendimento);
        atual = atual->proximo;
    }
    printf("----------------\n");
}

void remover_elemento(Fila *fila) {
    Cliente *aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    free(aux);
    return;
}

int main() {
    Fila *fila = inicializar();
    int movimento = 1, loop = 1, opcao, id, prioridade = 3, prioridadeInput;

    while (loop) {
        if (movimento == 4) {
            if (prioridade == 0) prioridade = 3;
            else prioridade--;
        }
    
    printf("\n--- Menu ---\n");
    printf("1. Inseir cliente\n");
    printf("2. Atender cliente\n");
    printf("3. Exibir fila\n");
    printf("4. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: 
            printf("Digite o ID do cliente: ");
            scanf("%d", &id);
            printf("Digite a prioridade (0-3, 3 é a maior): ");
            scanf("%d", &prioridadeInput);
                if (prioridade < 0 || prioridade > 3) {
                    printf("Prioridade invalida: Use valores netre 0 e 3\n");
                    break;
                }
                inserir(fila, id, prioridadeInput, &movimento);
                break;

        case 2:
            consulta(fila, prioridadeInput, &movimento);
            break;
        case 3:
            exibirFila(fila);
            break;
        case 4:
            loop = 0;
            break;
        default: 
        printf("Opcao invalida\n");

        }
    }

    while (!filaVazia(fila)) {
        remover_elemento(fila);
    }

    free(fila);

    return 0;
}