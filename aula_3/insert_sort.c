#include <stdio.h> 

void insert_sort(int v[], int  n) {
    int i, j, aux; //i = elemento inserido, j = vai percorrer o arr ate achar sua posicao
    for (i = 1; i < n; i++) { //loop pra percorrer os elementos, comeca do um pq o primeiro ja esta em ordem
        aux = v[i]; //fica com o v[i] ate achar seu local
        j = i - 1; //posicao de incio de j

        //desloca os elementos
        while ((j >= 0) && (aux < v[j])) { //INVERTE O SINAL PARA SER DECRESCENTE
            v[j+1] = v[j]; //desloca v[j]
            j--; //decremanta pra continuar comparando ate a posicao certa
        }
        v[j+1] = aux; //achou entao incrementa 
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int v[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    puts("Vetor normal:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    puts(" ");

    insert_sort(v, n);

    puts("Vetor ordenado:");
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    return 0;
}