#include <stdio.h>

#define MAX_TAM 100
#define NADA -1

typedef struct {
    int valor;
    int espaco;
} Bloco;

void bubbleSort(int v[], int n) {
    int swap;
    do {
        swap = 0;
        for (int i = 0; i < n-1; i++) {
            if (v[i] > v[i+1] && v[i+1] != NADA) {
                int aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                swap = 1;
            }
        }
    } while((swap));
}

void construcao(int v[], int tam, Bloco blocos[], int *cont) {
    int ultimo= -1;
    *cont = 0;

    for (int i = 0; i < tam; i++) {
        if (v[i] != NADA) {
            blocos[*cont].valor = v[i];
            blocos[*cont].espaco = (ultimo == -1) ? 0 : i - ultimo - 1;
            ultimo = i;
            (*cont)++;
        }
    }
}

void inserir(int v[], int *n, int tam, int valor) {
    if (*n > tam) {
        printf("vetor cheio\n");
        return;
    }

    int pos = 0;
    while (pos < tam && v[pos] != NADA) pos++;

    v[pos] = valor;
    (*n)++;
    bubbleSort(v, tam);
}

void remover(int v[], int *n, int tam, int valor) {
    for (int i = 0; i < tam; i++) {
        if (v[i] == valor) {
            v[i] = NADA;
            (*n)--;
        }
    }
    bubbleSort(v, tam);
}

void impressora(int v[], int tam) {
    for (int i = 0; i < tam; i++) {
        if (v[i] == NADA) printf(" ");
        else printf("%d ", v[i]);
    }
    puts(" ");
}

int main() {
    int tam, n;

    printf("\nInforme o tamanho do vetor:\n");
    scanf("%d", &tam);
    if (tam >= MAX_TAM){
        printf("\nVetor excede a quantidade limite\n");
        return 1;
    }

    int v[tam];
    Bloco blocos[tam];

    for (int i = 0; i < tam; i++) {
        v[i] = NADA;
    }
    
    printf("\nInforme o quant de elementos:\n");
    scanf("%d", &n);

    if (n > tam) {
        printf("\nQuantidade de elementos maior que o vetor definido\n");
        return 1;
    }

    printf("\nInforme os elementos:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    bubbleSort(v, tam);
    int cont;
    construcao(v, tam, blocos, &cont);


    printf("\nVetor Ordenado:\n");
    impressora(v, tam);

    int put;
    printf("\nInforme o elemento a ser inserido:\n");
    scanf("%d", &put);
    inserir(v, &n, tam, put);
    construcao(v, tam, blocos, &cont);
    impressora(v, tam);

    int dell;
    printf("\nInforme o elemento a ser removido:\n");
    scanf("%d", &dell);
    remover(v, &n, tam, dell);
    construcao(v, tam, blocos, &cont);
    impressora(v, tam);

    return 0;
}