#include <stdio.h>

void merge(int *v, int esquerda, int meio, int direita) { //ordenacao em duas partes em uma 
    int n1 = meio-esquerda+1; //tamanho esquuerda
    int n2 = direita-meio; //tamanho direita
    int E[n1], D[n2]; //vetores auxiliares para controle

    for (int i = 0; i < n1; i++) { //copia elemeots paara o vetor aux
        E[i] = v[esquerda+i];
    }
    for (int j = 0; j < n2; j++) { //copia elemeots paara o vetor aux
        D[j] = v[meio+j+1];
    }

    int i = 0, j = 0, k = esquerda; //indices para os whiles
    while (i < n1 && j < n2) { //comparacao entres as duas metades
        if (E[i] <= D[j]) { //INVERTE O SINAL PARA SER DECRESCENTE
            v[k] = E[i];
            i++;
        } else { //x a direita menor
            v[k] = D[j];
            j++;
        }
        k++;

        while (i < n1) { //se sobrar elementos aqui vai pro outro
            v[k] = E[i];
            i++;
            k++;
        }
        while (j < n2) { //se sobrar elementos aqui vai pro outro
            v[k] = D[j];
            j++;
            k++;
        }
    }
}

void merge_sort(int *v, int esquerda, int direita) {
    if (esquerda < direita) { //condicao de parada da rec
        int meio = esquerda + (direita-esquerda) / 2; //calculo para dividir o vetor no meio
        merge_sort(v, esquerda, meio); //ordena a primeira parte
        merge_sort(v, meio+1, direita); // a segunda
        merge(v, esquerda, meio, direita); //joga no merge pra combinar as duas partes
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    puts("Vetor normal:");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    puts(" ");

    merge_sort(arr, 0,  n-1);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}